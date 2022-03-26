all: user

user: user.o string.o
	c++ -o user user.o string.o

user.o: user.cc string.h
	c++ -c user.cc

string.o: string.cc string.h
	c++ -c string.cc

