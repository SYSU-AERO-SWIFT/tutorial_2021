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





   

    int main(int argc, char **argv)
   {
     /**
      
       the easiest way to do it.  The third argument to init() is the name of the node.
	**/
     ros::init(argc, argv, "talker");
     
  ros::NodeHandle n;
  ros::Publisher akira_msgs_pub = n.advertise<akira_msgs::Akiramsg>("akira_msgs", 1000);
  ros::Rate loop_rate(10);
  int count = 0;

  while (ros::ok())
  {
    akira_msgs::Akiramsg msg;
    

    //用vector给float32[]数组赋值
    float array[3] = {0.008,0,0};
    std::vector<float> array1(array);
    	msg.speed=array1;
    
	msg.Yaw=1.57;
    std::cout << std::endl;

    akira_msgs_pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }

  return 0;
}
