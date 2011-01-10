
CC=g++

flags=-O2 -msse3 -msse4.2 -fPIC

version=0.1

all: mlib

mlib: ../build/console_parameters.o ../build/double.o ../build/float.o ../build/integer.o ../build/long.o ../build/mmemory.o ../build/objfile.o ../build/processor.o ../build/randomize.o ../build/timer.o 
	g++ -shared -W1,-soname,libmlib.so.1 -o ../build/libmlib.so.$(version) ../build/console_parameters.o ../build/double.o ../build/float.o ../build/integer.o ../build/long.o ../build/mmemory.o ../build/objfile.o ../build/processor.o ../build/randomize.o ../build/timer.o 
	ln -s -f ../build/libmlib.so.$(version) ../build/libmlib.so


../build/console_parameters.o:
	$(CC) $(flags) -c console_parameters.cpp -o ../build/console_parameters.o

../build/double.o:
	$(CC) $(flags) -c double.cpp -o ../build/double.o

../build/float.o:
	$(CC) $(flags) -c float.cpp -o ../build/float.o

../build/integer.o:
	$(CC) $(flags) -c integer.cpp -o ../build/integer.o

../build/long.o:
	$(CC) $(flags) -c long.cpp -o ../build/long.o

../build/mmemory.o:
	$(CC) $(flags) -c mmemory.cpp -o ../build/mmemory.o

../build/objfile.o:
	$(CC) $(flags) -c objfile.cpp -o ../build/objfile.o

../build/processor.o:
	$(CC) $(flags) -c processor.cpp -o ../build/processor.o

../build/randomize.o:
	$(CC) $(flags) -c randomize.cpp -o ../build/randomize.o

../build/timer.o:
	$(CC) $(flags) -c timer.cpp -o ../build/timer.o


clean:
	rm -rf ../build/*.o
