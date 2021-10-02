#include "background_recovery.h"
using namespace cv;
using namespace std;

struct pix
{
    int colors;
    int times;
};
vector<pix> m[4000][5000];
int num[4000][5000];

void Recovery::readVideo(string filePath){

    capture.open(filePath);
    capture.read(frame);
    if (!capture.isOpened())
    {
        cout << "Fail to open file!\n";
        return ;
    }
}
void Recovery:: process(){
    std::chrono::steady_clock::time_point _curTimePoint = std::chrono::steady_clock::now();
    int rows = frame.rows;
    int cols = frame.cols;
//    imshow("output", frame);
 //   int num[rows][cols];
    ans = frame.clone();
    Mat init = frame.clone();
    int cnt = 0;
    while (capture.read(frame))
    {
        cnt++;
        if (cnt % 2 == 0)
        {
            continue;
        }
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                int tmp = frame.at<int> (i,j);
                int bl = 1;
                for (int k = 0; k < m[i][j].size(); ++k)
                {
                    if (tmp == m[i][j][k].colors)
                    {
                        bl = 0;
                        m[i][j][k].times++;
                        break;
                    }
                }
                if (bl)
                {
                    pix t;
                    t.colors = tmp;
                    t.times = 1;
                    m[i][j].push_back(t);
                }
            }
        }


    }
    //cout << frame.at<Vec3b>(1,1)[0] << " " <<frame.at<Vec3b>(1,1)[1] << " " << frame.at<Vec3b>(1,1)[2] << endl;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols - 60; ++j)
        {
            //cout << m[i][j].size() << "\t";
            pix tmp;
            tmp.times = 0;
            for (int k = 0; k < m[i][j].size(); ++k)
            {
                if (m[i][j][k].times > tmp.times)
                {
                    tmp.times = m[i][j][k].times;
                    tmp.colors = m[i][j][k].colors;
                }
            }
            //cout << i << " " << j << "\n";
            //cout << tmp.colors << "\n";
            if (tmp.colors == 0)
            {
                tmp.colors = init.at<int>(i,j);
            }
            ans.at<int>(i,j) = tmp.colors;
        }
        //cout << endl;
    }
    cv::imwrite("result/result.jpg",ans);
    capture.release();
    auto curTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(curTime - _curTimePoint);
    cout<<  duration.count() <<"s"<<endl;

}
void Recovery::showResult(){
    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", ans );
    
    waitKey(0);
}