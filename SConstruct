
import os, sys

num_cpu = int(os.environ.get('NUM_CPU', 12))
SetOption('num_jobs', num_cpu)

def print_cmd_line(s, target, src, env):
	sys.stdout.write(" (CC) %s \n"% (' and '.join([str(x) for x in target])))
	#sys.stdout.write("%s\n"%s); # by default

mode = 'r'  # [d - debug], [p - profile], [w - warrning]

flgs = ''

if 'd' in mode:
	flgs += ' -g -ggdb -O0 '
else:
	flgs += ' -O3 -ffast-math '

if 'p' in mode:
	flgs += ' -pg '

if 'w' in mode:
	flgs += ' -Wall -Wextra -pedantic -Weffc++ -Wconversion -Wsign-conversion -Wold-style-cast ' 
	flgs += ' -Wunreachable-code -Woverloaded-virtual -Wctor-dtor-privacy -Wnon-virtual-dtor ' 

e = Environment(CC = 'g++')
e.Append(CCFLAGS = '-msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -fopenmp -msahf -fstack-protector-all')
e.Append(CCFLAGS = flgs)
e.Append(LINKFLAGS = '-fopenmp')
e.Append(LINKFLAGS = '-Wl,-R./build')

e['PRINT_CMD_LINE_FUNC'] = print_cmd_line

mlib_src   = Glob('mlib/*.cpp')
rt2_src    = Glob('rt2/*.cpp')
rt2cpu_src = Glob('rt2cpu/*.cpp')

tests_src_mlib   = ['tests/correct_tests_mlib.cpp']
tests_src_rt2cpu = ['tests/correct_tests_rt2cpu.cpp']
perf_src = ['tests/performance_tests_mlib.cpp']
cmp_src  = ['tests/cmp_tests.cpp']


e.SharedLibrary('./build/mlib.so', mlib_src)
e.SharedLibrary('./build/rt2.so', rt2_src, CPPPATH='./mlib/')

e.Program('./build/rt2cpu', rt2cpu_src, CPPPATH=['./mlib/', './rt2/'], LIBS=['SDL', 'gomp', 'mlib', 'rt2'], LIBPATH='./build')

e.Program('./build/correct_tests_mlib',  tests_src_mlib,   CPPPATH='./mlib/',             LIBS=['gomp', 'mlib'], LIBPATH='./build')
e.Program('./build/correct_tests_rt2',   tests_src_rt2cpu, CPPPATH=['./mlib/', './rt2/'], LIBS=['gomp', 'mlib', 'rt2'], LIBPATH='./build')
e.Program('./build/performance_tests_mlib', perf_src, CPPPATH=['./mlib/','./rt2/'], LIBS=['gomp', 'mlib', 'rt2'], LIBPATH='./build')
e.Program('./build/cmp_tests', cmp_src, CPPPATH='./mlib/', LIBS=['gomp', 'mlib'], LIBPATH='./build')

e.Program('doc/apps/cmp_virtual_method',  ['doc/apps/cmp_virtual_method.cpp'],  CPPPATH='./mlib/', LIBS=['gomp', 'mlib'], LIBPATH='./build')

