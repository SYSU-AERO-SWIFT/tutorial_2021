#include"Recovery.h"
int main(int argi, char** argv)
{
	string s = argv[1];
	//string s = "D://CVimage//video0.mp4";
	Recovery tool;
	tool.readVideo(s);
	tool.process();
	tool.showResult();
	return 0;
}