#include "parser.h"
#include <urdf/model.h>
#include <string>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Point.h>
#include <ros/ros.h>
#include <random>
#include <iomanip>
#include<cmath>
using namespace std;
using namespace ros;
float angle=0;
int main(int argc, char** argv)
{
  init(argc,argv,"publisher");
  NodeHandle n;
  Publisher car_publisher= n.advertise<geometry_msgs::Vector3>("car_control", 10);
  
  geometry_msgs::Vector3 info;
  Rate loop_rate(20);//设置发布频率为20HZ
  while(ok())
  { angle +=M_PI/100;
    info.x=(sin(angle)-sin(angle-M_PI/100));
    info.y=abs(cos(angle)-cos(angle-M_PI/100));
    info.z=fmod(angle,M_PI)<M_PI?fmod(angle,M_PI*2)-M_PI/2:fmod(angle,M_PI*2)-M_PI;
    car_publisher.publish(info);
    ROS_INFO("command has been published!");
    loop_rate.sleep();
  }
  return 0;
}
