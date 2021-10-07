/*************************************************************************
	> File Name: Recovery.cpp
	> Author:ZX Xie 
	> Mail:1514806752@qq.com 
	> Created Time: 2021年09月30日 星期四 03时43分38秒
 ************************************************************************/


#include "../inc/Recovery.h"


/* readVideo
* @param filePath 文件绝对路径
* 根据绝对路径读取需要还原背景的文件
*/
void Recovery::readVideo(String filePath) {
    video = VideoCapture(filePath);
    if (!video.isOpened()) {
        cout << "could not load video file ..." << endl;
    }
}


/* process
* 进行还原过程
*/

typedef struct p{
    Vec3b rgb;
    int count;
}point;

void Recovery::process() {
    clock_t start, end;
    start = clock();
    //允许偏差范围
    int knn = 30;
    // 获取图像总帧数
    int totalFrameNumber = video.get(CV_CAP_PROP_FRAME_COUNT);
    //抽样样本数
    int samplesNumber;
    if (totalFrameNumber<30) samplesNumber = 6;
    else samplesNumber = 15;
    int skip = totalFrameNumber/samplesNumber;
    Mat frame[samplesNumber];
    video.read(frame[0]);
    Mat ans = frame[0].clone();
    ans = 0;
    int nr = frame[0].rows; //行数
    int nc = frame[0].cols; //列数乘通道数
    // 读取样本点到frame矩阵数列
    int count = 1;
    for (int i = 1; i < samplesNumber; ++i) {
        for (int j = 0; j < skip; ++j) {
            video.grab();
        }
        video.retrieve(frame[i]);
    }
    //恢复背景
    for (int i = 0; i < nr; ++i)
    for (int j = 0; j < nc; ++j) {
        vector<point> karr;
        int flag = 1;
        Vec3b bestRgb;
        int bestCount = 0;
        //统计样本内近似范围最多的点
        for (int k = 0; k < samplesNumber; ++k) {
            point p;
            //读取RGB值，存到point里
            p.rgb = frame[k].ptr<Vec3b>(i)[j];
            if (flag) {
                flag = 0;
                p.count = 1;
                karr.push_back(p);
            }
            else {
                for (int ii = 0; ii < karr.size(); ++ii) {
                    int sub = 0;
                    for (int jj = 0; jj < 3; ++jj) {
                        sub += abs(karr[ii].rgb[jj] - p.rgb[jj]);
                    }
                    //偏离值在合理范围内，跟目标值取加权均值
                    if (sub <= knn) {
                        for(int jj = 0; jj < 3; ++jj) {
                            karr[ii].rgb[jj] = (karr[ii].rgb[jj]*karr[ii].count + p.rgb[jj])/(karr[ii].count + 1);
                        }
                        karr[ii].count += 1;
                        if (karr[ii].count > bestCount) {
                            bestCount = karr[ii].count;
                            bestRgb = karr[ii].rgb;
                        }
                    }
                    //超过合理范围就新建一个点
                    else {
                        p.count = 1;
                        karr.push_back(p);
                    }
                }
            }
        }
        //统计完给ans赋值
        ans.ptr<Vec3b>(i)[j] = bestRgb;
    }
    //finish
    cout << "finish!!!\n";
    image = ans;
    //if (imwrite("result2.jpg",image)){
    //    cout << "保存成功\n";
    //}
    video.release();
    end = clock();
    cout << "Process time: " << (double)(end-start)/CLOCKS_PER_SEC << "s\n";
}

/* showResult
* 窗口展示背景还原后的结果
*/
void Recovery::showResult() {
    if( image.empty() )  // Check for invalid input
    {
        cout <<  "Could not open or find the image" << endl;
    }
    namedWindow( "show the result", WINDOW_NORMAL); // Create a window for display.
    imshow("show the result", image );                // Show our image inside it.
    waitKey(0); // Wait for a keystroke in the window
}

