#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys, subprocess, os
import matplotlib.pyplot as plt
import matplotlib.legend as legend
import multiprocessing as mp


from matplotlib import rc 
rc('font',**{'family':'serif'}) 
rc('text', usetex=True) 
rc('text.latex',unicode=True) 
rc('text.latex',preamble='\usepackage[utf8]{inputenc}') 
rc('text.latex',preamble='\usepackage[russian]{babel}') 

def progressbar(p, m):
	print chr(27) + '[A' + "progress " + m + ": " + str(p) + "% "

def progress(p, m):
	print "progress " + m + ": " + str(p) + "% "

def run(p,t):
	s = "./cmp_virtual_method " + str(p) + " " + str(t)
	output = str(os.popen(s, "r").read())
	return output[:-1]

def create_test(f, r, k):
	x  = []
	mn = []
	av = []
	
	com = 16 #  1<= com <= 64
	if k==1: com = 32
	if k==2: com = 16
	if k==3: com = 2

	for i in r:
		progress(i * 100 / len(r), '<' + str(k) + '>')
		x = x + [i*k]
		s = run(i*k, com ** 4).split(' ')
		mn = mn + [int(s[0])]
		av = av + [int(s[1])]

	ax = plt.subplot(1,1,1)
	p1, = plt.plot(x, mn, 'gs-', aa=True, label='min')
	p2, = plt.plot(x, av, 'b^-', aa=True, label='avg')
	ax.legend(loc='upper right')

	plt.ylabel(unicode('Накладные расходы (в \%)', 'utf-8'))
	plt.xlabel(unicode('Количесво объектов в массиве', 'utf-8'))
	plt.title (unicode('Накладные расходы при наследование', 'utf-8'))
	plt.grid(True)
	plt.savefig(f)

if __name__ == '__main__':
	mp.Process(target=create_test, args=('compare_virtual_methods_s.eps', range(1,51), 1)).start()
	mp.Process(target=create_test, args=('compare_virtual_methods_m.eps', range(1,51), 100)).start()
	mp.Process(target=create_test, args=('compare_virtual_methods_b.eps', range(1,51), 10000)).start()
	
	print "done."
