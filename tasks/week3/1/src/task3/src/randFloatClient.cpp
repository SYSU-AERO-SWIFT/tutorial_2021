// 请求/judge服务，服务数据类型task3::random_float

#include <ros/ros.h>
#include "task3/random_float.h"
#include <iostream>
#include <cstdlib>
int main(int argc,char **argv)
{
	ros::init(argc,argv,"randFloatClient");
	ros::NodeHandle node;
	ros::service::waitForService("/judge");
	ros::ServiceClient rand_client = node.serviceClient<task3::random_float>("judge");

	task3::random_float srv;
	srv.request.val = rand() / double(RAND_MAX);
	rand_client.call(srv);

	ROS_INFO("The random number is: %lf.",srv.response.val_return);
	ROS_INFO("The result is %s",srv.response.result ? "Yes" : "No");
	return 0;
}