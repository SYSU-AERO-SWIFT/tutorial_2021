#include <random_data_generator_server/random_data_generator_server.h>

namespace random_data_generator_server
{

RandomDataGeneratorServer::RandomDataGeneratorServer()
{ 
  this->randomBytesRandomService = this->n.advertiseService("randombytes_random", &RandomDataGeneratorServer::randomBytesRandom, this);
}

RandomDataGeneratorServer::~RandomDataGeneratorServer()
{
}


bool RandomDataGeneratorServer::randomBytesRandom(random_data_generator_server::RandomBytesRandom::Request  &req, 
                                                  random_data_generator_server::RandomBytesRandom::Response &res)
{
  res.data = randombytes_random();
  return true;
}

}  // namespace encrypt_text_server