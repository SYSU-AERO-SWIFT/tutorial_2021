#include "Recover.h"


int main(int argc, char const* argv[])
{
    Recovery TtTest;
    TtTest.readVideo("video0.mp4");
    TtTest.process();
    TtTest.showResult();

}




