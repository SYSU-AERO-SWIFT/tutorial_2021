/*
 * using the algorithm named Jung 
 * in this code have some changes
 * add the limit of similar frame 
 * this code is not the best one 
 * the parameter can be better
 */

#include "../inc/Recovery.h"

using namespace std; 

unsigned int iBkg[4100][4100][3];
unsigned int c_iBkg[4100][4100][3];

/*
 * this part open the video 
 * then get the information of the video include 
 * height width and total frame numbers
 * finally we create the output size 
 */

void Recovery::readVideo(const string& filePath) {
        cap.open(filePath);

        if(!cap.isOpened()) {
                printf("open file fail!\n");
                return ;
        }

        printf("open file success!\n");

        height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
        width= cap.get( CV_CAP_PROP_FRAME_WIDTH);
        frame_tot = cap.get(CV_CAP_PROP_FRAME_COUNT);

        output.create(height,width,CV_8UC3);
}

/*
 * frame save the frame we processed
 * p point the frame pixel
 * q point the output pixel
 * m is the change pixel num 
 * lrat means learning rate  
 * Y is the limitation of similarity
 */

void Recovery::process(){
        Mat frame;
        uchar * p;
        uchar * q;
        double lrat = 0.6;
        double m;
        int Y = 3;

        for(int i=0;i<frame_tot*0.813;++i){
                cap>>frame;
                for(int j=0;j<height;++j){
                        for(int k=0;k<width;++k){
                                p = frame.ptr<uchar>(j,k);
                                q = output.ptr<uchar>(j,k);
                                for(int t=0;t<3;++t){

                                        if(abs(iBkg[j][k][t]-p[t])<=1) {
                                                m = lrat * abs (p[t]-q[t]);
                                                c_iBkg[j][k][t]++;
                                        }
                                        else {
                                                m = 1;
                                                c_iBkg[j][k][t] = 0;
                                        }

                                        iBkg[j][k][t] = p[t];
                                        if(c_iBkg[j][k][t] > Y) continue;

                                        if(p[t]-q[t]>1) {
                                                q[t] += m;
                                        }
                                        else if(q[t] - p[t] > 1) {
                                                q[t] -= m;
                                        }
                                }
                        }
                }
}
        cap.release(); 

}


//output 
void Recovery::showResult(){
        namedWindow("Background"); 
        imwrite("./result/result.png",output); 
        imshow("Background",output);
}		

