/*************************************************************************
	> File Name: test_sub.cpp
	> Author:ZX Xie 
	> Mail:1514806752@qq.com 
	> Created Time: 2021年10月17日 星期日 02时17分36秒
 ************************************************************************/

#include<learning_topic/test.h>
#include<ros/ros.h>

using namespace ros;

void infocallback(const learning_topic::test::ConstPtr& msg){
    ROS_INFO("receive:%d",msg->ranNum);
}

int main(int argc, char** argv){
    init(argc,argv,"test_sub");
    NodeHandle n;
    Subscriber test_sub = n.subscribe("test_info",5,infocallback);
    spin();
    return 0;
}
