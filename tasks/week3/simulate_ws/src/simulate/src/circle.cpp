#include <ros/ros.h>
#include "geometry_msgs/Twist.h"

int main(int argc, char *argv[])
{
    ros::init(argc,argv,"circle");
    ros::NodeHandle n;
    ros::Publisher pub=n.advertise<geometry_msgs::Twist>("cmd_vel",10);
    geometry_msgs::Twist msg;
    msg.angular.z=1;
    msg.angular.x=1;

    while(ros::ok())
    {
        pub.publish(msg);
        


    }
    return 0;
}
