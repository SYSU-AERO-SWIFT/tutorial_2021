
#include "background_recovery.cpp"
int main(int argc, char const *argv[]){
	Recovery test;
	test.readVideo(argv[1]);
	test.process();
	test.showResult();
	return 0;

}