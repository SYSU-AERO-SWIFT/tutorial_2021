/*************************************************************************
	> File Name: test_pub.cpp
	> Author:ZX Xie 
	> Mail:1514806752@qq.com 
	> Created Time: 2021年10月17日 星期日 02时05分01秒
 ************************************************************************/

#include<cstdlib>
#include<ros/ros.h>
#include<learning_topic/test.h>

using namespace ros;

int main(int argc, char** argv){
    init(argc,argv,"test_pub");
    NodeHandle n;
    Publisher test_pub = n.advertise<learning_topic::test>("test_info",5);
    Rate loop_rate(1);//循环频率

    while(ok()){
        learning_topic::test t;
        t.ranNum = std::rand();
        ROS_INFO("send:%d",t.ranNum);
        test_pub.publish(t);
        loop_rate.sleep();
    }
    return 0;
}
