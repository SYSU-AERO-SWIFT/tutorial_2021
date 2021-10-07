## Readme

- Author:赵子健
- Revised:赵子健
- Data:2021-10-04
- Version：2.0.0
- Abstract:第二周背景还原任务说明

### Functions

利用平均值法还原视频背景，这种方法还原视频总帧数大的效果比较好，在操作后发现video0还原效果较好、而video1、2还原效果不是很好

### Interfaces

- void Recovery::readVideo(string filePath); 读入视频

- void Recovery::process(); 利用平均值法对视频进行背景还原操作，并在命令行输出操作时间

- void Recovery::showResult(); 显示处理后的背景图像

### Depend Libraries

- openCV

- g++

### how to compile

执行makefile文件

### how to run

./recovery <视频路径>

### the result if it is running well 

Open successfully.

Execution time:运行时间s