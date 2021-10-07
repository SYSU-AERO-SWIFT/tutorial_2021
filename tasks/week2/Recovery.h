/*
* public���������Բ��ɱ��ұ���ʵ��
* private���������Կ���������
* �������б���ʹ��public������
*/
#ifndef RECOVERY
#define RECOVERY
#include<iostream>
#include<string>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
class Recovery {
public:
    /* readVideo
    * @param filePath �ļ�����·��
    * ���ݾ���·����ȡ��Ҫ��ԭ�������ļ�
    */
    void readVideo(string filePath);
    /* process
    * ���л�ԭ����
    */
    void process();
    /* showResult
    * ����չʾ������ԭ��Ľ��
    */
    void showResult();
private:
    VideoCapture vid;//�������Ƶ
    int row, col, total;//�С��С���֡��
    Mat* result;//���ͼ���ָ��
};
#endif