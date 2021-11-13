#include <ros/ros.h>

#include <dynamic_reconfigure/server.h>
#include <dynamic_tutorials/AkiraConfig.h>

void callback(dynamic_tutorials::AkiraConfig &config, uint32_t level) {
 ROS_INFO("Reconfigure Request: %f ", 
           config.num);
}

int main(int argc, char **argv) 
{
   ros::init(argc, argv, "dynamic_reconfigure_node");

   dynamic_reconfigure::Server<dynamic_tutorials::AkiraConfig> server;
   dynamic_reconfigure::Server<dynamic_tutorials::AkiraConfig>::CallbackType f;

   f = boost::bind(&callback, _1, _2);
   server.setCallback(f);

   ROS_INFO("Spinning node");
   ros::spin();
   return 0;
}
