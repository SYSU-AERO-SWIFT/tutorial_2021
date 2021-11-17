#include "parser.h"
#include <urdf/model.h>
#include <string>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Point.h>
#include <ros/ros.h>
#include <random>
#include <iomanip>
using namespace std;
using namespace ros;
typedef struct
{
    float target_val;   //目标值
    float err;          //偏差值
    float err_last;     //上一个偏差值
    float Kp,Ki,Kd;     //比例、积分、微分系数
    float integral;     //积分值
    float output_val;   //输出值
}PID;
PID pid;

float PID_realize(float actual_val)
{pid.err=pid.target_val-actual_val;
pid.integral +=pid.err;
pid.output_val=pid.Kp*pid.err+pid.Ki*pid.integral+pid.Kd*(pid.err-pid.err_last);
return pid.output_val;
}

vector<float> vec;
void callback(const geometry_msgs::Vector3& info)
{ vec.push_back(info.x);
 vec.push_back(info.y);
 vec.push_back(info.z);

}

int main(int argc, char** argv) {
	
    
    ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;
	little_car car;//初始化控制对象  小车
    car.joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
	car.pos_pub = n.advertise<geometry_msgs::Point>("car_position",1); //小车的位置消息发布
	
	/* 
	 *请添加一个Subscriber，从你自己编写的Publisher处订阅指令
	 */
    Subscriber car_sub=n.subscribe("car_control",10,callback);
	/*
	 *若有需要，也可以从小车处发布你所需要的信息
	 */
    ros::Rate loop_rate(10);
	SVector3 velocity={0,0,0};  //速度向量
	car.set_noise_level(0);		   //设置噪声等级
	float yaw = 0.0;
    while (ros::ok()) 
	{ spinOnce();
	
	
	if(vec.size()>=3)
	{
	velocity.x=vec[0];
	velocity.y=vec[1];
	yaw=vec[2];
	
	car.set_yaw(yaw); //修改小车的方向
	car.set_velocity(velocity);//设置小车速度
	vec.clear();
	car.update_();//小车状态更新
	}
		
   
	loop_rate.sleep();
    }


    return 0;
}