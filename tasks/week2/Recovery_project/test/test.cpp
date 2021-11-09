#include"Recovery.h"
#include<chrono>
int main(int argc, char** argv)
{
Recovery test;

chrono::steady_clock::time_point t1 = chrono::steady_clock::now();

test.readVideo(argv[1]);
test.process();
test.showResult();

chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
cout << "Process time = " << time_used.count() << " seconds" << endl;

return 0;
} 
