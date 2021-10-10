#include "parser.h"
#include <urdf/model.h>
#include <string>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Point.h>
#include <ros/ros.h>
#include <random>
#include <iomanip>
#include <math.h>
#include "std_msgs/Float32MultiArray.h"

//PID struct

typedef struct PID
{
    int SetPoint;
    double Proportion;
    double Integral;
    double Derivative;
    int LastError;
    int PrevError;
}PID;
float yaw=0.0;
std_msgs::Float32MultiArray msg;

#define P 100
#define I 0.6
#define D 1
static PID x_PID,y_PID;
static PID* x_ptr=&x_PID;
static PID* y_ptr=&y_PID;

void IncPIDInit()
{
    x_ptr->LastError=0;//Error[-1]
    x_ptr->PrevError=0;//Error[-2]
    x_ptr->Proportion=P;
    x_ptr->Integral=I;
    x_ptr->Derivative=D;
    x_ptr->SetPoint=0;

    y_ptr->LastError=0;//Error[-1]
    y_ptr->PrevError=0;//Error[-2]
    y_ptr->Proportion=P;
    y_ptr->Integral=I;
    y_ptr->Derivative=D;
    y_ptr->SetPoint=0;
}

float IncPIDCalc_x(float now_x,float yaw)
{
     
    if(0<yaw<3.14)
    {
        x_ptr->SetPoint=0.5*cos(yaw)-0.5;
    }
    else
    {
        x_ptr->SetPoint=-0.5*cos(yaw)+1.5;
    }

    double iError,iIncpid;
    iError=x_ptr->SetPoint-now_x;
    iIncpid=x_ptr->Proportion*iError - x_ptr->Integral*x_ptr->LastError+x_ptr->Derivative*x_ptr->PrevError;
    x_ptr->PrevError=x_ptr->LastError;
    x_ptr->LastError=iError;
    return iIncpid;
}

float IncPIDCalc_y(float now_y,float yaw)
{
     
    if(0<yaw<3.14)
    {
        y_ptr->SetPoint=0.5*sin(yaw);
    }
    else
    {
        y_ptr->SetPoint=0.5*sin(yaw);
    }

    double iError,iIncpid;
    iError=y_ptr->SetPoint-now_y;
    iIncpid=y_ptr->Proportion*iError - y_ptr->Integral*y_ptr->LastError+y_ptr->Derivative*y_ptr->PrevError;
    y_ptr->PrevError=y_ptr->LastError;
    y_ptr->LastError=iError;
    return iIncpid;
}



void cal_yaw_and_velocity(geometry_msgs::Point::ConstPtr& ptr)
{
    msg.data[0]=IncPIDCalc_x(ptr->x,yaw);
    msg.data[1]=IncPIDCalc_y(ptr->y,yaw);
    yaw++;
    if(yaw>6.28)
    {
        yaw=0;
    }
    
}

int main(int argc, char** argv) {
    
    
    ros::init(argc, argv, "command_noise");
    ros::NodeHandle n;
    IncPIDInit();
    ros::Publisher v_pub=n.advertise<std_msgs::Float32MultiArray>("velocity",100);

    ros::Subscriber pos_sub=n.subscribe("car_position",100,cal_yaw_and_velocity);
    ros::Rate loop_rate(20);
    
    while(ros::ok())
    {
        v_pub.publish(msg);   
        loop_rate.sleep();
    }
    
    ros::spin();

    
    
   
        
        
       
        
    ros::spin();
}
