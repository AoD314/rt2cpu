#!/usr/bin/python
# -*- coding: utf-8 -*-

import subprocess, os
import matplotlib.pyplot as plt
import matplotlib.legend as legend
import threading as th
import time

from matplotlib import rc 
rc('font',**{'family':'serif'}) 
rc('text', usetex=True) 
rc('text.latex',unicode=True) 
rc('text.latex',preamble='\usepackage[utf8]{inputenc}') 
rc('text.latex',preamble='\usepackage[russian]{babel}') 

def progressbar(p, m):
	print chr(27) + '[A' + "progress " + m + ": " + str(p) + "% "

def run(p,t):
	s = "./cmp_virtual_method " + str(p) + " " + str(t)
	output = str(os.popen(s, "r").read())
	return output[:-1]

def pcall(r, ind, x, mn, av):
	for j in range(len(ind)):
		i = ind[j]
		v = r[j]
		x[i] = v * 4
		s = run(v, 1024 * 512).split(' ')
		mn[i] = int(s[0])
		av[i] = int(s[1])

def create_test(f, r):
	l = len(r)
	x  = range(l)
	mn = range(l)
	av = range(l)

	plt.clf()

	N = 6
	
	lr = []
	tt = []
	for i in range(N):
		lr = lr + [r[i::N]]
		tt = tt + [th.Thread(target=pcall, args=(lr[i], list(x[i::N]), x, mn, av))]
		tt[i].daemon = True
		tt[i].start()

	for i in range(N):
		tt[i].join()

	ax = plt.subplot(1,1,1)
	p1, = plt.plot(x, mn, 'gs-', aa=True, label='min')
	p2, = plt.plot(x, av, 'b^-', aa=True, label='avg')
	ax.legend(loc='upper right')

	plt.ylabel(unicode('Накладные расходы (в \%)', 'utf-8'))
	plt.xlabel(unicode('Количество объектов в массиве', 'utf-8'))
	#plt.title (unicode('Накладные расходы при наследование', 'utf-8'))
	plt.grid(True)
	plt.savefig(f)

if __name__ == '__main__':
	t = time.time()
	create_test('compare_virtual_methods_l.pdf', range(1,31))
	create_test('compare_virtual_methods_b.pdf', range(1,501,5))
	t = (time.time() - t)
	print "TIME : " + str(t)

