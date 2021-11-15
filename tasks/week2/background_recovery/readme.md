### Readme Tutorial

- Author: 陈建原
- Revised: 陈建原
- Date: 2021-10-09
- Version: 1.0.0
- Abstract: 这是一个用于还原视频背景的程序

### Functions:
	整体的思路是从视频中取一些图片样本，取样本像素点的色彩众数作为待还原图像对应像素点的色彩
	具体来看，先设定一个帧数FRAME，读取video的前FRAME张图片并将其按顺序保存到samples数组中，对于待还原图像的每一个像素点，遍历这些图片样本的对应像素点的色彩，在遍历过程中使用了hash数组和自定义的max_index函数来得到色彩的众数
	该方法在选取合适数量的样本时能够达到一个比较好的效果，经过测试，对于video0当FRAME取20时有较好的效果，对于video1当FRAME取210时有较好的效果，对于video2当FRAME取270时有较好的效果
	
### Interfaces:
	void readVideo(String filePath); //根据绝对路径读取需要还原背景的文件
    	void process(); //进行还原过程
    	void showResult(); //窗口展示背景还原后的结果
    	short max_index(short a[], int len); //求序列最大元素的下标 
	
### Depend Libraries:
	-依赖openCV

### how to compile
	在test文件夹中使用 g++ code.cpp `pkg-config --cflags --libs opencv`
	
### how to run
	准备工作：
		目录/test/resource用于存放视频
		在code.cpp中通过修改path来修改文件路径
		通过FRAME修改选取的图片数
		通过修改row和col的值来自定义输出图片的分辨率
		通过修改imwrite的路径参数来修改保存的文件名
	运行：
		在/test目录下重新编译code.cpp，执行./a.out即可在当前目录生成图片文件
	
