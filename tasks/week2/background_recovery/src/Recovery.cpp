#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string.h>
#include <iostream>
#include "Recovery.h"
#define FRAME 210

using namespace std;
using namespace cv;

void Recovery::readVideo(String filePath)
{
	cap = VideoCapture(filePath);
}

void Recovery::process()
{
	while (true)
	{
		cap.read(img);
		if (!img.data || imgNum > FRAME-1) break;
		
		imgNum++;
		resize(img, imgResize, Size(1280, 720));
        sample[imgNum - 1] = imgResize.clone();
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			short hash1[256] = {0};
			short hash2[256] = {0};
			short hash3[256] = {0};
			
			for (int n = 0; n < FRAME; n++)
			{
				hash1[sample[n].at<Vec3b>(i,j)[0]]++;
				hash2[sample[n].at<Vec3b>(i,j)[1]]++;
				hash3[sample[n].at<Vec3b>(i,j)[2]]++;
			}
			imgRecover.at<Vec3b>(i,j)[0] = max_index(hash1, 256);
			imgRecover.at<Vec3b>(i,j)[1] = max_index(hash2, 256);
			imgRecover.at<Vec3b>(i,j)[2] = max_index(hash3, 256);
		}			
	}
}

void Recovery::showResult()
{
	imshow("image", imgRecover);
	//imwrite("./imgTest2_210.jpg", imgRecover);
}

short Recovery::max_index(short a[], int len)
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
