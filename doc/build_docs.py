#!/usr/bin/python

import os

print "compiling ..."
os.system('cd ..; scons -c; scons')

print "cpp -> tex"
os.system('cd ./src/; python ./convert-cpp-to-tex.py')

print "create pattern"
os.system('cd ./imgs/; python aa_example.py')
os.system('cd ./imgs/; python aa_pattern.py')

print "create compare"
os.system('cd ./apps/; python ./cmp_virtual_method.py')
os.system('cd ./apps/; python ./cmp_et.py')

print "create table parallel perfrormance "
os.system('cd ./perf/; python ./parallel_perf.py')

print "generate docs"
os.system('texi2pdf rt2cpu.tex')
os.system('texi2pdf rt2cpu.tex')

