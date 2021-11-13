## About the frontmask vanisher

- Author: Lou Yuefeng
- Revised: Lou Yuefeng
- Date: 2021-10-3
- Version: 1.0.0
- Abstract: A brief introduction on the basic machanics of the Recovery file and tips for further utilization
### Functions:
	Firstly the **readVideo()** function is to read video through direct path, make sure you enter a feasible path
	Then **process()** function randomly select 50(*you may change this number according to specific demand*) frames and take median property on 3-tunnel-scale pixel by pixel
	The **showResult()** function is literally used to show image
### Interfaces:
	int main(int argc, char const* argv[])
 {
     Recovery TtTest;
     TtTest.readVideo("video0.mp4");//Enter path here
     TtTest.process();
     TtTest.showResult();
 
 }

### Depend Libraries:
	include <opencv2/opencv.hpp>
	include <iostream>
	include <random>
	include <time.h>
	include <sys/stat.h>
	include <sys/types.h>
	include <unistd.h>
	for advanced usage, maybe you should learn how Gussian Model MOG (statistical method based on probability theory)method or kkn(take stuff alike as one kind and observe their distance, take difference between frames as parameter)  method works, I didn't do much training so neither preformed well in this case
