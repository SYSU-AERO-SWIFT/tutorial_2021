#include"Recovery.h"

void Recovery::readVideo(string filePath)
{
path = filePath;
VideoCapture cap;
cap.open(path);
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
}
cap >> Image;
}

Avf /= Fcount;
Avf.convertTo(Avf, CV_8UC3); 
cvtColor(Avf, AvGrayf, COLOR_BGR2GRAY);
}

void Recovery::process()
{
cap.open(path);
cap >> Image;
resize(Image, Image, Isize);

Image.convertTo(Image, CV_8UC3);
cvtColor(Image, Grayf, COLOR_BGR2GRAY);

absdiff(Grayf, AvGrayf, Dif);
threshold(Dif, Compare, 20, 255, THRESH_BINARY);

int irow = Compare.rows;
int icol = Compare.cols;

for (int i = 0; i < irow; i++)
{
Vec3b* p1 = Image.ptr<Vec3b>(i);
Vec3b* p2 = Avf.ptr<Vec3b>(i);
uchar* p3 = Compare.ptr<uchar>(i);

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
waitKey(30);
} 
