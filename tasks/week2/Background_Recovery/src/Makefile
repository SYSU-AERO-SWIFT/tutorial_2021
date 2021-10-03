INCLUDES = -I/usr/local/include/opencv
LIBS = -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml
LIBDIRS = -L/usr/local/lib
 
OPT = -O3 -Wno-deprecated
 
CC=g++
 
.PHONY: all clean
 
OBJS= Recovery_vedio1_2.o
 
clean:
	rm -f *.o *~ Recovery_vedio1_2
 
all:Recovery_vedio1_2
	echo all:make complete
 
%.o:%.cpp
	$(CC) -c $(INCLUDES) $+ $(OPT)

test2:$(OBJS)
	$(CC) $(LIBDIRS) $(LIBS) -o $@ $+ $(OPT)
