#ifndef __CONTROL_H
#define __CONTROL_H
#include <geometry_msgs/Point.h>
#include <ros/ros.h>
#include "geometry_msgs/Twist.h"
#include <sensor_msgs/JointState.h>


typedef struct PID_STRUCT
{
    float SetPoint;            //the goal point
    double Proportion;       //P
    double Integral;         //I
    double Derivative;       //D
    float LastError;           //the error of last time
    float PrevError;           //the error of previous time
}PID;
#define P 1
#define I 1
#define D 1
class control
{
    private:
      PID x_PID;             //the PID struct of position x
      PID y_PID;             //the PID struct of position y
      PID* x_ptr=&x_PID;
      PID* y_ptr=&y_PID;
      

    public:
      ros::NodeHandle n;
      ros::Subscriber pos_sub1;
      ros::Subscriber pos_sub2;
      void IncPIDInit();
      float IncPIDCalc_x(float now_x,float yaw);
      float IncPIDCalc_y(float now_x,float yaw);
      
      void subscribe_and_publish_init()
      {
        pos_sub1=n.subscribe("position",1,&control::get_msgs,this);//get the position of the car
        pos_sub2=n.subscribe("joint_states",1,&control::sub_msgs,this);
      }
      void get_msgs(geometry_msgs::Point::ConstPtr ptr);
      void sub_msgs(sensor_msgs::JointState::ConstPtr ptr);

      //void cal_yaw_and_velocity(geometry_msgs::Point::ConstPtr ptr);
      //void pub_msgs(geometry_msgs::Point::ConstPtr ptr);

};

#endif