#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#define FRAME 210
using namespace cv;

class Recovery 
{public:
    void readVideo(String filePath); //根据绝对路径读取需要还原背景的文件
    void process(); //进行还原过程
    void showResult(); //窗口展示背景还原后的结果
    short max_index(short a[], int len); //求序列最大元素的下标 
    
private:
	VideoCapture cap;
	Mat img;
	Mat imgResize;
	Mat imgRecover(720,1280,CV_8UC3);
	int imgNum = 0;
	int row = 720;
    	int col = 1280;
	Mat sample[FRAME];
};
