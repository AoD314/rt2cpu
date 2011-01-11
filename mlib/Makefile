
CC=g++

flags=-msse3 -msse4.2 -g -ggdb -fPIC -fopenmp
#flags=-g -openmp -fast -axS

version=0.1

all: mlib

mlib: console_parameters.o double.o float.o integer.o long.o mmemory.o objfile.o processor.o randomize.o timer.o 
	g++ -shared -W1,-soname,libmlib.so.1 -o ../build/libmlib.so.$(version) ../build/console_parameters.o ../build/double.o ../build/float.o ../build/integer.o ../build/long.o ../build/mmemory.o ../build/objfile.o ../build/processor.o ../build/randomize.o ../build/timer.o  -lgomp
	ln -s -f ../build/libmlib.so.$(version) ../build/libmlib.so


console_parameters.o:
	$(CC) $(flags) -c console_parameters.cpp -o ../build/console_parameters.o

double.o:
	$(CC) $(flags) -c double.cpp -o ../build/double.o

float.o:
	$(CC) $(flags) -c float.cpp -o ../build/float.o

integer.o:
	$(CC) $(flags) -c integer.cpp -o ../build/integer.o

long.o:
	$(CC) $(flags) -c long.cpp -o ../build/long.o

mmemory.o:
	$(CC) $(flags) -c mmemory.cpp -o ../build/mmemory.o

objfile.o:
	$(CC) $(flags) -c objfile.cpp -o ../build/objfile.o

processor.o:
	$(CC) $(flags) -c processor.cpp -o ../build/processor.o

randomize.o:
	$(CC) $(flags) -c randomize.cpp -o ../build/randomize.o

timer.o:
	$(CC) $(flags) -c timer.cpp -o ../build/timer.o


clean:
	rm -rf ../build/console_parameters.o ../build/double.o ../build/float.o ../build/integer.o ../build/long.o ../build/mmemory.o ../build/objfile.o ../build/processor.o ../build/randomize.o ../build/timer.o 
