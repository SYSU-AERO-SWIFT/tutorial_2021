#include <ros/ros.h>
#include "week3_tasks/Rdata.h"
#include <iostream>
#include <time.h> 

using namespace std; 

int main(int argc,char **argv){
	ros::init(argc,argv,"rdata_publisher"); 

	ros::NodeHandle n; 

	ros::Publisher rdata_pub = n.advertise<week3_tasks::Rdata>("/rdata_info",10); 

	ros::Rate loop_rate(10); 

	srand(time(0)); 

	while(ros::ok()){
		week3_tasks::Rdata tmp; 
	        tmp.rdata = rand(); 	

		rdata_pub.publish(tmp);  

		ROS_INFO("PUBLISHER:: %d\n",tmp.rdata); 
	}

	loop_rate.sleep(); 

	return 0; 
}

