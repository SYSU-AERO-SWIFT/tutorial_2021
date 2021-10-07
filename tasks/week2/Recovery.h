/*
* public方法、属性不可变且必须实现
* private方法、属性可自行增添
* 主函数中必须使用public方法；
*/
#ifndef RECOVERY
#define RECOVERY
#include<iostream>
#include<string>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
class Recovery {
public:
    /* readVideo
    * @param filePath 文件绝对路径
    * 根据绝对路径读取需要还原背景的文件
    */
    void readVideo(string filePath);
    /* process
    * 进行还原过程
    */
    void process();
    /* showResult
    * 窗口展示背景还原后的结果
    */
    void showResult();
private:
    VideoCapture vid;//读入的视频
    int row, col, total;//行、列、总帧数
    Mat* result;//结果图像的指针
};
#endif