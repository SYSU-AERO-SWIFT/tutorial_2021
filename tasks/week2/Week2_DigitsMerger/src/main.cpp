/*
 * this part is used to test the Recovery.h&.cpp
 * t1 is a time counter 
 * it output the calculate time of .process()
 * the input will be got from the command line
 */

#include <iostream> 
#include "../inc/Recovery.h" 
using namespace std; 

int main(int argv,char ** argc){
        string filePath= argc[1]; 
        //cin>>filePath; 
        Recovery r;
        r.readVideo(filePath);

        double t1 = clock();
        r.process();
        t1 = clock() - t1;
        printf("Process Time: %.6lf s\n",t1/CLOCKS_PER_SEC);    
        r.showResult();

        waitKey(0); 
        return 0;
}


