// 发布 /little_car_control话题，消息类型Vecotr3，x记录速率，y记录航向角 --> x、y记录速度，z记录航向角

#include <ros/ros.h>
//#include "little_car/control.h"
#include <geometry_msgs/Vector3.h>
#include <math.h>
int main(int argc,char ** argv)
{
	ros::init(argc,argv,"control_publisher");
	ros::NodeHandle n;
	ros::Publisher little_car_control_pub = n.advertise<geometry_msgs::Vector3>("little_car_control",10);

	ros::Rate loop_rate(20);
	int r = 1;
	float y = 0.0;
	while(ros::ok())
	{
		geometry_msgs::Vector3 control_msg;
		double tot = 0.05;
		y = y + r * 0.01;
		if (y >= 1.0 || y <= -1.0)
		{
			r = r * -1;
		}
		control_msg.z = y;
		control_msg.x = tot * cos(control_msg.z);
		control_msg.y = tot * sin(control_msg.z);
		little_car_control_pub.publish(control_msg);
		loop_rate.sleep();
	}
}