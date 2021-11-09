#include "ros/ros.h"
#include "taskweek3/reply_acr_float.h"

bool judge(taskweek3::reply_acr_float::Request &req,
                        taskweek3::reply_acr_float::Response &res)
{
    if(req.rand_gen<0.5){
        res.answer = 1;
    }
    else res.answer = 0;
    return 1;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "task_server");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("reply_acr_float", judge);
    ros::spin();

    return 0;
}