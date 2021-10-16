#include "stdint.h"
#include "ros/ros.h"
#include "random_data_generator_server/RandomBytesRandom.h"

using namespace std;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "client");

  ros::NodeHandle n;
  ros::ServiceClient client  = n.serviceClient<random_data_generator_server::RandomBytesRandom>("randombytes_random");
  
  random_data_generator_server::RandomBytesRandom srv;

  if (client.call(srv))
  {
    uint32_t r = srv.response.data;
    ROS_INFO("RandomBytes Random: 0x%X", r);
  }
  else
  {
    ROS_ERROR("Failed to call service");
    return 1;
  }


  return 0;
}
