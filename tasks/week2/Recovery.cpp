#include"Recovery.h"
void Recovery::readVideo(string filePath)
{
	vid.open(filePath);
	if (vid.isOpened())
		cout << "Open successfully." << endl;
	else
		cout << "Wrong file path." << endl;
	Mat temp;
	vid >> temp;
	row = temp.rows;
	col = temp.cols;
	total = vid.get(CAP_PROP_FRAME_COUNT);
	vid.set(CAP_PROP_POS_FRAMES, 0);//重置视频与开始位置
}
void Recovery::showResult()
{
	//imwrite("Result.jpg", *result);
	namedWindow("Result", WINDOW_NORMAL);
	imshow("Result", *result);
	waitKey(0);
}
void Recovery::process()//通过计算各个像素点在所有图像中的平均值获取背景
{
	double time1 = getTickCount();//计时
	unsigned int** add = new unsigned int* [row];
	for (int i = 0; i < row; i++)
	{
		add[i] = new unsigned int[3 * col];
		for (int j = 0; j < 3 * col; j++)
			add[i][j] = 0;
	}
	Mat pic;
	vid >> pic;
	while (!pic.empty())//将各像素点在所有图片中的值累计起来
	{
		for (int i = 0; i < row; i++)
		{
			uchar* p = pic.ptr<uchar>(i);
			for (int j = 0; j < col*3; j++)
				add[i][j] += p[j];
		}
		vid >> pic;
	}
	result = new Mat(row, col, CV_8UC3);
	for (int i = 0; i < row; i++)
	{
		uchar* p = result->ptr<uchar>(i);
		for (int j = 0; j < col * 3; j++)
			p[j] = add[i][j] / total;//计算平均值并存入结果
	}
	double time2 = getTickCount();
	double time = (time2 - time1) /getTickFrequency();
	std::cout << "Execution time: " << time << "s" << std::endl;
}