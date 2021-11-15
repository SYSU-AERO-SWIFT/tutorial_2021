#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	string path = "./resource/video1.mp4";
	Recovery rec;
	rec.readVideo(path);
	rec.process();
	rec.showResult();
	return 0;
}
