# 项目说明

## 梗概
我们希望你能创建一个基于ROS的系统，对任务7的场景进行仿真。在比赛场地内有10台移动机器人，4台障碍机器人，移动机器人相碰撞会导致其运动方向旋转180度，移动时间超过二十秒也会导致运动方向转向180度，障碍机器人在场地内做圆周运动。你有一台无人机，无人机有两种碰撞移动机器人的方式，触碰移动机器人顶部会导致移动机器人顺时针旋转45度，在移动机器人前方降落后与其碰撞将导致移动机器人旋转180度。无人机的目标是将尽可能多的地面机器人驱赶出场地。  
更多信息请看[任务7详细规则](https://wenku.baidu.com/view/4333d4e780eb6294dd886c50.html)

## 具体要求
- 采用ROS多模块实现地面机器人，无人机，场地，传感器（摄像头以及全向雷达）
- 无人机不能直接获取地面机器人的坐标，只能通过摄像头节点获取无人机周围半径3m内的地面机器人相对于无人机的距离。
- 无人机的下降触碰和前方降落碰撞可以简化为2种触发模式
- 无人机的速度不超过3 m/s，场地大小为 20mx20m，地面机器人移动速度为0.33m/s且地面机器人自身的移动轨迹有噪声，具体参数看任务7详细规则第18页
- 用opencv(二维平面)或者rviz(三维立体)显示出来

## 评分标准
| 评分项                        | 分值 |
| ----------------------------- | ---- |
|实现了移动机器人运动的仿真 | 20 |
|实现了无人机的仿真（包括传感器）|25|
|用opencv/rviz显示出来|25~40|
|能够将地面机器人驱赶出场地|20～30|

## 评分说明
- 主要考察利用ROS搭建一个完整系统的能力
- 能够将地面机器人驱赶出场地即可获得20分，能够将更多的地面机器人驱赶出去将有更高的分数
- 考虑到同学们的虚拟机可能带不动gazebo，因此没有要求用gazebo做仿真，但如果你能使用gazebo做仿真，将`适当加分`
