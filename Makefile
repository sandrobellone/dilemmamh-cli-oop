CC = g++
CFLAG = -std=c++11

build: dilemmamh-cli.cpp dmh.o
	$(CC) $(CFLAG) -o dilemmamh-cli dilemmamh-cli.cpp dmh.o

dmh.o: dmh.cpp dmh.h
	$(CC) $(CFLAG) -c dmh.cpp dmh.h

clean:
	rm -f *.o *.gch dilemmamh-cli
