#week3 说明

##Publisher与Subscriber
1.对应工具包名字为learning_topic
2.工具包内有节点person_publisher1，person_subscriber1,以及自定义消息类型Person
3.启动方式：$ roslaunch learning_topic topic.launch

##service与client
1.对应工具包名字为ros_tutorials_service
2.工具包内有节点service_server与service_client，自定义的服务类型SrvTutorial
3.启动方式为：  $rosrun ros_tutorials_service service_server 
              $rosrun ros_tutorials_service service_client


##little_car
1.对应工具包名字为little_car
2.只实现了让小车在0噪声情况下走s型曲线的任务
3.启动方式为：$roslaunch little_car little_car.launch
