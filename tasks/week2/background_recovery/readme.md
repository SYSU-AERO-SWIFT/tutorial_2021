## Readme

- Author: Zexi-Xie
- Revised: Zexi-Xie
- Date: 2021-10-04
- Version: 1.0.0
- Abstract: Hello, this is the readme for my code of background recovery

### Functions:
	通过比较简单的聚类算法，从视频里截取样本帧后以时间为维度看每个位置像素点的RGB值分布情况，选出在偏差范围内像素点分布最密集的点作为背景点。
	一开始选择直接对视频取关键帧，再对每个位置的每个色素值取众数的方法。但是发现这种方式能够很好的对video0和video3实现背景提取，而且效率很高，在5s之内可以完成process函数。但是对于video2无论我如何调参都有较为明显的噪点。分析像素点的原理后，发现把RGB分开统计各个颜色的众数再合并得到的像素值并不是RGB三维空间中真正的聚点，因此决定把RGB三个值合并一起考虑。尝试过用位运算把三个uchar值存到一个uint里，但是这样的方式在比较差值时并不能直接做差，效果不好。于是再建立一个结构体和设置一个偏差值来对RGB点进行聚类。当两个点的差值（三维分别的差的绝对值加和）小于偏差值时，认为这两个点属于近似点，取加权平均值后增加这个点的权重；当像素点和已有点之差都大于偏差值时，把这个点加入聚类点容器。
	经过对参数的调整，发现knn(偏差值)在30左右较为理想，knn过小时运行时间长，成图噪点也多；knn过大时成图跟原图色差较大。
	样本帧的数量直接决定了process函数的运行时间，对于video0，取6帧左右即可达到较好的效果；对于video1，取10帧左右可以达到较好的效果；对于video2，取15帧左右成图效果好。

### Interfaces:
```c++
    /* readVideo
    * @param filePath 文件绝对路径
    * 根据绝对路径读取需要还原背景的文件
    * 用VideoCapture类读取完存到私有变量video
    */
    void readVideo(String filePath);

    /* process
    * 进行还原过程
    */
    void process();

    /* showResult
    * 窗口展示背景还原后的结果
    */
    void showResult();
```
### Depend Libraries:
	依赖C++
	依赖opencv



### 编译提示:

```
cd ~/tutorial_2021/tasks/week2/background_recovery
make
```



### 测试程序

```
#运行程序
./bin/demo ./resource/video<i>.mp4      (i = 0,1,2)

#成功运行
>>finish!!!
>>Process time: ***s

#自测process运行时间
video0：16.38s
video1：29.79s
video2：468.76s  (我也很难理解为什么耗时这么长)

```


