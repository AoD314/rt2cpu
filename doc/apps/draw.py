#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys, subprocess, os
import matplotlib.pyplot as plt

#from matplotlib import rcParams
#rcParams['text.usetex']=True
#rcParams['text.latex.unicode']=True

from matplotlib import rc 
rc('font',**{'family':'serif'}) 
rc('text', usetex=True) 
rc('text.latex',unicode=True) 
rc('text.latex',preamble='\usepackage[utf8]{inputenc}') 
rc('text.latex',preamble='\usepackage[russian]{babel}') 

def progressbar(p):
	print chr(27) + '[A' + "progress : " + str(p) + "%"

def run(p,t):
	s = "./cmp_virtual_method " + str(p) + " " + str(t)
	output = str(os.popen(s, "r").read())
	return output[:-1]

x = []
y = []
r = range(1,91)
for i in r:
	progressbar(i * 100 / len(r))
	x = x + [i]
	y = y + [int(run(i, 1024 * 1024))]

plt.plot(x, y, aa=True)
plt.ylabel(unicode('Накладные расходы (в \%)', 'utf-8'))
plt.xlabel(unicode('Количесво объектов в массиве', 'utf-8'))
plt.title (unicode('Накладные расходы при наследование', 'utf-8'))
plt.grid(True)
plt.savefig("compare_virtual_methods.eps")

print "done."
