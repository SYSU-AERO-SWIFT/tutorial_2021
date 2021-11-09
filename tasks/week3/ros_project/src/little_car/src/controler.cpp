#include <geometry_msgs/Twist.h>
#include <ros/ros.h>

struct vector_hold
{
    float x; float y; float z;
} ;

// 全局变量
vector_hold g_car_vel = {0,0,0};
vector_hold g_cmd_vel = {0,0,0};

void myCallback1(const geometry_msgs::TwistConstPtr data_holder1)
{
        g_car_vel.x = (data_holder1->linear).x;
        g_car_vel.y = (data_holder1->linear).y;
        g_car_vel.z = 0;
}

void myCallback2(const geometry_msgs::TwistConstPtr data_holder2)
{
        g_cmd_vel.x = (data_holder2->linear).x;
        g_cmd_vel.y = (data_holder2->linear).y;
        g_cmd_vel.z = 0;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "controler");
    ros::NodeHandle nh;

    // 订阅小车当前速度“car_vel”
    ros::Subscriber my_subscribe_object1 = nh.subscribe<geometry_msgs::Twist>("car_vel", 1, myCallback1);
    // 订阅小车目标速度  “cmd_vel”
    ros::Subscriber my_subscribe_object2 = nh.subscribe<geometry_msgs::Twist>("cmd_vel", 1, myCallback2);
    // 发布到“cmd_acc”的发布者
    ros::Publisher my_publish_object = nh.advertise<geometry_msgs::Twist>("cmd_acc",1);

    // 向“cmd_acc”发布的间隔时间
    float dt = 0.1; 
    ros::Rate loop_rate(10);

    // 定义速度差
    vector_hold dif_vel = {0,0,0};
   // 定义用于发布的加速度
    geometry_msgs::Twist acc2pub;
    // 定义系数k
     float k = 1.0;
    while(ros::ok())
    {
            // 计算速度差
            dif_vel.x = g_cmd_vel.x - g_car_vel.x;
            dif_vel.y = g_cmd_vel.y - g_car_vel.y;
            dif_vel.z = 0;
            // 计算加速度
            acc2pub.linear.x = k * dif_vel.x;
            acc2pub.linear.y = k * dif_vel.y;
            acc2pub.linear.z = k * dif_vel.z;

            my_publish_object.publish(acc2pub);

            ros::spinOnce();
            loop_rate.sleep();
    }

    return 0;
}