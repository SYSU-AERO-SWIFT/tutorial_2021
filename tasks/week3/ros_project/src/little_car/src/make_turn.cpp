
#include <geometry_msgs/Point.h>
#include <ros/ros.h>
#include "parser.h"
#include "geometry_msgs/Twist.h"


int main(int argc, char* argv[])
{
    ros::init(argc, argv, "make_turn");
    ros::NodeHandle nh;
    ros::Publisher pub=nh.advertise<geometry_msgs::Twist>("maketurn",10);
    geometry_msgs::Twist velocity_and_yaw_msg;
    ros::Rate rate(60);
    ros::Duration du(2);
    du.sleep();
    float yaw=0;
    float velocity=0.008;
    velocity_and_yaw_msg.linear.x=0;
    velocity_and_yaw_msg.linear.y=0.008;
    velocity_and_yaw_msg.angular.z=yaw;
    int count=0;
    //let the cat go straight
    while(ros::ok())
    {
        count++;
        rate.sleep();

        if(count>200)
        {
            break;
        }
        pub.publish(velocity_and_yaw_msg);
    }
    
    //let the car make a turn
    while(ros::ok())
    {
       
       velocity_and_yaw_msg.linear.x=-velocity*sin(yaw);
       velocity_and_yaw_msg.linear.y=velocity*cos(yaw);
       velocity_and_yaw_msg.angular.z=yaw;
       yaw+=0.01;
       pub.publish(velocity_and_yaw_msg);

       rate.sleep();
       if(yaw>=3.14)
       {
           break;
       }
    }
    //let the car stop
    velocity_and_yaw_msg.linear.x=0;
    velocity_and_yaw_msg.linear.y=0;
    pub.publish(velocity_and_yaw_msg);
    ros::spinOnce();



    return 0;
}
