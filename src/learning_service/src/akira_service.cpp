#include <ros/ros.h>
#include "learning_service/Akira.h"
#include <cstdlib>
// service回调函数，输入参数req，输出参数res
bool akiraCallback(learning_service::Akira::Request  &req,
         			learning_service::Akira::Response &res)
{
    // 显示请求数据
    ROS_INFO("float get %0.2f",  req.num);

	// 设置反馈数据
	if(req.num<0.5)
	res.yes = 1;
	else
	res.yes = 0;
	

    return true;
}

int main(int argc, char **argv)
{
    // ROS节点初始化
    ros::init(argc, argv, "akira_server");

    // 创建节点句柄
    ros::NodeHandle n;

    // 创建一个名为/akira的server，注册回调函数personCallback
    ros::ServiceServer akira_service = n.advertiseService("/akira", akiraCallback);

    // 循环等待回调函数
    ROS_INFO("Ready to show bool");
    ros::spin();

    return 0;
}
