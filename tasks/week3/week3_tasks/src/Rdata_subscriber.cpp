#include <ros/ros.h>
#include "week3_tasks/Rdata.h"

void RdataCallback(const week3_tasks::Rdata::ConstPtr& msg){
	ROS_INFO("SUB Info: number:%d\n",
		 msg->rdata);  
}

int main(int argv,char** argc){
	ros::init(argv,argc,"rdata_subscriber"); 

	ros::NodeHandle n; 

	ros::Subscriber rdata_sub = n.subscribe("/rdata_info",10,RdataCallback); 

	ros::spin(); 

	return 0; 
}
