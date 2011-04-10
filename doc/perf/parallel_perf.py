#!/usr/bin/python2
# -*- coding: utf-8 -*-

import subprocess
import re, os

sc = [['-f', '60', '-a', '1', '-w', '640',   '-h', '480',  '-d', '1', '-l', '1', '-b'],
      ['-f', '35', '-a', '1', '-w', '1024',  '-h', '768',  '-d', '2', '-l', '1', '-b'],
      ['-f', '20', '-a', '2', '-w', '1400',  '-h', '1050', '-d', '4', '-l', '2', '-b'],
      ['-f', '10', '-a', '3', '-w', '1920',  '-h', '1080', '-d', '4', '-l', '2', '-b']
      ]

level = ['low', 'middle', 'hard', ' very hard']
perf = [[], [], [], []]

f = open("table_perf.tex", "wt")

st = 1
fn = 7

for step in range(4):
    f.write("\\begin{center}\n")
    f.write("\\begin{tabular}{|c|")
    for i in range(1, fn-st+1):
        f.write("c|")
    f.write("}\n")
    
    f.write("\\hline\n \\vbox{\\vspace{1mm}{\\hbox{\\qquad \\qquad Кол-во потоков}} ")
    f.write("\\vspace{3mm}\\hbox{Сложность сцены}} & ")
    for t in range(st, fn):
        f.write(" " + str(t) + " ")
        if t == fn-1:
            f.write("\\\\")
        else:
            f.write("&")
    f.write(" \n")
    
    for i in range(4):
        f.write("\\hline\n")
        f.write( str(level[i]) + " &")
        for t in range(st, fn):
                cmd = '../../build/rt2cpu -o ../../data/my_stul2.obj ' + " ".join(sc[i] + ['-t', str(t)])
                print (cmd)
                out = str(os.popen(cmd, "r").read())
                #out = "qwe = 22.232 fps\nqwe = 222.666 fps"
                pattern = re.compile(".*= (.*) fps")            
                ls = pattern.findall(out)
                vmax = -1
                for v in ls:
                    if vmax < float(v):
                        vmax = float(v)
                perf[i].append(vmax)
                f.write(" " + str(vmax) + " ")
                if t == fn-1:
                    f.write("\\\\")
                else:
                    f.write("&")
        f.write(" \n")
    
    f.write("\\hline\n")
    f.write("\\end{tabular}\n")
    f.write("\\end{center}\n\n")
    st += 6
    fn += 6
    
###############  

import matplotlib.pyplot as plt
import matplotlib.legend as legend  

from matplotlib import rc 
rc('font',**{'family':'serif'}) 
rc('text', usetex=True) 
rc('text.latex',unicode=True)
rc('text.latex',preamble="\\usepackage[utf8]{inputenc}")
rc('text.latex',preamble="\\usepackage[russian]{babel}") 

ax = plt.subplot(1,1,1)

plt.plot(range(1, 25), perf[0], 'g-',  aa=True, label=level[0])
plt.plot(range(1, 25), perf[1], 'b+',  aa=True, label=level[1])
plt.plot(range(1, 25), perf[2], 'ro',  aa=True, label=level[2])
plt.plot(range(1, 25), perf[3], 'bs-', aa=True, label=level[3])

ax.legend(loc='upper right')

plt.ylabel(unicode('fps', 'utf-8'))
plt.xlabel(unicode('Количесво активных потоков', 'utf-8'))
plt.title (unicode('Эффективность реализации параллельного алгоритма', 'utf-8'))
plt.grid(True)
plt.savefig("table_perf.eps")
    