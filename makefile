all: OSexam
OSexam: main.o
	g++ main.o -o OSexam
main.o: main.cpp
	g++ -c main.cpp
