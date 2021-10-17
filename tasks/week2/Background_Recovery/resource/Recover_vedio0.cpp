#include "Recover_vedio0.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

/*该视频的障碍物基本上是单色小块，因此先将图片转换到HSV色彩空间，
  因为HSV色彩空间对颜色比较敏感，然后采用阈值和掩码矩阵，在配合一个
  copyTo函数，基本可以达到要求
  该方法有一定局限性，只能适用于类似的单色障碍物，并且对单色障碍物
 */
void Recovery::readVideo(string filePath)
{
	//打开视频，如果打开失败则输出提示
	capture.open(filePath);
	if (!capture.isOpened())
	{
		cout << "打开失败" << endl;
		return;
	}
}

void Recovery::process()
{
	
	Mat hsv;   //hsv色彩空间
	Mat mask;
	for (int i = 0; i < 17; i++)   //读取任意一张合适的图片
	{
		capture >> frame;
	}
	//以下注释部分可以用于输出图片的帧率和总帧数，但是在本题没什么用
	/*int frame_width = capture.get(CAP_PROP_FRAME_WIDTH);
	int frame_height = capture.get(CAP_PROP_FRAME_HEIGHT);
	int count = capture.get(CAP_PROP_FRAME_COUNT);
	double fps = capture.get(CAP_PROP_FPS);
	std::cout << "frame width:" << frame_width << std::endl;
	std::cout << "frame height:" << frame_height << std::endl;
	std::cout << "FPS:" << fps << std::endl;
	std::cout << "Number of Frames:" << count << std::endl;*/
    capture >> recovery_image;      //先将一张图片读至recovery_image,这张图片有障碍物
    capture >> frame;
	cvtColor(frame, hsv, COLOR_BGR2HSV);
	//
	inRange(hsv, Scalar(35, 43,46), Scalar(77, 255, 255), mask);   //根据掩码将紧接着的一张图片（已经剔除了障碍物）也读至recovery_image，
	                                                              //两张图片互补基本上可以去掉障碍物，如果不行再加第三张图片
	bitwise_not(mask, mask);
	frame.copyTo(recovery_image, mask);
}

void Recovery::showResult()
{
	imwrite ("~/Desktop/tutorial_2021/tutorial_2021/tasks/week2/Background_Recovery/result/video0_result.jpg",recovery_image);   //写至相关路径
}
int main()
{
	Recovery recovery;
	recovery.readVideo("/home/linhuangnan/Desktop/tutorial_2021/tutorial_2021/tasks/week2/resource");
	recovery.process();
	recovery.showResult();
}
