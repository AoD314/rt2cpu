
import os, sys

num_cpu = int(os.environ.get('NUM_CPU', 12))
SetOption('num_jobs', num_cpu)

def print_cmd_line(s, target, src, env):
	#sys.stdout.write(" (CC) %s \n"% (' and '.join([str(x) for x in target])))
	sys.stdout.write("%s\n"%s); # by default

optimize  = '-finline-functions -ftree-loop-optimize -foptimize-sibling-calls'

mode = 'r'  # [ r - release], [d - debug], [p - profile], [w - warrning]

flgs = ''

if 'd' in mode:
	flgs += ' -g -ggdb -O0 '

if 'r' in mode:
        flgs += ' -O3 ' + optimize

if 'p' in mode:
        flgs += ' -O3 -g ' + optimize

if 'w' in mode:
	flgs += ' -Wall -Wextra -pedantic -Weffc++ -Wconversion -Wsign-conversion -Wold-style-cast ' 
	flgs += ' -Wunreachable-code -Woverloaded-virtual -Wctor-dtor-privacy -Wnon-virtual-dtor ' 

e = Environment(CC = 'g++')
e.Append(CCFLAGS = '-msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -std=c++0x -fopenmp -msahf -fstack-protector-all')
e.Append(CCFLAGS = flgs)
e.Append(LINKFLAGS = '-fopenmp')

e['PRINT_CMD_LINE_FUNC'] = print_cmd_line

mlib_src   = Glob('mlib/*.cpp')
rt2_src    = Glob('rt2/*.cpp')
rt2cpu_src = Glob('rt2cpu/*.cpp')

tests_src_mlib   = ['tests/correct_tests_mlib.cpp']
tests_src_rt2cpu = ['tests/correct_tests_rt2cpu.cpp']
perf_src = ['tests/performance_tests_mlib.cpp']
cmp_src  = ['tests/cmp_tests.cpp']


#StaticLibrary
#SharedLibrary
e.StaticLibrary('./build/mlib', mlib_src)
e.StaticLibrary('./build/rt2', rt2_src, CPPPATH='./mlib/', LIBS=['gomp', 'tbb', 'mlib'])

e.Program('./build/rt2cpu', rt2cpu_src, CPPPATH=['./mlib/', './rt2/'], LIBS=['SDL', 'gomp', 'rt2', 'mlib'], LIBPATH='./build')

e.Program('./build/correct_tests_mlib',  tests_src_mlib,   CPPPATH='./mlib/',             LIBS=['gomp', 'mlib'], LIBPATH='./build')
e.Program('./build/correct_tests_rt2',   tests_src_rt2cpu, CPPPATH=['./mlib/', './rt2/'], LIBS=['gomp', 'rt2', 'mlib'], LIBPATH='./build')
e.Program('./build/performance_tests_mlib', perf_src, CPPPATH=['./mlib/','./rt2/'], LIBS=['gomp', 'rt2', 'mlib'], LIBPATH='./build')
e.Program('./build/cmp_tests', cmp_src, CPPPATH='./mlib/', LIBS=['gomp', 'mlib'], LIBPATH='./build')

e.Program('doc/apps/cmp_virtual_method',  ['doc/apps/cmp_virtual_method.cpp'],  CPPPATH='./mlib/', LIBS=['gomp', 'mlib'], LIBPATH='./build')
e.Program('doc/apps/cmp_et',  ['doc/apps/cmp_et.cpp'],  CPPPATH='./mlib/', LIBS=['gomp', 'mlib'], LIBPATH='./build')

