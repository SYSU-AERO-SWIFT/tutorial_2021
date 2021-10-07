/*************************************************************************
	> File Name: Recovery.h
	> Author:ZX Xie 
	> Mail:1514806752@qq.com 
	> Created Time: 2021年10月03日 星期日 09时12分15秒
 ************************************************************************/

#ifndef _RECOVERY_H
#define _RECOVERY_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <map>
#include <cmath>
#include <ctime>

using namespace cv;
using namespace std;

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
    VideoCapture video; //存放读取的视频流
    Mat image;         //存放还原背景图片
};


#endif
