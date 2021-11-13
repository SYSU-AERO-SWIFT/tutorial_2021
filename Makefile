object = Recover.o test.o
Recovery: $(object)
	gcc -o Recovery $(object)
  
%.o : %.c
	gcc -c $<
  
clean:
	rm *.o
	rm main
