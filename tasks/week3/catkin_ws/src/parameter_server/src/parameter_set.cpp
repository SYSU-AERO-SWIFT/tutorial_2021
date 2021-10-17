#include "ros/ros.h"
#include <cstdlib>
#define N 99999
int main(int argc,char** argv)
{
    ros::init(argc,argv,"set_parameter");
    ros::NodeHandle nh;
    nh.setParam("floating_num",rand()%(N+1)/(float)(N+1));
    return 0;
}