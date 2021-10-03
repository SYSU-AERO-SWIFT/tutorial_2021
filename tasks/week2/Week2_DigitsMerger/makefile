INCLUDE = $(shell pkg-config --cflags opencv)#opencv的include头文件路径
LIBS = $(shell pkg-config --libs opencv) -lm #opencv的lib库文件路径

SOURCES = ./src/Recovery.cpp ./inc/Recovery.h ./src/main.cpp#源文件

# 目标文件
OBJECTS = Recovery.o main.o #先生成目标文件.o

TARGET =./bin/Demo #生成的可执行文件名称
$(TARGET):$(OBJECTS)
	g++ -fopenmp -o $(TARGET) $(OBJECTS) -I $(INCLUDE) $(LIBS) $(OTHERLIB) -std=c++11
$(OBJECTS):$(SOURCES)
	g++ -fopenmp -c $(SOURCES) -std=c++11
clean:
	rm *.gch $(OBJECTS) $(TARGET)
