 #include <opencv2/opencv.hpp>
#include <iostream>
#include <random>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;
using namespace cv;
class Recovery
{
public:

    clock_t startTime, endTime;
    vector<Mat> frames;
    Mat frame, medianFrame;
    VideoCapture cap;
    void readVideo(String filePath);



    static int computeMedian(vector<int> elements);

   


    void process();

    void showResult();
private:
//如果要改可以根据障碍动的速度调节随机选出来的帧数，我选了50帧，如果动得快或者障碍不是纯色（比较斑斓）可以调低一点（毕竟无人机应该挺快的）
};
