/*************************************************************************
	> File Name: test_client.cpp
	> Author:ZX Xie 
	> Mail:1514806752@qq.com 
	> Created Time: 2021年10月17日 星期日
 ************************************************************************/
#include <cstdlib>
#include <time.h>
#include <ros/ros.h>
#include <learning_service/serve.h>

using namespace ros;

int main(int argc, char **argv){
    // ROS节点初始化
    init(argc, argv, "test_client");
    // 创建节点句柄
    NodeHandle n;
    // 创建一个client
    ServiceClient client = n.serviceClient<learning_service::serve>("learning_service");
    // 创建service消息
     learning_service::serve C;
    std::srand((unsigned)std::time(0));
    Rate loop_rate(1);//循环频率
    while(ok()){
        C.request.num= float_t(std::rand() % 1000000) / 1000000.0;
        // 发布service请求，等待加法运算的应答结果
        if (client.call(C)){
            if(C.response.reply) ROS_INFO("%f  YES", C.request.num);
            else ROS_INFO("%f  NO", C.request.num);
        }
        loop_rate.sleep();
    }
    return 0;
}
