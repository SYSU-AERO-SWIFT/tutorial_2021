#include "parser.h"
#include "littlecar/command.h"
#include <ros/ros.h>
#include <cmath> 

using namespace std;

littlecar::command next_state;	

void car_forward(const littlecar::command::ConstPtr current_state, float& acceleration);

int main(int argc, char** argv)

{
	ros::init(argc, argv, "commandPub");
    ros::NodeHandle m;
	ros::Rate loop_rate(20);

    ros::Publisher command_publisher = m.advertise<littlecar::command>("/command2car", 100);
    
	float acceleration = 0.001;


	while(ros::ok())
    {
		ros::Subscriber sub = m.subscribe<littlecar::command>("/car_state", 100, boost::bind(&car_forward, _1, acceleration));
		ros::spinOnce();

		command_publisher.publish(next_state);
		
        loop_rate.sleep();
    }
    
    return 0;
}

void car_forward(const littlecar::command::ConstPtr current_state, float& acceleration)
{
	if(current_state->x != 0)
		next_state.th = atan(current_state->y/current_state->x);
	else
		next_state.th = 1.5707;
	next_state.x = current_state->x + acceleration*cos(next_state.th);
	next_state.y = current_state->y + acceleration*sin(next_state.th);
	next_state.z = current_state->z;
	
}

