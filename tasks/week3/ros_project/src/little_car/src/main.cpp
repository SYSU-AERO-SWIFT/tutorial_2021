#include "parser.h"
#include <urdf/model.h>
#include <string>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Point.h>
#include <ros/ros.h>
#include <random>
#include <iomanip>
#include "geometry_msgs/Twist.h"

using namespace std;


/*
*********************************************************************************
This main function lets the car go straight,make a turn and then stop without noise 
*********************************************************************************
*/

/*
 void control(const geometry_msgs::Twist::ConstPtr msg_ptr)
 {
	static SVector3 velocity={0,0,0};
    static float yaw = 0.0;
    static little_car car;//初始化控制对象  小车
    yaw=msg_ptr->angular.z;
	velocity.x=msg_ptr->linear.x;
	velocity.y=msg_ptr->linear.y;
	velocity.z=0;
    ROS_INFO("receive_message");
	car.set_velocity(velocity);//设置小车速度
	car.set_yaw(yaw);
    car.update_();//小车状态更新
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;
    little_car car;
    car.joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
    car.pos_pub = n.advertise<geometry_msgs::Point>("car_position",1); //小车的位置消息发布

    ros::Subscriber sub=n.subscribe<geometry_msgs::Twist>("maketurn",10,control);
    car.set_noise_level(0);    //设置噪声等级
    ros::spin();
    return 0;
}
*/


/*
*************************************************************************************
this program lets the car go S shape with noise
*************************************************************************************
*/

void go_S(const geometry_msgs::Twist::ConstPtr msg_ptr)
 {
	static SVector3 velocity={0,0,0};
    static float yaw = 0.0;
    static little_car car;//初始化控制对象  小车
    yaw=msg_ptr->angular.z;
	velocity.x=msg_ptr->linear.x;
	velocity.y=msg_ptr->linear.y;
	velocity.z=0;
    ROS_INFO("receive_message");
	car.set_velocity(velocity);//设置小车速度
	car.set_yaw(yaw);
    car.update_();//小车状态更新
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;
    little_car car;
    car.pos_pub = n.advertise<geometry_msgs::Point>("position",1); //小车的位置消息发布
    car.joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
    
    ros::Subscriber	sub=n.subscribe("controlcommand",10,go_S);
    car.set_noise_level(5);    //设置噪声等级
    ros::spin();
    return 0;
}