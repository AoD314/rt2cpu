#!/usr/bin/python
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import numpy as np
import math

def add_a(x,y, num):
  x = [i+num for i in x]
  return x,y

cnt = 3

plt.figure(num=None, figsize=(2, 1), dpi=92)
plt.grid(False)

gs = gridspec.GridSpec(1, 2)
ax1 = plt.subplot(gs[:, 0])
ax2 = plt.subplot(gs[:, 1])

ax1.get_xaxis().set_visible(False)
ax1.get_yaxis().set_visible(False)
ax2.get_xaxis().set_visible(False)
ax2.get_yaxis().set_visible(False)

###########################################

th = [i*2*3.1415926/(360) for i in np.arange(0, 360, 360/(cnt**2))]
x = [ (math.cos(i) + 1)/2 for i in th]
y = [ (math.sin(i) + 1)/2 for i in th]
ax1.plot(x,y, 'bo')

###########################################

lx = [ (i + 0.0) / (cnt-1) for i in np.arange(0,cnt,1) ]
ly = [ (i + 0.0) / (cnt-1) for i in np.arange(0,cnt,1) ]
x = []
y = []
for i in lx:
  for j in ly:
    x = x + [i]
    y = y + [j]
ax2.plot(x,y, 'bo')

###########################################

plt.savefig('aa_pattern.eps')

#plt.show()
