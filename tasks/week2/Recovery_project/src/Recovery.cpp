#include"Recovery.h"

void Recovery::readVideo(string filePath)
{
    path = filePath;
    VideoCapture cap;
    cap.open(path);
    
    // 以下循环读取并求出Avf和AvDif
    Isize = Size(500, 400);
    cap >> Image;
    while (Image.data)
     {
            Fcount++;
            resize(Image, Image, Isize);
            if (Fcount == 1) {
            Image.convertTo(Image, CV_32FC3);
            Avf = Image;
        }
    if (Fcount > 1)
        {
            Image.convertTo(Image, CV_32FC3);
            accumulate(Image, Avf);

            absdiff(Image, PreImage, tmpAvDif);
            tmpAvDif.convertTo(tmpAvDif, CV_32FC3);

            if (Fcount == 2) { AvDif = tmpAvDif; }
            else { accumulate(tmpAvDif, AvDif); }
        }
        PreImage = Image;
        cap >> Image;
    }

    Avf /= Fcount;
    Avf.convertTo(Avf, CV_8UC3);
    cvtColor(Avf, AvGrayf, COLOR_BGR2GRAY); // 由Avf生成AvGrayf

    AvDif /= Fcount;
    AvDif.convertTo(AvDif, CV_8UC3);
    cvtColor(AvDif, AvGrayDif, CV_BGR2GRAY); // 由AvDif生成AvGrayDif

    // 得到上下边界的值的矩阵
    HighBorder = AvGrayf + (6 * AvGrayDif);
    LowBorder = AvGrayf - (7 * AvGrayDif);
}

void Recovery::process()
{
    // 重新读取一帧
    cap.open(path);
    cap >> Image;
    resize(Image, Image, Isize);

    Image.convertTo(Image, CV_8UC3);
    cvtColor(Image, Grayf, COLOR_BGR2GRAY); // 得到当前帧的灰度矩阵

    inRange(Grayf, LowBorder, HighBorder, Imask); // 根据待判定的像素点的值是否在区间内得到Mask

    Imask = 255 - Imask; // Imask取反

    int irow = Imask.rows;
    int icol = Imask.cols;

    // 对彩色的原始帧进行遍历，根据Imask的值将“前景”用对应的背景替换

    for (int i = 0; i < irow; i++)
    {
    Vec3b* p1 = Image.ptr<Vec3b>(i);
    Vec3b* p2 = Avf.ptr<Vec3b>(i);
    uchar* p3 = Imask.ptr<uchar>(i);

    for (int j = 0; j < icol; j++)
         {
                if (p3[j] == 255) {
                            p1[j] = p2[j];
                 }
         }

    }
 }

void Recovery::showResult()
    {
        imshow(path, Image);
        waitKey(0);
    } 