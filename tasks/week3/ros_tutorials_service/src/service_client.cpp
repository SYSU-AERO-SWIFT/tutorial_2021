#include "ros/ros.h" // ROS的基本头文件
#include "ros_tutorials_service/SrvTutorial.h" // SrvTutorial服务头文件（构建后自动生成）
#include <cstdlib> // 使用atoll函数所需的库
#include<string>
using namespace std;
int main(int argc, char **argv) // 节点主函数
{
ros::init(argc, argv, "service_client"); // 初始化节点名称

ros::NodeHandle nh; // 声明与ROS系统通信的节点句柄
// 声明客户端，声明利用ros_tutorials_service功能包的SrvTutorial服务文件的
// 服务客户端ros_tutorials_service_client。
// 服务名称是"ros_tutorial_srv"
ros::ServiceClient ros_tutorials_service_client =nh.serviceClient<ros_tutorials_service::SrvTutorial>("ros_tutorial_srv");
// 声明一个使用SrvTutorial服务文件的叫做srv的服务
ros_tutorials_service::SrvTutorial srv;
while(ros::ok())
{

srv.request.a = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);


// 请求服务，如果请求被接受，则显示响应值
if (ros_tutorials_service_client.call(srv))
{string output=srv.response.result==true?"YES":"NO";
ROS_INFO("send srv, srv.Request.a :%f, %s", srv.request.a, output.c_str());

}
else
{
ROS_ERROR("Failed to call service ros_tutorial_srv");
return 1;
}
sleep(1);
}
return 0;
}