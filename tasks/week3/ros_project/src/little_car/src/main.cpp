#include "parser.h"
#include <urdf/model.h>
#include <string>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Point.h>
#include <ros/ros.h>
#include <random>
#include <iomanip>
#include "std_msgs/Float32MultiArray.h"
using namespace std;
 //初始化控制对象  小车//初始化控制对象  小车
SVector3 velocity={0,0,0};

void callback_set_yaw(const std_msgs::Float32MultiArray::ConstPtr& msg)
{
    velocity.x=msg->data[0];
	velocity.y=msg->data[1];
	velocity.z=0;
}

int main(int argc, char** argv) {
    
	ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;
	little_car car;
    car.joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
	car.pos_pub = n.advertise<geometry_msgs::Point>("car_position",1); //小车的位置消息发布
	
	/* 
	 *请添加一个Subscriber，从你自己编写的Publisher处订阅指令
	 */
   ros::Subscriber velocity_sub=n.subscribe("velocity",100,callback_set_yaw);

    
	/*
	 *若有需要，也可以从小车处发布你所需要的信息
	 */
    ros::Rate loop_rate(20); 
	car.set_noise_level(2);		   //设置噪声等级

	/*
	//noise==0
	//make a turn
	
	while (ros::ok()) {
				   //修改小车的方向
		velocity.x=yaw*sin(yaw);
		velocity.y=yaw*cos(yaw);
		velocity.z=0;
		 
		car.set_velocity(velocity);//设置小车速度
        car.update_();//小车状态更新
		loop_rate.sleep();
    }
	*/

    while(ros::ok()){
		//car.set_yaw(yaw);
		car.set_velocity(velocity);
		car.update_();//小车状态更新
		loop_rate.sleep();
	}

	ros::spin();


    return 0;
}

