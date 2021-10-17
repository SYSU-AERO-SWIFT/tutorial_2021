#include <ros/ros.h> 
#include "week3_tasks/Rfdata.h"

bool dataCallback(week3_tasks::Rfdata::Request& req,
		    week3_tasks::Rfdata::Response& res){

	ROS_INFO("Random float data:%f",req.data);  

	if(req.data<0.5) res.result = "YES";
	else res.result = "NO"; 	

	return true; 
} 

int main(int argv,char** argc){
	
	ros::init(argv,argc,"rfdata_server"); 

	ros::NodeHandle n; 

	ros::ServiceServer rfdata_server = n.advertiseService("/show_data",dataCallback); 

	ROS_INFO("Ready to show data");  

	ros::spin(); 
	return 0; 
}
