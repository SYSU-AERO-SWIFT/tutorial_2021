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
#include <geometry_msgs/Vector3.h>
//#include "little_car/control.h"
using namespace std;
SVector3 un_velocity={0,0.008,0};
float un_yaw;
little_car car;//初始化控制对象  小车
void turn(float delta_yaw,float &yaw,SVector3 & velocity,float speed){
	yaw += delta_yaw;
	velocity.x = speed * cos(yaw);
	velocity.y = speed * sin(yaw);
}
void controlCallback(const geometry_msgs::Vector3::ConstPtr & msg)
{
	SVector3 velocity={(float)msg->x,(float)msg->y,0};
	//SVector3 velocity={0,0.008,0};
	//float yaw = 0;
	float yaw = (float)msg->z;
	car.set_yaw(yaw);    //修改小车的方向
	car.set_velocity(velocity);//设置小车速度
    car.update_();//小车状态更新
}
int main(int argc, char** argv) {
    ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;
	//little_car car;//初始化控制对象  小车
    car.joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
	car.pos_pub = n.advertise<geometry_msgs::Point>("car_position",1); //小车的位置消息发布
	/* 
	 *请添加一个Subscriber，从你自己编写的Publisher处订阅指令
	 */
	//ros::Subscriber control_sub = n.subscribe("/little_car_control",10,&controlCallback);

	/*
	 *若有需要，也可以从小车处发布你所需要的信息
	 */


    ros::Rate loop_rate(60);
	SVector3 velocity={0,0,0};  //速度向量
	car.set_noise_level(0);		   //设置噪声等级
	float yaw = 0.0;
    while (ros::ok()) {
		yaw += 0.01;
		turn(0.01,yaw,velocity,0.008);	//写死转向
		//yaw = un_yaw;
		//velocity.x = un_velocity.x;
		//velocity.y = un_velocity.y;
		car.set_yaw(yaw);    //修改小车的方向
		car.set_velocity(velocity);//设置小车速度
        car.update_();//小车状态更新
		loop_rate.sleep();
		
    }

    ros::spin();
    return 0;
}

