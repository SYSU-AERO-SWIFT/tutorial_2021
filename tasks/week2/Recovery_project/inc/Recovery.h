#pragma once

#include<iostream>
#include<string>
#include<opencv.hpp>

using namespace std;
using namespace cv;

class Recovery {
public:
void readVideo(string filePath);
void process();
void showResult();
private:
string path; //视频路径
VideoCapture cap; //
Mat Image; //当前帧
Mat PreImage; //上一帧
Mat tmpAvDif; //当前的帧差分绝对值
Mat AvDif; // 平均的帧差分绝对值
Mat AvGrayDif; // AvDif的灰度矩阵
Mat Avf; // 帧的和的平均
Mat AvGrayf; // Avf的灰度矩阵
Mat Grayf; // Process函数中读取的当前帧的灰度矩阵
Mat Imask; // inRange生成的掩模
Mat HighBorder; // 上边界
Mat LowBorder; // 下边界
Size Isize; // 处理过程中图片的尺寸
float Fcount; // VideoCapture中对帧的计数
};
