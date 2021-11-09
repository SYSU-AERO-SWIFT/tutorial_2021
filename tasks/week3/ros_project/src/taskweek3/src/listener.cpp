#include "ros/ros.h"
#include "taskweek3/Num.h"
void chatterCallback(const taskweek3::Num::ConstPtr& data)
{
    ROS_INFO("I heard:  %d  ", data->num);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "listener");
    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe("chatter", 100, chatterCallback);

    ros::spin();

    return 0;
}