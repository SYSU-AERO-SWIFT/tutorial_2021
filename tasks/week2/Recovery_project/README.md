# 项目Background Recovery说明

## 基本信息

**作者**：杨诺萁

**修改日期**：21/10/4

**简介**：包含类**Recovery**的定义和实现，实现从给定的视频中读取帧，按**累积帧**和**累积绝对值帧间差分**后取平均的方法建立背景模型，从而提取背景。

***

## 类说明

### 方法与接口

**读取视频**：

```C++
void VideoCapture(string FilePath)
```

**处理帧与背景建模**：

```C++
void Process()
```

**展示背景结果**

```C++
void show()
```

### 编译

```shell
# 先切换到工程目录下
rm ./bin/test1
make clear
make
```

### 运行

```shell
./bin/test1 ./resource/video0.mp4 #示例
```

### 背景提取过程的具体说明

```C++
// 我对读取的图片都进行了resize处理，否则虽然能通过编译，但
// 运行过程中会出现内存错误

// 背景模型实际上是平均值上下的一个区间，是8位灰度矩阵
// 建模完成后，重新读取第一帧，用背景模型判定前景部分，并用保留
// 的彩色平均背景进行替换，得到结果

// 前景判定的方法是：位于区间内的是背景，反之则是前景
```


