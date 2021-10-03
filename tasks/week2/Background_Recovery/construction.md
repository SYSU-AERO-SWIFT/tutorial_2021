# Instructions of BackgroundRecovery
##（*参考CSDN*）
***
##Contributor
- Author:**林黄楠**
- Revised: --
- Date: 2021-10-3
- Version: 1.0.0
- Abstract:==这是一份视频背景还原的说明，因为时间和水平有限，因此采取比较易于理解的平均背景法来还原背景图==


##details
### Functions:
主要包括
readvideo(FilePath)
process()
showResult()

### Interfaces:
	... //C++ style declaration
### Depend Libraries:
<iostream>
<opencv2/opencv.hpp>
std
cv

### theories
***
>>>>>>>>>>>>>>>>>>>>>>>
平均背景法是一种建立背景模型的方法。简单地说，就是从视频或摄像头中获取一系列的帧，然后取这些帧中的平均像素值来表征背景。然后再给这些平均像素值加上一定的阈值范围，这就构成了背景模型。在新加入的图像中，如果对应位置的像素超出了这个背景模型中对应位置像素的阈值范围，就把它当作前景。

####步骤1: 累积背景
1.从视频中连续获取多帧图像，把这多帧图像分别标为I1、I2 ... 

2.从第2帧图像开始，把后面的300帧图像累加起来（这种累加是矩阵加法，下同）I2+…+ I300+I301 （因为考虑到后面的帧差需要从第2帧开始计算，所以这里也是从第2帧开始），得到图像IavgF

3.定义：帧差 = In-In-1l  把多帧图像里面的每一个帧差累加起来[I2-I1+I3-I4+…+I299-I300+(I300-I301)]得到图像 Iscratch

####步骤2: 创建基于统计学的背景模型
由步骤1得到了两个图像，IavgF 和Iscratch

1. 计算出这多帧中每帧的平均值IavgF

2. 从这300帧的帧差和中计算出平均帧差

3. 计算阈值的上限：（这里以7.0作为一个计算阈值上限的参数）

4. IavgF + [(IdiffF + 1.0) * 7.0] --> IhiF
把IhiF这个3通道图分割成3个单通道图Ihi1, Ihi2, Ihi3分别代表B、G、R通道

5. 计算阈值的下限：这里以6.0作为一个计算阈值下限的参数，IavgF - [(IdiffF + 1.0) * 6.0] --> IlowF,再把把IhiF这个3通道图分割成3个单通道图Ilow1, Ilow2, Ilow3分别代表B、G、R通道

####步骤3 利用背景模型分割背景
继续从视频或摄像头中获取图像帧，把获取到的图像帧标为I
1. 把I这个3通道图分割成3个单通道图Igray1, Igray2, Igray3分别代表B、G、R通道

2. 对Igray1, Igray2,Igray3进行阈值处理：
对于Igray1，如果图像中的像素值在(low1, lhi1)的范围之内，则把该像素值设置为255，否则把该像素值设为0。对Igray2和Igray3作同样的处理。然后合并Igray1, Igray2, Igray3这3个单通道图为1个3通道图Imask。

3. 作最后处理: 255 – Imask à Imask

### explanation
```C++
类中总共有的函数如下：
    /*readvideo  
    *读取视频
    */
    void readVideo(string filePath);
    /* process
    * 进行还原过程
    */
    void process();

    /* showResult
    * 窗口展示背景还原后的结果
    */
    void showResult();

    /* Init
     * 初始化所有的私有数据成员Mat
     */          
    void InitImages(Mat &init_image);

    /* average 
     * 将每一张图片读入并求和，其平均值就是加上一定的范围便可以认为是背景
     */          
    void Accumulate_background();

    /* statistic 
     * 统计均值，偏差
     */          
    void createModelsfromStats();

    /* set argument 
     * 设置参数，与阈值有关
     */          
    void setHighThreshold(float high);

    void setLowThreshold(float low);

    /*get mask
     * 每一张输入图片与背景模型比较，得到mask
     */
     void backgroundDiff();
     
    /*release
     *释放空间
     */
    void DeallocateImage();
    
    /*Mat addition
     *Mat的加法
     */
    void Mat_addition(Mat& fst, Mat& snd);
```

##END










