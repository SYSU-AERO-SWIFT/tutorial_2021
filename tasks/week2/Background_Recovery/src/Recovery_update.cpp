#include "Recovery_update.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <ctime>

using namespace cv;

vector<Mat> Igray(3);
vector<Mat> Ilow(3);
vector<Mat> Ihi(3);
vector<Mat> mask(3);



/*void Recovery::Mat_addition(Mat& fst, Mat& snd) {
	#define    Vec3b    Vec<float,3>
	int w = fst.cols;
	int h = fst.rows;
	int dims = fst.channels();
	for (int row = 0; row < h; row++) {
		for (int col = 0; col < w; col++) {
			if (dims == 1) { // 灰度图像
				float pv = fst.at<float>(row, col)+snd.at<float>(row,col);
				fst.at<uchar>(row, col) = pv;
			}
			if (dims == 3) { // 彩色图像
				Vec3b fstvec = fst.at<Vec3b>(row, col);
				Vec3b sndvec = snd.at<Vec3b>(row, col);
				fst.at<Vec3b>(row, col)[0] = fstvec[0]+sndvec[0];
				fst.at<Vec3b>(row, col)[1] = fstvec[1] + sndvec[1];
				fst.at<Vec3b>(row, col)[2] = fstvec[2] + sndvec[2];
			}
		}
	}
}*/

void Recovery::readVideo(string filePath)
{
	capture.open(filePath);
	if (! capture.isOpened())
	{
		cout << "打开失败" << endl;
		return;
	}
}

void Recovery::Accumulate_background()
{
	frame.convertTo(Iscratch,CV_32FC3);
	static int first = 1;
	if (!first)
	{
		IavgF=IavgF+Iscratch;
		absdiff(Iscratch, IprevF, Iscratch2);
		IdiffF=IdiffF+Iscratch2;
		Icount += 1.0;
	}
	first = 0;
	IprevF = Iscratch;
}

void Recovery::InitImages(Mat &init_image)
{
	Size size = init_image.size();
	IavgF =Mat::zeros(size, CV_32FC3);
	IdiffF = Mat::zeros(size, CV_32FC3);
	IprevF = Mat::zeros(size, CV_32FC3);
	IhiF = Mat::zeros(size, CV_32FC3);
	IlowF = Mat::zeros(size, CV_32FC3);
	

	Ilow[0] = Mat::zeros(size, CV_32FC1);
	Ilow[1] = Mat::zeros(size, CV_32FC1);
	Ilow[2] = Mat::zeros(size, CV_32FC1);
	Ihi[0] = Mat::zeros(size, CV_32FC1);
	Ihi[1] = Mat::zeros(size, CV_32FC1);
	Ihi[2] = Mat::zeros(size, CV_32FC1);
	Icount = 0.00001;
	Igray[0] = Mat::zeros(size, CV_32FC1);
	Igray[1] = Mat::zeros(size, CV_32FC1);
	Igray[2] = Mat::zeros(size, CV_32FC1);
	mask[0] = Mat::zeros(size, CV_8UC1);
	mask[1] = Mat::zeros(size, CV_8UC1);
	mask[2] = Mat::zeros(size, CV_8UC1);
}





void Recovery::createModelsfromStats()
{
	Size size = image_recovery.size();
	Mat temp1(size, CV_32FC3);
	temp1 = Scalar(1 / Icount, 1 / Icount, 1 / Icount);
	
	IavgF = IavgF.mul(temp1); //计算累计背景图片的均值
	IdiffF = IdiffF.mul(temp1);//累计绝对值帧的均值
	//IavgF.convertTo(temp2, CV_8UC3);
	//namedWindow("recovery", WINDOW_FREERATIO);
	//imshow("recovery", temp2);
	//waitKey(0);
	//为了使累计绝对值帧的均值不全为0，给每个元素都加1
	IdiffF += Scalar(1.0, 1.0, 1.0);
    setHighThreshold(10.0);//当计算前景和背景阈值以及避免前景阈值和背景阈值相等而出现的退化情况时，我们要缩放这个因素
	setLowThreshold(10.0);
}

