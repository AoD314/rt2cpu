#!/usr/bin/python

import os

print "cpp -> tex"
os.system('cd ./src/; python ./convert-cpp-to-tex.py')



print "generate docs"
os.system('texi2pdf rt2cpu.tex')
os.system('texi2pdf rt2cpu.tex')

