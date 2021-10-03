#include "Recovery.h"
using namespace cv;

vector<Mat> Igray(3);
vector<Mat> Ilow(3);
vector<Mat> Ihi(3);
Mat frame;

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
	imshow("dfa", Iscratch);
	Iscratch.convertTo(Iscratch, CV_8UC3);
	waitKey(1000);
	static int first = 1;
	if (!first)
	{
		add(IavgF,Iscratch,IavgF);
		absdiff(Iscratch, IprevF, Iscratch2);
		add(IdiffF, Iscratch2, IdiffF);
		Icount += 1.0;
		cout << Icount;
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
	Imaskt = Mat::zeros(size, CV_8UC1);
	Imask = Mat::zeros(size, CV_8UC1);
	mask = Mat::zeros(size, CV_8UC1);
}





void Recovery::createModelsfromStats()
{
	IavgF *= 1 / Icount; //计算累计背景图片的均值
	
	IdiffF *= 1 / Icount;//累计绝对值帧的均值
	//为了使累计绝对值帧的均值不全为0，给每个元素都加1
	IdiffF += Scalar(1.0, 1.0, 1.0);

	setHighThreshold(7.0);//当计算前景和背景阈值以及避免前景阈值和背景阈值相等而出现的退化情况时，我们要缩放这个因素
	setLowThreshold(8.0);
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
	inRange(Igray[0], Ilow[0], Ihi[0], Imask);
	//通道2
    inRange(Igray[1], Ilow[1], Ihi[1], Imaskt);
	mask = cv::min(mask, Imaskt);
	//通道3
	inRange(Igray[2], Ilow[2], Ihi[2], Imaskt);
	mask = cv::min(mask, Imaskt);
	mask = 255 - mask;

}

void Recovery::process()
{
	capture>>image_recovery;
	if (image_recovery.empty()) {
		cout << "读取失败" << endl;
		return;
	}
	InitImages(image_recovery);
	int frame_width = capture.get(CAP_PROP_FRAME_WIDTH);
	int frame_height = capture.get(CAP_PROP_FRAME_HEIGHT);
	int count = capture.get(CAP_PROP_FRAME_COUNT);
	double fps = capture.get(CAP_PROP_FPS);
	cout << "frame width:" << frame_width << endl;
	cout << "frame height:" << frame_height << endl;
	cout << "FPS:" << fps << endl;
	cout << "Number of Frames:" << count << endl;

	namedWindow("recovery", WINDOW_FREERATIO);
	while (true) 
	{
		capture>>frame;
        if (frame.empty()) {
			break;
		}
		Accumulate_background();
	}
	createModelsfromStats();
	backgroundDiff();
	split(image_recovery, Igray);
	Igray[0] = cv::max(mask, Igray[0]);
	Igray[1] = cv::max(mask, Igray[1]);
	Igray[2] = cv::max(mask, Igray[2]);
	merge(Igray, image_recovery);

}

void Recovery::showResult()
{
	namedWindow("recovery", WINDOW_FREERATIO);
    imshow("recovery", image_recovery);
	waitKey(1000);
	imshow("MASK", mask);
	waitKey(1000);
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
	Imaskt.release();
	Imask.release();
	mask.release();
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
		Recovery recovery;
		recovery.readVideo("/home/linhuangnan/Desktop/tutorial_2021/tutorial_2021/tasks/week2/resource/video1.mp4");
		recovery.process();
		recovery.showResult();
		recovery.DeallocateImage();
}
