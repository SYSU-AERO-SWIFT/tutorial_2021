#include"Recovery.h"

int max_count_num(vector<int>arr, int len)//一个用于计算arr中元素出现次数最多的函数，返回的是元素
{
	int i, j;
	int m;
	int count;
	//定义次数存储数组
	int* max = (int*)malloc(sizeof(int) * len);
	if (max == NULL) {
		printf("malloc failed\n");
		exit(-1);
	}
	//数组初始化
	for (i = 0; i < len; i++) {
		max[i] = 0;
	}

	//对数组中的元素进行count
	for (i = 0; i < len; i++) {
		count = 0;
		for (j = i; j < len; j++) {
			if (arr[i] == arr[j]) {
				max[i]++;
			}
		}
	}

	//取出数组中元素的最大值
	m = 0;
	for (i = 0; i < len; i++) 
	{
		if (max[m] < max[i]) {m = i;}
	}
	
    return arr[m];
	
}


void Recovery::readVideo(String filePath)//读取视频
{capture.open(filePath);
 if (!capture.isOpened())  
     cout << "Read video Failed !" << endl;  
height = capture.get(CV_CAP_PROP_FRAME_HEIGHT);//画面的高度
width = capture.get(CV_CAP_PROP_FRAME_WIDTH);//画面的宽度
fps = capture.get(CV_CAP_PROP_FPS);//视频的帧率
count = 0;//计数器
framenum = capture.get(CAP_PROP_FRAME_COUNT);//记录帧的总数
}     
     
  


void Recovery:: process(){
double time1 = static_cast<double>( getTickCount());//记录起始时间，其中getTickCount()函数返回CPU 自某个事件（如启动电脑）以来走过的时钟周期数
       int interval = (framenum /100) + 1;//取帧的间隔
       Mat out(height, width, CV_8UC3); //输出对象
       vector<int> arr0;//存放像素的每个值，分别对应三个通道
       vector<int> arr1;
       vector<int>arr2;
       Mat tempframe1;	
	for (int i = 0; i < framenum; i++)//按照预先设定好的间隔读取一定帧
	{
		capture >> tempframe1;
		if (i % interval == 0)
			frames.push_back(tempframe1.clone());
		if (frames.size() > 100) break;//防止frames尺寸过大

	}
	
	
		for (int j = 0; j < out.rows; j++)//原理很简单，就是计算已经读取的帧中每个像素的每个值的出现次数，将出现次数最多的值赋给这个像素
		{
			for (int k = 0; k < out.cols; k++)
			{
				for (int i = 0; i < frames.size()-1; i++)
				{
					arr0.push_back(frames[i].at<Vec3b>(j, k)[0]);
					arr1.push_back(frames[i].at<Vec3b>(j, k)[1]);
					arr2.push_back(frames[i].at<Vec3b>(j, k)[2]);
				}
				out.at<Vec3b>(j, k)[0] = max_count_num(arr0, arr0.size());
				out.at<Vec3b>(j, k)[1] = max_count_num(arr1, arr1.size());
				out.at<Vec3b>(j, k)[2] = max_count_num(arr2, arr2.size());
				arr0.clear();
				arr1.clear();
				arr2.clear();
			}
		}
		
		imwrite("result/result.png", out);//写入文件
		
    
double time2 = (static_cast<double>( getTickCount()) - time1)/getTickFrequency();//获得了读取一张图像所需的时间单位为秒。 其中getTickFrequency()函数返回CPU一秒钟所走得时钟周期数。
cout<<"还原视频背景用时为："<< time2 <<"秒"<<endl;//输出运行时间;
}


void Recovery::showResult()//结果展示
{cvNamedWindow("result",WINDOW_AUTOSIZE);
  //imshow("result","./result/result.png");
  waitKey(0);

}

