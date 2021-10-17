
#ifndef _RECOVERY_H_
#define _RECOVERY_H_

#include <iostream>
#include <string.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <time.h>
#include <math.h>

using namespace cv;
using namespace std;

/*
 *iBkg are used to save the pixels of previous frame 
 *c_iBkg are used to save the count of similar 
 */
extern unsigned int iBkg[4100][4100][3];
extern unsigned int c_iBkg[4100][4100][3];


class Recovery {

public:
    /* readVideo
    * @param filePath 文件绝对路径
    * 根据绝对路径读取需要还原背景的文件
    */
    void readVideo(const string& filePath);

    /* process
    * 进行还原过程
    */
    void process();

    /* showResult
    * 窗口展示背景还原后的结果
    */
    void showResult();

private:
        VideoCapture cap; // link to video
        int height,width,frame_tot; // the basic information of frame
        Mat output; // the answer
};


#endif 
