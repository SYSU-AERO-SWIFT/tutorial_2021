/*************************************************************************
	> File Name: main.cpp
	> Author:ZX Xie 
	> Mail:1514806752@qq.com 
	> Created Time: 2021年09月30日 星期四 03时54分33秒
 ************************************************************************/

#include "../inc/Recovery.h"

int main(int argc, char const *argv[]){
    Recovery solution;
    solution.readVideo(argv[1]);
    solution.process();
    solution.showResult();
    return 0;
}
