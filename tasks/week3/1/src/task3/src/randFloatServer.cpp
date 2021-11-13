//执行/judge服务，服务数据类型task3::random_float

#include <ros/ros.h>
#include "task3/random_float.h"

bool randCallback(task3::random_float::Request &req,task3::random_float::Response &res)
{
	res.val_return = req.val;
	res.result = (req.val < 0.5);
	return true;
}

int main(int argc,char **argv)
{
	ros::init(argc,argv,"randFloatServer");
	ros::NodeHandle n;
	ros::ServiceServer rand_server = n.advertiseService("/judge",randCallback);

	ros::spin();
	return 0;
}
