VPATH := src:inc:test

TAR=./bin/test1
CC=g++
RM=rm -rf 

CONFIG=pkg-config --cflags --libs opencv

$(TAR):Recovery.cpp test.cpp Recovery.h
	$(CC) -o $(TAR)  ./src/Recovery.cpp ./test/test.cpp -I./inc `$(CONFIG)`

.PHONY:
clear: 
	$(RM) $(TAR)


