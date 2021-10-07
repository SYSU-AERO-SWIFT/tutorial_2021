compiler=g++
lib=`pkg-config --cflags --libs opencv`
main: main.cpp Recovery.o
	$(compiler)  main.cpp Recovery.o -o recovery $(lib)
Recovery.o: Recovery.cpp
	$(compiler)  -c Recovery.cpp $(lib)
clean:
	rm *.o
