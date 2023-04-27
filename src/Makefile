CC = g++
CFLAGS = -Wall -Werror -pedantic -std=c++17

all: main

main:main.o CommandLineParser.o
	$(CC) $(CFLAGS) -o main main.o CommandLineParser.o

main.o:main.cpp CommandLineParser.h
	$(CC) $(CFLAGS) -c main.cpp


CommandLineParser.o: CommandLineParser.cpp CommandLineParser.h
	$(CC) $(CFLAGS) -c CommandLineParser.cpp

clean:
	rm *.o
	rm main