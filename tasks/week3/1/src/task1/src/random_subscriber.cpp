//订阅/random_int话题，自定消息类型task1::random
#include <ros/ros.h>
#include "task1/random.h"

//回调函数
void randomIntCallback(const task1::random::ConstPtr& msg)
{
	ROS_INFO("Subscribe random int: %d",msg->random_int);
}
int main(int argc,char ** argv)
{
	ros::init(argc,argv,"random_subscriber");
	ros::NodeHandle n;
	ros::Subscriber random_int_sub = n.subscribe("/random_int",10,randomIntCallback);
	ros::spin();
	return 0;
}