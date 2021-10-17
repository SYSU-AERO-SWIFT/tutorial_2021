#include "parser.h"
#include <urdf/model.h>
#include <string>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Point.h>
#include <ros/ros.h>
#include <random>
#include <iomanip>
#include <math.h>
#include "std_msgs/Float32.h"


int main(int argc, char** argv) {
    
    ros::init(argc, argv, "command_publisher");
    ros::NodeHandle n;
    
    
    ros::Publisher v_pub=n.advertise<std_msgs::Float32>("yaw",100);

    
    std_msgs::Float32 msg_yaw;
    msg_yaw.data=0.0;
    ros::Rate loop_rate(60);
    while(ros::ok())
    {
        msg_yaw.data=msg_yaw.data+0.01;
        v_pub.publish(msg_yaw);
        loop_rate.sleep();
           
    }
}
