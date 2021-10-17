#include <geometry_msgs/Point.h>
#include <ros/ros.h>
#include "geometry_msgs/Twist.h"
#include "add_noise.h"
#include <sensor_msgs/JointState.h>
using namespace std;
int circle_count=0;
float yaw=0;
float now_x=0.0;
float now_y=0.0;
float x_new_v;
float y_new_v;

//Initiate the PID struct
void control::IncPIDInit()
{
    x_ptr->LastError=0;  //  Error[-1]
    x_ptr->PrevError=0;  //  Error[-2]
    x_ptr->Proportion=P;
    x_ptr->Integral=I;
    x_ptr->Derivative=D;
    x_ptr->SetPoint=0;

    y_ptr->LastError=0;  //  Error[-1]
    y_ptr->PrevError=0;  //  Error[-2]
    y_ptr->Proportion=P;
    y_ptr->Integral=I;
    y_ptr->Derivative=D;
    y_ptr->SetPoint=0;
}


//calculate the 
float control::IncPIDCalc_x(float now_x,float yaw)
{
     
    if(circle_count % 2==0)
    {
        x_ptr->SetPoint=(circle_count*2+1)*0.8-0.8*cos(yaw);
    }
    else
    {
        x_ptr->SetPoint=0.8*(circle_count*2+1)+0.8*cos(yaw);
    }
    float iError,iIncpid;
    iError=x_ptr->SetPoint-now_x;
    iIncpid=x_ptr->Proportion*iError - x_ptr->Integral*x_ptr->LastError+x_ptr->Derivative*x_ptr->PrevError;
    x_ptr->PrevError=x_ptr->LastError;
    x_ptr->LastError=iError;
    return iIncpid;
}


float control::IncPIDCalc_y(float now_y,float yaw)
{
     
    if(circle_count%2==0)
    {
        y_ptr->SetPoint=-0.8*sin(yaw);
    }
    else
    {
        y_ptr->SetPoint=0.8*sin(yaw);
    }
    float iError;
    float iIncpid;
    iError=y_ptr->SetPoint-now_y;
    iIncpid=y_ptr->Proportion*iError - y_ptr->Integral*y_ptr->LastError+y_ptr->Derivative*y_ptr->PrevError;
    y_ptr->PrevError=y_ptr->LastError;
    y_ptr->LastError=iError;
    return iIncpid;
}


//this callback function is used to get_the_position of the car
//but the callback function can't subscribe the position out of no reason
//so I use parameter server instead
void control::get_msgs(geometry_msgs::Point::ConstPtr ptr)
{
    //now_x=ptr->x;
    //now_y=ptr->y;
    
}

//  There is no need to subscribe the jointstate.
//  The reason why I subscrebe this is to guarantee the AsyncSpinner function works
void control::sub_msgs(sensor_msgs::JointState::ConstPtr ptr)
{
    
       // rate.sleep();
       ROS_INFO("subscribe successfully");
}


int main(int argc, char* argv[]) {
    ros::init(argc, argv, "add_noise");
    ros::NodeHandle nh;
    ros::Publisher pub=nh.advertise<geometry_msgs::Twist>("controlcommand",10);
    control mycontrol;
    mycontrol.IncPIDInit(); //Initiate PID struct

    //initiate subscribers to get information
    mycontrol.subscribe_and_publish_init();
    
    //use multitreads to process the data
    ros::AsyncSpinner s(2);
    s.start();
    
 
    static geometry_msgs::Twist velocit_and_yaw_msgs;
    ros::Duration du(3);
    du.sleep();
    // publish the first velocity and yaw message;
    velocit_and_yaw_msgs.linear.x=0;
    velocit_and_yaw_msgs.linear.y=-0.008;
    velocit_and_yaw_msgs.angular.z=yaw;
    pub.publish(velocit_and_yaw_msgs);
    yaw+=0.01;

    

    //publish commands
    while(ros::ok())
    {
        ros::Rate rate(20);
        rate.sleep(); 
        ros::param::get("x_v",now_x);
        ros::param::get("y_v",now_y);
        ROS_INFO("%f",now_x);
        ROS_INFO("%f",now_y);

        x_new_v=mycontrol.IncPIDCalc_x(now_x,yaw);
        y_new_v=mycontrol.IncPIDCalc_y(now_y,yaw);
        velocit_and_yaw_msgs.angular.z=yaw;
        if(-0.008<x_new_v && x_new_v<0.008)
        {
            velocit_and_yaw_msgs.linear.x=x_new_v;
        }
        else
        {
            if(x_new_v<0)
            velocit_and_yaw_msgs.linear.x=-0.008;
            else
            velocit_and_yaw_msgs.linear.x=0.008;

        }
        if(-0.008<y_new_v && y_new_v<0.008)
        {
            velocit_and_yaw_msgs.linear.y=y_new_v;
        }
        else
        {
            if(y_new_v<0)
            velocit_and_yaw_msgs.linear.y=-0.008;
            else
            velocit_and_yaw_msgs.linear.y=0.008;
        }
        pub.publish(velocit_and_yaw_msgs);
        ROS_INFO("PUBED");
        if(yaw>=3.14 | yaw<=0)
        {
            circle_count++;
        }
        if(circle_count % 2 ==0)
        {
           yaw+=0.01;
        }
        else
        {
            yaw-=0.01;
        }
    }
}
