/*
* public方法、属性不可变且必须实现
* private方法、属性可自行增添
* 主函数中必须使用public方法；
*/
#pragma once
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<vector>

using namespace std;
using namespace cv;

class Recovery {
public:
    /* readVideo
    * @param filePath 文件绝对路径
    * 根据绝对路径读取需要还原背景的文件
    */
    void readVideo(String filePath);


    /* process
    * 进行还原过程
    */
    void process();



    /* showResult
    * 窗口展示背景还原后的结果
    */
    void showResult();

private:
VideoCapture capture;//读取视频的变量
vector<Mat> frames;//存放帧的向量
int height = ;//画面的高度
int width = ;//画面的宽度
int fps = ;//视频的帧率
int count ;//计数器
int framenum ;//记录帧的总数


};















