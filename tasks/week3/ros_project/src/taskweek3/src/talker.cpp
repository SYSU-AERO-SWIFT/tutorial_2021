#include "ros/ros.h"
#include "taskweek3/Num.h"
#include<stdlib.h>
#include<time.h>

int get_rand()
{
    srand(time(NULL));
    return rand()%(100);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "talker");
    ros::NodeHandle n;
    ros::Publisher chatter_pub = n.advertise<taskweek3::Num>("chatter", 100);
    ros::Rate loop_rate(10);
    int count = 0;

    while(ros::ok())
    {
        taskweek3::Num data;
        srand((unsigned)time(NULL));
        data.num = get_rand();

        ROS_INFO("Rand number generated : %d  ", data.num);

        chatter_pub.publish(data);

        ros::spinOnce();

        loop_rate.sleep();
    }
    return 0;
}