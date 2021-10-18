/*************************************************************************
	> File Name: test_service.cpp
	> Author:ZX Xie 
	> Mail:1514806752@qq.com 
	> Created Time: 2021年10月17日 星期日
 ************************************************************************/

#include <cstdlib>
#include <ros/ros.h>
#include <learning_service/serve.h>

using namespace ros;

// service回调函数
bool func(learning_service::serve::Request &c,learning_service::serve::Response &d){
    if (c.num < 0.5){
        d.reply = true;
    }
    else d.reply = false;
    return true;
}

int main(int argc, char **argv){
    // ROS节点初始化
    ros::init(argc, argv, "test_service");
    // 创建节点句柄
    ros::NodeHandle n;
    // 创建server
    ros::ServiceServer service = n.advertiseService("learning_service", func);
    // 循环等待回调函数
    ros::spin();
    return 0;
}
