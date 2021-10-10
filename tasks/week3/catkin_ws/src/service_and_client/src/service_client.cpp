#include "ros/ros.h"
#include "service_and_client/Mysrv.h"
#include <ctime>
#include <cstdlib>
#define N 99999

int main(int argc,char** argv)
{
    ros::init(argc,argv,"service_client");
    ros::NodeHandle nh;
    ros::ServiceClient client=nh.serviceClient<service_and_client::Mysrv>("float_number");
    service_and_client::Mysrv mysrv;
    mysrv.request.num=rand()%(N+1)/(float)(N+1);
    ROS_INFO("random number between 0 and 1 %f",mysrv.request.num);
    if(client.call(mysrv))
    {
        if(mysrv.response.response==1)
        {
            ROS_INFO("yes");
        }
        else
        ROS_INFO("no");

    }
    else
    {
        ROS_INFO("Failed to call service");
    }
    return 0;
}