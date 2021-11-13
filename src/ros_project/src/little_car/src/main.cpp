#include "parser.h"
#include <urdf/model.h>
#include <string>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Point.h>
#include <ros/ros.h>
#include <random>
#include <iomanip>
#include <akira_msgs/Akiramsg.h>
using namespace std;
void msgCallback(const akira_msgs::Akiramsg::ConstPtr& msg)
	{

  
  std::vector<float> array = msg->speed;
  float Yaw = msg->Yaw;
  velocity={msg->speed[0],msg->speed[1],msg->speed[2]};
  yaw=msg->Yaw;

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
	/*



  ros::init(argc,argv,"test1");
  ros::NodeHandle n;


	
	 *若有需要，也可以从小车处发布你所需要的信息
	 */
	  ros::Subscriber msg_sub = n.subscribe("akira_msgs", 100, msgCallback);
  little_car::set_velocity(velocity)
  little_car::set_yaw(yaw)
  ros::spin();
  return 0; 
	 
	 
    ros::Rate loop_rate(60);
	SVector3 velocity={0,0.008,0};  //速度向量
	car.set_noise_level(0);		   //设置噪声等级
	float yaw = 0.0;
    while (ros::ok()) {
	//	yaw += 0.01;
	//	car.set_yaw(yaw); 		   //修改小车的方向
		car.set_velocity(velocity);//设置小车速度
        car.update_();//小车状态更新
		loop_rate.sleep();
    }


    return 0;
}

