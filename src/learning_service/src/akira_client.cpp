#include <ros/ros.h>
#include "learning_service/Akira.h"
#include <cstdlib>
#include "ros/time.h"

int main(int argc, char** argv)
{
    // 初始化ROS节点
	ros::init(argc, argv, "akira_client");

    // 创建节点句柄
	ros::NodeHandle node;

    // 发现/spawn服务后，创建一个服务客户端，连接名为/spawn的service
	ros::service::waitForService("/akira");
	ros::ServiceClient akira_client = node.serviceClient<learning_service::Akira>("/akira");

    // 初始化learning_service::Person的请求数据
	learning_service::Akira srv;
	srv.request.num = rand()/1000;
	

    // 请求服务调用
	ROS_INFO("Call service to evaluate float", 
			  srv.request.num);

	akira_client.call(srv);

	// 显示服务调用结果
	ROS_INFO("Show float result : %s", srv.response.yes);
	if(srv.response.yes>0)
		ROS_INFO("yes");
	else
		ROS_INFO("No");

	return 0;
};

