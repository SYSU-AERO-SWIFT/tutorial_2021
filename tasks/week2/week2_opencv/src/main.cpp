#include"Recovery.cpp"
int main(int argc, char ** argv)
{  Recovery recovery;       
   recovery.readVideo(argv[1]);                
   recovery.process();                  
   recovery.showResult();                              


return 0;
}
