#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#define FRAME 210
using namespace cv;

class Recovery 
{public:
    void readVideo(String filePath); //���ݾ���·����ȡ��Ҫ��ԭ�������ļ�
    void process(); //���л�ԭ����
    void showResult(); //����չʾ������ԭ��Ľ��
    short max_index(short a[], int len); //���������Ԫ�ص��±� 
    
private:
	VideoCapture cap;
	Mat img;
	Mat imgResize;
	Mat imgRecover(720,1280,CV_8UC3);
	int imgNum = 0;
	int row = 720;
    	int col = 1280;
	Mat sample[FRAME];
};
