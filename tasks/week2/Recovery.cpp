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
	vid.set(CAP_PROP_POS_FRAMES, 0);//������Ƶ�뿪ʼλ��
}
void Recovery::showResult()
{
	//imwrite("Result.jpg", *result);
	namedWindow("Result", WINDOW_NORMAL);
	imshow("Result", *result);
	waitKey(0);
}
void Recovery::process()//ͨ������������ص�������ͼ���е�ƽ��ֵ��ȡ����
{
	double time1 = getTickCount();//��ʱ
	unsigned int** add = new unsigned int* [row];
	for (int i = 0; i < row; i++)
	{
		add[i] = new unsigned int[3 * col];
		for (int j = 0; j < 3 * col; j++)
			add[i][j] = 0;
	}
	Mat pic;
	vid >> pic;
	while (!pic.empty())//�������ص�������ͼƬ�е�ֵ�ۼ�����
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
			p[j] = add[i][j] / total;//����ƽ��ֵ��������
	}
	double time2 = getTickCount();
	double time = (time2 - time1) /getTickFrequency();
	std::cout << "Execution time: " << time << "s" << std::endl;
}