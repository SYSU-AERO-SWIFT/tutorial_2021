# 背景还原项目说明
- Author: 马浩铭
- Revised: 马浩铭
- Date: 2021-9-30
- Version: 1.0.0
- Abstract: 完成背景还原项目

## Functions:
	还原tasks/week2中几个视频的背景（只完成了前两个视频）
## Interfaces:
	readVideo: 读入视频
	process: 处理视频
	showResult: 展示处理结果
## Depend Libraries:
	- opencv4.5.3
	- g++
## 编译方法
	通过makefile文件直接编译。因为main函数中已经包含了头文件关系，所以makefile只依赖于main.cpp

## 测试方法
	通过执行bin/demo文件，并给出视频路径，如 ./bin/demo video0.mp4

## 实现流程
	统计视频中每个像素块出现的不同颜色，将出现次数最多的作为结果中的像素值。