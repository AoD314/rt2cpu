#!/usr/bin/python3

import subprocess

f = open('Makefile', 'w')

f.write("\nCC=g++")
f.write("\n\nflags=-O3 -msse3 -msse4.2 -g -Wall -fPIC -fopenmp")

f.write("\n\nversion=0.1")
f.write("\n\nall: mlib\n")

list = []

myout = subprocess.getoutput('ls *.cpp')
list = myout.split("\n") 

nlist = []
for n in list:
	name = n[:-4]
	nlist = nlist + [name]

#####

obj = ''

for n in nlist:
	obj = obj + '../build/' + n + '.o '

f.write('\nmlib: ' + obj)

f.write('\n\tg++ -shared -W1,-soname,libmlib.so.1 -o ../build/libmlib.so.$(version) ' + obj + ' -lgomp')
f.write('\n\tln -s -f ../build/libmlib.so.$(version) ../build/libmlib.so')

f.write('\n\n')

for n in nlist:
	f.write('\n../build/'+n+'.o:')
	f.write('\n\t$(CC) $(flags) -c ' + n + '.cpp -o ../build/' + n + '.o\n' )

f.write('\n\nclean:')
f.write('\n\trm -rf ' + obj + '\n')

f.close()

