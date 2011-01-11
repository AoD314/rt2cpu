
import os

#num_cpu = int(os.environ.get('NUM_CPU', 12))
#SetOption('num_jobs', num_cpu)

env = Environment(CC = 'g++', CCFLAGS = '-msse3 -msse4.2 -fopenmp')

mlib_src = Glob('mlib/*.cpp')
rt2_src = Glob('rt2/*.cpp')

env.SharedLibrary('./build/mlib.so', mlib_src)

env.Program('./build/rt2cpu', rt2_src, CPPPATH='./mlib/', LIBS=['SDL', 'gomp', 'mlib'], LIBPATH='./build')


