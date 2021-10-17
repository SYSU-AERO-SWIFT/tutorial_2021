#include "ros/ros.h"
#include "service_and_client/Mysrv.h"

bool compare(service_and_client::Mysrv::Request &req,service_and_client::Mysrv::Response &res)
{
    if(req.num<0.5)
      res.response=1;
    else
      res.response=0;
    return true;
}
int main(int argc,char** argv)
{
    ros::init(argc,argv,"service_server");
    ros::NodeHandle nh;
    ros::ServiceServer server =nh.advertiseService("float_number",compare);
    ros::spin();
    return 0;
}