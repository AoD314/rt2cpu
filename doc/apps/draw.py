#!/usr/bin/python
# -*- coding: utf-8 -*-
from pylab import *
import subprocess
from os import *

def run(p,t):
	s = "./a.out " + str(p) + " " + str(t)
	output = str(popen(s, "r").read())
	return output[:-1]

x = []
y = []
for i in range(1, 300):
	print str(i) + " / 300"
	x = x + [i]
	y = y + [int(run(i, 128))]

plot(x,y)

print "done."

show()

x = []
y = []
for i in range(1, 101):
	print str(i) + " / 100"
	x = x + [i*600]
	y = y + [int(run(i*600, 8))]

plot(x,y)

print "done."

show()

