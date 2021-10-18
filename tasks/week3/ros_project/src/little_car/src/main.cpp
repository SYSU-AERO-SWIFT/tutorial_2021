#include "parser.h"
#include <urdf/model.h>
#include <string>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Point.h>
#include <ros/ros.h>
#include <random>
#include <iomanip>
#include <cmath>
#include <geometry_msgs/Twist.h>
using namespace std;


SVector3 g_cmd_acc={0,0,0};
float g_yaw;
geometry_msgs::Twist g_car_vel;

void myCallback(const geometry_msgs::TwistConstPtr acc_holder)
{
		g_cmd_acc.x=(acc_holder->linear).x;
		g_cmd_acc.y=(acc_holder->linear).y;
		g_cmd_acc.z = 0;

		//g_yaw = atan2(g_cmd_acc.y, g_cmd_acc.x);
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;
	little_car car;//初始化控制对象  小车
    car.joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
	car.pos_pub = n.advertise<geometry_msgs::Point>("car_position",1); //小车的位置消息发布

		// 添加一个订阅者，从“cmd_acc”获取加速信息
	ros::Subscriber my_subscriber_object = n.subscribe<geometry_msgs::Twist>("cmd_acc",1, myCallback);

		// 添加一个发布者，发布小车的速度信息到“car_vel”
	ros::Publisher my_publish_object = n.advertise<geometry_msgs::Twist>("car_vel", 1);

	car.set_noise_level(0);		   //设置噪声等级
	ros::Rate loop_rate(60); 
	float dt = 1.0/60.0;  //设置小车的加速时间间隔

	// 小车的初状态
	SVector3 velocity={0,0,0}; 
	float yaw = 0.0;

    while (ros::ok())
	 {
		velocity.x = g_cmd_acc.x * dt;
		velocity.y = g_cmd_acc.y * dt;
		velocity.z = g_cmd_acc.z * dt;
		yaw += 0.01;

		//设置小车速度和角度
		car.set_velocity(velocity);
		car.set_yaw(yaw);

		// 发布小车速度信息
		g_car_vel.linear.x = velocity.x;
		g_car_vel.linear.y = velocity.y;
		g_car_vel.linear.z = velocity.z;
		my_publish_object.publish(g_car_vel);

        car.update_(); //小车状态更新

		ros::spinOnce();
		loop_rate.sleep();
    }

    return 0;
}

