#include "ros/ros.h"
#include <dynamic_reconfigure/server.h>
#include <dynamic_tutorials/AkiraConfig.h>

int main(int argc, char **argv)
{
    dynamic_reconfigure::Client<dynamic_tutorials::Akira> client("dynamic_srv", dynCallBack);  //订阅服务，并设置回调函数用于回读改变后的最新参数
    dynamic_tutorials::Akira config;

    ros::Rate loop_rate(10);
    while (ros::ok())
    {

        config.num = rand();
        client.setConfiguration(config);          //用于更新参数
       

        ros::spinOnce();
        loop_rate.sleep();
    }
}

