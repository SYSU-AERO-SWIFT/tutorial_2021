#ifndef _RANDOM_DATA_GENERATOR_SERVER_
#define _RANDOM_DATA_GENERATOR_SERVER_

#include "ros/ros.h"
#include "random_data_generator_server/RandomBytesRandom.h"
#include "sodium.h"

namespace random_data_generator_server
{
    class RandomDataGeneratorServer
    {
        public:
        RandomDataGeneratorServer();
        ~RandomDataGeneratorServer();

        private:
        
        ros::NodeHandle n;
        ros::ServiceServer randomBytesRandomService;
        bool randomBytesRandom(random_data_generator_server::RandomBytesRandom::Request  &req, 
                               random_data_generator_server::RandomBytesRandom::Response &res);
    };
}


#endif