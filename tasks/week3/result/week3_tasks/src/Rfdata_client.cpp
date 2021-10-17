#include <ros/ros.h>
#include "week3_tasks/Rfdata.h"
#include <time.h> 
int main(int argv,char** argc) {
	
	ros::init(argv,argc,"rfdata_Client"); 

	ros::NodeHandle node; 

	ros::service::waitForService("/show_data"); 
	ros::ServiceClient rfdata_client = node.serviceClient<week3_tasks::Rfdata>("/show_data"); 

	srand((unsigned)time(0)); 
	week3_tasks::Rfdata srv; 
	srv.request.data = rand()/float(RAND_MAX);  

	ROS_INFO("Call service to show romdom float: %f",
		  srv.request.data);  
	
	rfdata_client.call(srv); 

	ROS_INFO("Show result :data:%f judge:%s",
		 srv.request.data,srv.response.result.c_str()); 

	return 0; 
	
}
