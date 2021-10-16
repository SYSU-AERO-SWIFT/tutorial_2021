#include <random_data_generator_server/random_data_generator_server.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "random_data_generator_server_node");

  random_data_generator_server::RandomDataGeneratorServer s;
  ROS_INFO("Ready!");
  ros::spin();

  return 0;
}