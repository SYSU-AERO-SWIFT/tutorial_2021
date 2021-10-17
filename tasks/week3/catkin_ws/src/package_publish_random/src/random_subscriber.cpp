#include "ros/ros.h"
#include "package_publish_random/my_own_msg.h"

void msgCallback(const package_publish_random::my_own_msg::ConstPtr& msg)
{
  ROS_INFO("receive msg=%f",msg->random_number);
}

int main(int argc,char** argv)
{
  ros::init(argc,argv,"random_subscriber");
  ros::NodeHandle nh;
  ros::Subscriber ros_sub=nh.subscribe("topic",10,msgCallback);
  ros::spin();
  return 0;
}
