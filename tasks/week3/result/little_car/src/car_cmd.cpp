#include <ros/ros.h>
#include "little_car/Cmd.h"

const double PI = acos(-1); 

int main(int argc,char** argv){
	
	ros::init(argc,argv,"car_cmd"); 
	ros::NodeHandle n; 

	ros::Publisher car_cmd_pub = n.advertise<little_car::Cmd>("/cmd_info",10); 

	ros::Rate loop_rate(20); 

	double k = 1.0; 
	int fl = 80; 
	little_car::Cmd tmp; 
	while(ros::ok()){
		tmp.yaw = PI/4 * k;  
		car_cmd_pub.publish(tmp);
	        ROS_INFO("pub success"); 	   
		loop_rate.sleep();
		fl++; 
		fl = fl % 160; 
		if(fl == 0) {
			k = -k; 
		}
	} 
}
