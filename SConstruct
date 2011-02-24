
import os

num_cpu = int(os.environ.get('NUM_CPU', 12))
SetOption('num_jobs', num_cpu)

wall = '-Wunreachable-code -Wall -Wextra -pedantic -Weffc++ -Wconversion -Wsign-conversion -Woverloaded-virtual -Wctor-dtor-privacy -Wold-style-cast -Wnon-virtual-dtor'

env    = Environment(CC = 'g++', CCFLAGS = '-msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -fopenmp -g -ggdb -O0 -msahf -fstack-protector-all')
env_w  = Environment(CC = 'g++', CCFLAGS = '-msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -fopenmp -g -ggdb -O0 -msahf -fstack-protector-all -Wunreachable-code -Wall -Wextra -pedantic -Weffc++ -Wconversion -Wsign-conversion -Woverloaded-virtual -Wctor-dtor-privacy -Wold-style-cast -Wnon-virtual-dtor')
perf   = Environment(CC = 'g++', CCFLAGS = '-msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -fopenmp -O3 -msahf -fstack-protector-all')
perf_d = Environment(CC = 'g++', CCFLAGS = '-msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -fopenmp -O3 -g -ggdb -msahf -fstack-protector-all')

mlib_src   = Glob('mlib/*.cpp')
rt2_src    = Glob('rt2/*.cpp')
rt2cpu_src = Glob('rt2cpu/*.cpp')

tests_src_mlib   = ['tests/correct_tests_mlib.cpp']
tests_src_rt2cpu = ['tests/correct_tests_rt2cpu.cpp']
perf_src = ['tests/performance_tests_mlib.cpp']
cmp_src  = ['tests/cmp_tests.cpp']

e = env
l = env
#l = env_w

l.SharedLibrary('./build/mlib.so', mlib_src)
l.SharedLibrary('./build/rt2.so', rt2_src, CPPPATH='./mlib/')

e.Program('./build/rt2cpu', rt2cpu_src, CPPPATH=['./mlib/', './rt2/'], LIBS=['SDL', 'gomp', 'mlib', 'rt2'], LIBPATH='./build')

e.Program('./build/correct_tests_mlib',  tests_src_mlib,   CPPPATH='./mlib/',             LIBS=['gomp', 'mlib'], LIBPATH='./build')
e.Program('./build/correct_tests_rt2',   tests_src_rt2cpu, CPPPATH=['./mlib/', './rt2/'], LIBS=['gomp', 'mlib', 'rt2'], LIBPATH='./build')

e.Program('./build/performance_tests_mlib', perf_src, CPPPATH=['./mlib/','./rt2/'], LIBS=['gomp', 'mlib', 'rt2'], LIBPATH='./build')
e.Program('./build/cmp_tests', cmp_src, CPPPATH='./mlib/', LIBS=['gomp', 'mlib'], LIBPATH='./build')

e.Program('doc/apps/cmp_virtual_method',  ['doc/apps/cmp_virtual_method.cpp'],  CPPPATH='./mlib/', LIBS=['gomp', 'mlib'], LIBPATH='./build')

