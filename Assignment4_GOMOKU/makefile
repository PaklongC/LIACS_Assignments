# eenvoudige makefile
all: hoofd.o gobord.o stapel.o
	g++ -Wall -o hetspel stapel.o gobord.o hoofd.o
gobord.o: gobord.cc gobord.h stapel.h
	g++ -Wall -c gobord.cc
hoofd.o: hoofd.cc gobord.h
	g++ -Wall -c hoofd.cc
stapel.o: stapel.cc stapel.h
	g++ -Wall -c stapel.cc
