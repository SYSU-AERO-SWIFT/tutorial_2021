#include "ros/ros.h"
#include "taskweek3/reply_acr_float.h"
#include<cstdlib>
#include<ctime>

float get_rand()
{
    #define N 999
    srand(time(NULL));
    return rand()%(N+1)/(float)(N+1);
 }

int main(int argc, char** argv)
{
    ros::init(argc, argv, "task_client");

    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<taskweek3::reply_acr_float>("reply_acr_float");

    taskweek3::reply_acr_float srv;
    srv.request.rand_gen = get_rand();

    if(client.call(srv))
    ROS_INFO("Request: %f  --  answer: %d ", srv.request.rand_gen,  srv.response.answer);

    return 0;
}