#include "ros/ros.h"
   
    #include <akira_msgs/Akiramsg.h>   
   
 int main(int argc, char **argv)
   {
     /**
      
       the easiest way to do it.  The third argument to init() is the name of the node.
	**/
     ros::init(argc, argv, "talker");
     
  ros::NodeHandle n;
  ros::Publisher akira_msgs_pub = n.advertise<akira_msgs::Akiramsg>("akira_msgs", 1000);
  ros::Rate loop_rate(10);
  int count = 0;

  while (ros::ok())
  {
    akira_msgs::Akiramsg msg;
    std::cout << "msg.data.size=" << msg.data.size() << std::endl;

    //用vector给float32[]数组赋值
    float array[3] = {rand(),rand(),rand()};
    std::vector<float> array1(array,array+3);
    msg.data = array1;
    std::cout << "msg.data3[0]=" << msg.data[0] << std::endl;
    std::cout << "msg.data3.size=" << msg.data.size() << std::endl;

    //下标访问float32[]数组
    msg.data[0] = rand();
    std::cout << "msg.data3[0]=" << msg.data[0] << std::endl;


    float array4[4] = {rand(),rand(),rand(),rand()};
    std::vector<float> array41(array4,array4+4);
    msg.data = array41;
    std::cout << "msg.data4.size=" << msg.data.size() << std::endl;
    std::cout << "msg.data4=" << msg.data[0] << " " << msg.data[1] <<  " " << msg.data[2] << " " <<  msg.data[3] << std::endl;

    msg.data.push_back(5.5);
    std::cout << "msg.data[5]=" << msg.data[4] << std::endl;

    //使用迭代器
    msg.data.resize(6);
    std::cout << "msg.data6.size=" << msg.data.size() << std::endl;
    std::cout << "msg.data6=" ;
    for(std::vector<float>::iterator it = msg.data.begin(); it != msg.data.end(); ++it)
    {
      *it = 0.6;
      std::cout << *it << " ";
    }
    std::cout << std::endl;

    akira_msgs_pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }

  return 0;
}






   









