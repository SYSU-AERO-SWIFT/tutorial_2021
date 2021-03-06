# 图像处理方向项目
## 项目内容

1. 学习图像处理相关算法
2. 学习基本点云处理
3. 学会使用ROS

## 注意
- **本项目的样例数据和示例资源非常大，请从百度网盘下载**：
  
  链接：

  [项目资源网盘](https://pan.baidu.com/s/1gv--hs9_pGmRkF-CSpwdnQ)

  提取码：pvpt


- 本项目的数据均在仿真平台上采集，环境相对理想
- 采集使用Realsense深度摄像头，**视野范围较小，采集到的图像存在部分空缺（超出最大可视距离）**
- 设计的算法应该具有一定的光照鲁棒性，可以适应一定程度的光照变化和光照不均匀
- 本项目预先将测试用的样例数据存储在ROS Bag当中。


## 基本任务：目标检测
### 任务说明
编写一个ROS节点，实现如下功能：

1. 订阅`/iris_0/realsense/depth_camera/color/image_raw`话题实时获得摄像机输入的彩色图像
2. 从图像中定位给定目标，并计算目标检测框
3. 将目标检测框发布到一个话题中
4. 对摄像机输入的图像以及目标检测结果做可视化

摄像机图像与可视化结果参考项目资源中的`origin.mp4`和`detect.mp4`。

样例输入参考`detect_video.bag`。

**注意：以上视频供参考，任务目标不是读取这两个视频，而是通过订阅话题来获得摄像机实时采集的图像。正确使用样例数据调试的方法参见“使用样例数据”小节**

### 待检测目标
要检测的目标的正面图像如下：

![sign_sample](https://github.com/SYSU-AERO-SWIFT/tutorial_2021/blob/main/pic.github/sign_sample.png)

你可以在项目资源中找到这张图片（sign_sample.png）。

关于目标图像的说明：
- 要识别的只有目标的标识牌的主体部分，不包含下方支撑的杆子
- 由于光照问题，图像的色彩仅供参考

### 关于检测方法

不限制检测的思路，可以考虑以下的一些思路：
- 色彩
- 模板匹配
- 目标检测网络（如YOLO）

使用深度学习方法可酌情加分

### 使用样例数据

考虑到大家没有条件自己使用摄像头采集，这里提供了预先录制的ROS Bag包含摄像头采集的数据。

使用如下命令重放录制的图像数据：

`rosbag play detect_video.bag`

Bag包包含的话题使用如下命令查看：

`rosbag info detect.bag`

### IoU

IoU 的全称为交并比（Intersection over Union）。

IoU 计算的是 “预测的边框” 和 “真实的边框” 的交集和并集的比值。

在目标检测任务中使用全过程中平均算法的IoU指标来评价性能。

### 提交要求
提交内容只需要包含一个**完整ROS包**，里面包含你编写的节点，以及一个README文件。

**请在README文件说明你发布检测框的话题的名称**

### 评分标准

本任务要求算法具有实时性能，单帧处理耗时过长会酌情扣分。

本项目鼓励使用深度学习，使用深度学习解决的可酌情加分

|          评分大项          | 评分小项 |          分值           |
| :------------------------: | :------: | :-----------------------: |
|         编写ROS节点并显示从摄像机采集到的图像        |          | 20 |
| 计算目标检测框并发布到话题 | | 20|
| 显示目标检测框 | | 5 |
| 平均IoU | IoU < 0.5 | 0 |
| | 0.5 <= IoU < 0.8 | 30 |
| | IoU >= 0.8 | 30 + 25 |
| 单帧处理耗时 | 不超过1s | 0 |
| | 1~2s | -10 |
| | > 2s | 本任务得分*0.5 |
| 使用深度学习 | 0.5 < IoU <= 0.8 | 本任务得分+10 | 
| |  IoU > 0.8 | 本任务得分*1.4 | 

## 拓展任务：目标位姿判定
### 任务说明

任务九中主要视觉任务是利用多种传感器来确定目标的姿态（目标摆放朝向）。

编写一个ROS节点，实现如下功能：

1. 从ROS话题中订阅获得所需的信息
2. 判定目标所在的空间坐标
3. 判定目标的姿态（欧拉角表示）
4. 在判明目标姿态的基础上，确定标识牌上字母“P”的孔的空间坐标

参考视频见项目资源中的`pose.mp4`。

样例数据存放在项目资源中的`pose.bag`。

可供订阅的话题列表在下一节说明。

### 参考思路
- 点云匹配
- SLAM
- 深度学习

### 样例数据

考虑到大家手上没有无人机采集完整的数据，项目已经来录制了一些需要的数据。

使用如下命令重放录制数据：

`rosbag play pose.bag`

话题列表：
- `/iris_0/realsense/depth_camera/color/image_raw` RGB彩色图像数据
- `/iris_0/realsense/depth_camera/depth/points` 点云数据
- `/mavros/local_position/pose` 无人机位姿数据

Bag包包含话题列表使用如下命令查看：

`rosbag info pose.bag`

### 关于位置
**话题提供的位置数据不能直接使用，因为摄像头坐标与无人机自身坐标存在定值偏移，具体信息请向考核负责人索要**

### 更多细节

本任务更多具体信息请向考核负责人索要。

### 提交要求
- 一个完整ROS包，包含三个节点，用户完成给出的三个子任务
- README文件，说明计算结果发布的话题

### 评分标准

更详细的评分细则可以咨询考核负责人。

|          评分大项          | 评分小项 |          分值           |
| :------------------------: | :------: | :-----------------------: |
|         判定目标空间坐标        |          | 60 |
| 判定目标姿态 | | 40|
| 判定“P”小孔坐标 | | 50 |
