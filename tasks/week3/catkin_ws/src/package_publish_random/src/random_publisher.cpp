#include <iostream>
#include <cstdlib>
#include <ros/ros.h>
#include <package_publish_random/my_own_msg.h>
using namespace std;
int main(int argc,char** argv)
{
  //初始化节点名称
  ros::init(argc,argv,"random_publisher");
  //声明一个节点句柄
  ros::NodeHandle nh;
  //声明发布者,消息文件是my_own_msg，话题名称是topic
  ros::Publisher ros_pub=nh.advertise<package_publish_random::my_own_msg>("topic",10);
  //设定循环周期
  ros::Rate loop_rate(10);
  //声明一个叫msg的消息
  package_publish_random::my_own_msg msg;
  while(ros::ok())
  {
    msg.random_number= rand();
    ROS_INFO("published_number=%f",msg.random_number);
    ros_pub.publish(msg);
    loop_rate.sleep();
  }
  return 0;
}
