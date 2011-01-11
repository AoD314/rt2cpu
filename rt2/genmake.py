#!/usr/bin/python3

import subprocess
import os

f = open('Makefile', 'w')

f.write("\nCC=g++")
f.write("\n\nflags=-O0 -msse3 -msse4.2 -g -ggdb -I../mlib")

f.write("\n\nall: rt2cpu\n")

list = []

myout = subprocess.getoutput('ls *.cpp')
list = myout.split("\n") 

nlist = []
for n in list:
	name = n[:-4]
	nlist = nlist + [name]

#####

obj = ''
o = ''

for n in nlist:
	obj = obj + '../build/' + n + '.o '
	o = o + n + '.o '

f.write('\nrt2cpu: ' + o)

f.write('\n\t$(CC) $(flags) ' + obj + '-lgomp -lSDL -lmlib -L../build/')

f.write('\n\n')

for n in nlist:
	f.write('\n'+n+'.o: ' + n + '.cpp ')
	if os.path.isfile(n + '.hpp'): 
		f.write(n + '.hpp')
	f.write('\n\t$(CC) $(flags) -c ' + n + '.cpp -o ../build/' + n + '.o\n' )

f.write('\n\nclean:')
f.write('\n\trm -rf ' + obj + '\n')

f.close()

