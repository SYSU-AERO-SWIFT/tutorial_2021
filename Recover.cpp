#include "Recover.h"


 void Recovery::readVideo(String filePath)
    {
       
       
        VideoCapture cap(filePath);
        if (!cap.isOpened())
            cerr << "Error opening video file\n"; 
    }// 读取视频文件



       int Recovery::computeMedian(vector<int> elements)
        {
            nth_element(elements.begin(), elements.begin() + elements.size() / 2, elements.end());

            //sort(elements.begin(),elements.end());
            return elements[elements.size() / 2];
        }//数学中值函数

         cv::Mat compute_median(std::vector<cv::Mat> vec)
        {
            // 注意:期望图片是CV_8UC3
            cv::Mat median_Img(vec[0].rows, vec[0].cols, CV_8UC3, cv::Scalar(0, 0, 0));

            for (int row = 0; row < vec[0].rows; row++)
            {
                for (int col = 0; col < vec[0].cols; col++)
                {
                    std::vector<int> elements_B;
                    std::vector<int> elements_G;
                    std::vector<int> elements_R;

                    for (int img_Number = 0; img_Number < vec.size(); img_Number++)
                    {
                        int B = vec[img_Number].at<cv::Vec3b>(row, col)[0];
                        int G = vec[img_Number].at<cv::Vec3b>(row, col)[1];
                        int R = vec[img_Number].at<cv::Vec3b>(row, col)[2];

                        elements_B.push_back(B);
                        elements_G.push_back(G);
                        elements_R.push_back(R);
                    }

                    median_Img.at<cv::Vec3b>(row, col)[0] = Recovery::computeMedian(elements_B);
                    median_Img.at<cv::Vec3b>(row, col)[1] = Recovery::computeMedian(elements_G);
                    median_Img.at<cv::Vec3b>(row, col)[2] = Recovery::computeMedian(elements_R);
                }
            }
            return median_Img;
        }//按像素对每个通道运算求中值


 void Recovery::process()
    {

       
        default_random_engine generator;
        uniform_int_distribution<int>distribution(0, cap.get(CAP_PROP_FRAME_COUNT));
        startTime = clock();//开始计时
       
        for (int i = 0; i < 50; i++)
        {
            int fid = distribution(generator);
            cap.set(CAP_PROP_POS_FRAMES, fid);
            Mat frame;
            cap >> frame;
            if (frame.empty())
                continue;
            frames.push_back(frame);
        } // 随机选择50帧   


        medianFrame = compute_median(frames); // 计算沿时间轴的中值
        cout << "Time: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;//计时结束
    }

 void Recovery::showResult()
    {
        imshow("frame", medianFrame);// 显示
        string folderPath = "/home/result";

        if (0 != access(folderPath.c_str(), 0))
        {
            // 创建result文件夹
            mkdir(folderPath.c_str(),S_IRWXU);   // 返回 0 表示创建成功，-1 表示失败
            // mode, she zhi cheng  ke du ke xie
        }

        imwrite("/home/result/bgp.png", medianFrame);//写入文件
        waitKey(0);
    }




