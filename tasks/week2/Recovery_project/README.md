#### 考核项目 Background recovery 说明文档

##### 	基本信息

- 作者：杨诺萁  

- 创建日期：21/10/3

- 版本：1.0.0

- 简介：编写Recovery类，在理想情况下提取视频的背景

  ***

  ##### 基本功能与接口

  1. 读取视频文件 void VideoCapture(string filePath)

  2. 处理视频文件得到背景 void Process()

  3. 显示提取到的背景 void show() 

     * 接口示例：

     Recovery test; //declare

     test.VideoCapture(someString); //Read video

     test.Process(); //Get background

     test.show(); //Show result

     *****

     ##### 编译与执行

     * 示例：

     $ make //编译

     $ ./bin/test1 ./resource/video0.mp4 //执行

     

     

  



