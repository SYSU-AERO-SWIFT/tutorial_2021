### 完成说明

#### 本周任务1、2、3

```C++
在文件夹“taskweek3”下：
talker.cpp 与 listener.cpp 对应任务1
task_client.cpp 与 task_server.cpp 对应任务3
```

#### 本周任务4、5

```C++
在文件夹”littlecar“下，不是原本的little_car，为了避免与类名little_car冲突，更换了包名。

我做了这些更改：
main.cpp中增加了小车速度信息的发布者；增加commandPub.cpp，包含对小车速度信息的订阅者，根据小车的速度信息调用相应函数得到用于发布的速度指令，创建发布者，发布速度指令，main.cpp中对指令进行订阅。
    
原本想通过加速度的方法实现小车的直线加速以及转弯，仅仅定义了car_forward函数控制小车按当前方向加速，但是运行时发现小车接收到的指令都是0，没找到原因。
```

#### 本周任务6

```C++
在文件夹task7下
我只仿照一些教程写了一个二轮驱动小车的urdf文件，在xacro文件夹下，moving_robot描述了小车的物理属性，control则给小车joint添加传动转置，控制器，integrate文件对以上两个文件进行整合。
在launch文件夹下的moving_car.launch解析并加载urdf文件到参数服务器，启动gazebo。
```









