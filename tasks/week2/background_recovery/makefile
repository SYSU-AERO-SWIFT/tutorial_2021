bin/demo: src/main.cpp src/Recovery.cpp
	g++ src/Recovery.cpp src/main.cpp -o bin/demo  `pkg-config --cflags --libs opencv`


.PHONY clean:
	rm -f *.o
