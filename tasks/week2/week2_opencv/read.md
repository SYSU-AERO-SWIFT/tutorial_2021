## 项目说明文档

### 基本信息

- 作者：方旭

- 创建日期：21/10/2


- 简介：编写Recovery类，一定程度上还原视频的静态背景

  ***

##### 基本功能与接口

  1. 读取视频文件 void VideoCapture(string filePath)

  2. 处理视频文件得到背景 void Process()

  3. 显示提取到的背景 void show() 

     * 类的接口示例：
   
     1.Recovery recovery        创建一个Recovery类对象   
     2.recovery.readVideo("视频路径")   读取视频                 
     3.recovery.process();                   还原视频背景并计时       
     4.recovery.showResult();                      展示还原结果             

      

      

 

##### 编译与执行

     命令行示例：
     $ cd week2_opencv//转到相应目录

     $ make //编译

     $ ./bin/demo ./resource/video0.mp4 //执行video0.mp4的还原
     
     
     ps:本人虚拟机的opencv无法正常使用imshow，在代码中已经注释掉，若要使用，请重新编译
     

