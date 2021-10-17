#include "parser.h"
#include <urdf/model.h>
#include <string>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Point.h>
#include <ros/ros.h>
#include <random>
#include <iomanip>
#include <little_car/Cmd.h>
using namespace std;

const double PI = acos(-1); 
double yaw = 0.0; 

void cmdCallback(const little_car::Cmd::ConstPtr& msg){
	yaw = msg->yaw; 
	ROS_INFO("change success"); 
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;
	little_cars car;//初始化控制对象  小车
    car.joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
	car.pos_pub = n.advertise<geometry_msgs::Point>("car_position",1); //小车的位置消息发布
	/* 
	 *请添加一个Subscriber，从你自己编写的Publisher处订阅指令
	 */
	ROS_INFO("WAIT COMMAND"); 
	ros::Subscriber car_cmd_sub = n.subscribe("/cmd_info",10,cmdCallback);  
	/*
	 *若有需要，也可以从小车处发布你所需要的信息
	 */
    	ros::Rate loop_rate(60);
	SVector3 velocity;  //速度向量
	car.set_noise_level(1);		   //设置噪声等级
        while (ros::ok()) {
	//	yaw += 0.01;
	//	car.set_yaw(yaw); 		   //修改小车的方向 
	ros::spinOnce(); 
	velocity = {sin(yaw)*0.004,cos(yaw)*0.004,0};  
	car.set_yaw(-yaw); 
	car.set_velocity(velocity);//设置小车速度
        car.update_();//小车状态更新
	loop_rate.sleep();
    }

    return 0;
}

