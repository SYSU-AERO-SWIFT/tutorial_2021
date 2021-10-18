1、**编写一个 package，其中包含一个信息发布节点 `Publisher`，和一个信息订阅节点 `Subscriber`。信息发布节点产生随机数据并发布，要求使用自己创建的自定义消息类型，信息订阅节点订阅话题并将数据输出到终端。**



完成于catkin_wk3文件夹内的learning_topic



2、**编写 ROS launch 文件并用 `roslaunch` 启动节点。**

​完成于learning_launch

​	topic.launch: 用于启动任务一    roslaunch learning_lanch topic.launch 

​	service.launch:用于启动任务二   roslaunch learning_lanch service.launch

3、**编写 `Service` 和 `Client`，`Client` 产生一个 0 到 1 内的随机浮点数，然后发给 `Service`，`Service` 接受到请求后，判断随机数是否小于 0.5，若是则回应布尔值 1，否则回应 0。`Client` 接收到回应后，先输出产生的随机数，然后输出 `Yes` 或 `No` 到终端。**



完成于catkin_wk3文件夹内的learning_service


**提交时请使用 `.gitignore` 忽略追踪中间文件（`build/`、`devel/`等）。**



参考资料：

ROS自定义msg类型及使用：https://blog.csdn.net/qq_36355662/article/details/62226935?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522163452391116780262560049%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=163452391116780262560049&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-1-62226935.first_rank_v2_pc_rank_v29&utm_term=std_msgs&spm=1018.2226.3001.4187



ROS service in roscpp 通信 （简介+实例+测试）：https://blog.csdn.net/qq_32761549/article/details/100013748?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522163447389416780274199673%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=163447389416780274199673&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v1~rank_v31_ecpm-7-100013748.first_rank_v2_pc_rank_v29&utm_term=ros+service&spm=1018.2226.3001.4187



ROS中编写Publisher和Subscriber的方法（C++版）：https://blog.csdn.net/zong596568821xp/article/details/78704956?ops_request_misc=&request_id=&biz_id=102&utm_term=ros%20subscriber&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-1-78704956.first_rank_v2_pc_rank_v29&spm=1018.2226.3001.4187



ROS launch用法：https://blog.csdn.net/X_SANSHAO/article/details/89478455?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522163446945916780265482870%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=163446945916780265482870&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-2-89478455.first_rank_v2_pc_rank_v29&utm_term=ROS+launch+&spm=1018.2226.3001.4187