void Recovery::setHighThreshold(float ratio) {
	IhiF = IavgF + (IdiffF * ratio);
	split(IhiF, Ihi);
}

void Recovery::setLowThreshold(float ratio) {
	IlowF = IavgF - (IdiffF * ratio);
	split(IlowF, Ilow);
}

void Recovery::backgroundDiff() {
	image_recovery.convertTo(Iscratch, CV_32F);
	split(Iscratch, Igray);
	//通道1
	inRange(Igray[0], Ilow[0], Ihi[0], mask[0]);
	//通道2
    inRange(Igray[1], Ilow[1], Ihi[1], mask[1]);
	mask[2] = min(mask[0], mask[1]);
	//通道3
	inRange(Igray[2], Ilow[2], Ihi[2], mask[0]);
	mask[2] = min(mask[0], mask[2]);
}

void Recovery::process()
{
	capture>>image_recovery;
	if (image_recovery.empty()) {
		cout << "读取失败" << endl;
		return;
	}
	InitImages(image_recovery);
	//int frame_width = capture.get(CAP_PROP_FRAME_WIDTH);
	//int frame_height = capture.get(CAP_PROP_FRAME_HEIGHT);
	//int count = capture.get(CAP_PROP_FRAME_COUNT);
	//double fps = capture.get(CAP_PROP_FPS);
	//cout << "frame width:" << frame_width << endl;
	//cout << "frame height:" << frame_height << endl;
	//cout << "FPS:" << fps << endl;
	//cout << "Number of Frames:" << count << endl;

	namedWindow("recovery", WINDOW_FREERATIO);
	for(int i=0;i<250;i++)
	{
		capture>>frame;
        if (frame.empty()) {
			break;
		}
		Accumulate_background();
	}
	createModelsfromStats();
	backgroundDiff();
	image_recovery.convertTo(image_recovery, CV_8UC3);
	IavgF.convertTo(IavgF, CV_8UC3);
	image_recovery.copyTo(IavgF, mask[2]);
	

	
	//image_recovery.convertTo(image_recovery, CV_8UC3);
	//IavgF.convertTo(IavgF, CV_8UC3);
	//addWeighted(IavgF, 0, image_recovery, 1,0,image_recovery);
	
	
	namedWindow("recovery", WINDOW_FREERATIO);
	imshow("recovery", IavgF);
	waitKey(0);
}

void Recovery::showResult()
{
  imwrite("/home/linhuangnan/Desktop/tutorial_2021/tutorial_2021/tasks/week2/Background_Recovery/result/recovery_video1.jpg", IavgF);   //写至相关路径
	//imshow("MASK", mask);
	//waitKey(1000);
    //writer.write(frame);
}



void Recovery::DeallocateImage() {
	capture.release();
	frame.release();
	IavgF.release();
	IdiffF.release();
	IprevF.release();
	IhiF.release();
	IlowF.release();
	Iscratch.release();
	Iscratch2.release();
	mask[0].release();
	mask[1].release();
	mask[2].release();
	Igray[0].release();
	Igray[1].release();
	Igray[2].release();
	Ilow[0].release();
	Ilow[1].release();
	Ilow[2].release();
	Ihi[0].release();
	Ihi[1].release();
	Ihi[2].release();
}



int main()
{
    clock_t start,end;
    Recovery recovery;
		recovery.readVideo("/home/linhuangnan/Desktop/tutorial_2021/tutorial_2021/tasks/week2/resource/video2.mp4");
		start=clock();
    recovery.process();
    end=clock();
    recovery.showResult();
		recovery.DeallocateImage();
    double totaltime=double(end-start)/CLOCKS_PER_SEC;
    cout<<"total time:"<<totaltime <<" s"<<endl;
}
