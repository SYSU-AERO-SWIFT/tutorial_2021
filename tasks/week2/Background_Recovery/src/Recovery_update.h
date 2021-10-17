#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

#include <vector>
using namespace std;
using namespace cv;

/*
* public方法、属性不可变且必须实现
* private方法、属性可自行增添
* 主函数中必须使用public方法；
*/
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

    void InitImages(Mat &init_image);

    void Accumulate_background();

    void createModelsfromStats();

    void setHighThreshold(float high);

    void setLowThreshold(float low);

    void backgroundDiff();

    void DeallocateImage();

    //void Mat_addition(Mat& fst, Mat& snd);
  
private:
    VideoCapture capture;
    Mat image_recovery,frame;
    Mat IavgF, IdiffF, IprevF, IhiF, IlowF;
    Mat Iscratch, Iscratch2;
    float Icount;
    
};


