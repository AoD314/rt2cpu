
import os

num_cpu = int(os.environ.get('NUM_CPU', 12))
SetOption('num_jobs', num_cpu)

env  = Environment(CC = 'g++', CCFLAGS = '-msse4.2 -fopenmp -g -ggdb')
perf = Environment(CC = 'g++', CCFLAGS = '-msse4.2 -fopenmp -O3')

mlib_src   = Glob('mlib/*.cpp')
rt2_src    = Glob('rt2/*.cpp')
rt2cpu_src = Glob('rt2cpu/*.cpp')

tests_src_mlib   = ['tests/correct_tests_mlib.cpp']
tests_src_rt2cpu = ['tests/correct_tests_rt2cpu.cpp']
perf_src = ['tests/performance_tests_mlib.cpp']
cmp_src  = ['tests/cmp_tests.cpp']


perf.SharedLibrary('./build/mlib.so', mlib_src)
perf.SharedLibrary('./build/rt2.so', rt2_src, CPPPATH='./mlib/')

perf.Program('./build/rt2cpu', rt2cpu_src, CPPPATH=['./mlib/', './rt2/'], LIBS=['SDL', 'gomp', 'mlib', 'rt2'], LIBPATH='./build')

perf.Program('./build/correct_tests_mlib',  tests_src_mlib,   CPPPATH='./mlib/',             LIBS=['gomp', 'mlib'], LIBPATH='./build')
perf.Program('./build/correct_tests_rt2',   tests_src_rt2cpu, CPPPATH=['./mlib/', './rt2/'], LIBS=['gomp', 'mlib', 'rt2'], LIBPATH='./build')

perf.Program('./build/performance_tests_mlib', perf_src, CPPPATH='./mlib/', LIBS=['gomp', 'mlib'], LIBPATH='./build')
perf.Program('./build/cmp_tests', cmp_src, CPPPATH='./mlib/', LIBS=['gomp', 'mlib'], LIBPATH='./build')


