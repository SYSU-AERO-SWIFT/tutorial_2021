#pragma once

#include<iostream>
#include<string>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Recovery {
public:
void readVideo(string filePath);
void process();
void showResult();
private:
string path;
VideoCapture cap;
Mat Image;
Mat AvGrayf;
Mat Grayf;
Mat Avf;
Mat Dif;
Mat Compare;
Size Isize;
float Fcount;
};
