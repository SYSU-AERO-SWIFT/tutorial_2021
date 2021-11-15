#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
#define FRAME 210

using namespace std;
using namespace cv;

//求序列最大元素的下标
short max_index(short a[], int len)
{
	if (len == 1) return 0;
	
	int max = 0;
	for (int i = 1; i < len; i++)
	{
		if (a[i] > a[max])
		{
			max = i;
		}
	}
	return max;
}

int main()
{
	//readVideo
	string path = "./resource/video1.mp4";
	VideoCapture cap(path);
	
	//定义process过程中所需变量
	Mat img;
	Mat imgResize;
	Mat imgRecover(720,1280,CV_8UC3);
	int imgNum = 0;
	int row = 720;
        int col = 1280;
	Mat sample[FRAME];
	
	//process
	while (true)
	{
		cap.read(img);
		if (!img.data || imgNum > FRAME-1) break;
		imgNum++;
		//修改图片分辨率
		resize(img, imgResize, Size(1280, 720));
		//保存样本
		sample[imgNum - 1] = imgResize.clone();
	}
	//遍历像素点和样本
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			//对每个像素点定义三个哈希数组用于统计三个颜色的出现次数
			short hash1[256] = {0};
			short hash2[256] = {0};
			short hash3[256] = {0};
			for (int n = 0; n < FRAME; n++)
			{
				hash1[sample[n].at<Vec3b>(i,j)[0]]++;
				hash2[sample[n].at<Vec3b>(i,j)[1]]++;
				hash3[sample[n].at<Vec3b>(i,j)[2]]++;
			}
			//将三个颜色的众数复制给imgRecover的当前像素
			imgRecover.at<Vec3b>(i,j)[0] = max_index(hash1, 256);
			imgRecover.at<Vec3b>(i,j)[1] = max_index(hash2, 256);
			imgRecover.at<Vec3b>(i,j)[2] = max_index(hash3, 256);
		}			
	}

	//showResult
	//显示结果
	//imshow("image", imgRecover);
	//waitKey(1000);
	//保存结果
	imwrite("./imgTest2_210.jpg", imgRecover);
	
	return 0;
}
