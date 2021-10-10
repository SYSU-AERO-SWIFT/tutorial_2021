#include "ros/ros.h"


int main(int argc,char** argv)
{
    ros::init(argc,argv,"parameter_get");
    ros::NodeHandle nh;

    float num=nh.param("floating_num",0);
    ROS_INFO("floating number is:%f",num);
    if(num<0.5)
    {
        ROS_INFO("Yes");
    }
    else
    {
        ROS_INFO("No");
    }
    return 0;
}