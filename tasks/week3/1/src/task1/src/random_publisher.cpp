#include <ros/ros.h>
#include "task1/random.h"
#include <iostream>
#include <cstdlib>
using namespace std;

//发布/random_int话题，自定义消息类型task1::random
int main(int argc,char ** argv)
{
	ros::init(argc,argv,"random_publisher");
	ros::NodeHandle n;
	ros::Publisher random_int_pub = n.advertise<task1::random>("/random_int",10);
	ros::Rate loop_rate(1);
	int count = 0;
	while (ros::ok())
	{
		task1::random random_msg;
		random_msg.random_int = rand() % 100;

		//发布
		random_int_pub.publish(random_msg);
		loop_rate.sleep();

	}
	return 0;
}