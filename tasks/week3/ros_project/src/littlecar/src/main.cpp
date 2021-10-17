#include "parser.h"
#include "littlecar/command.h"
#include <urdf/model.h>
#include <string>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Point.h>
#include <ros/ros.h>
#include <random>
#include <iomanip>
#include <thread>
using namespace std;

void deCommand(const littlecar::command::ConstPtr next_state, SVector3 &velocity, float &yaw)
{
	velocity.x = next_state->x;
	velocity.y = next_state->y;
	velocity.z = next_state->z;
	yaw = next_state->th;
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;
	little_car car;//初始化控制对象  小车
    car.joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
	car.pos_pub = n.advertise<geometry_msgs::Point>("car_position",1); //小车的位置消息发布
	/* 
	 *请添加一个Subscriber，从你自己编写的Publisher处订阅指令
	 */

		

	/*
	 *若有需要，也可以从小车处发布你所需要的信息
	 */


	ros::Publisher state_pub = n.advertise<littlecar::command>("/car_state", 100);
	

    ros::Rate loop_rate(60);
	SVector3 velocity={0,0.008,0};  //速度向量
	car.set_noise_level(0);		   //设置噪声等级
	float yaw = 0.0;
	car.set_yaw(yaw);//修改小车的方向
	car.set_velocity(velocity);//设置小车速度
	car.update_();//小车状态更新

    while (ros::ok()) {

		SVector3 current_velocity = car.get_velocity(); 
		
		littlecar::command current_state;
		current_state.x = current_velocity.x;
		current_state.y = current_velocity.y;
		current_state.z = current_velocity.z;
		current_state.th = yaw;
		state_pub.publish(current_state);		
	
		ros::Subscriber sub0 = n.subscribe<littlecar::command>("/command2car", 100, boost::bind(&deCommand, _1, velocity, yaw));
		ros::spinOnce();
		
		car.set_velocity(velocity);
		car.set_yaw(yaw);
		car.update_();//小车状态更新

		loop_rate.sleep();
    }


    return 0;
}

