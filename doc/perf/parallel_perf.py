#!/usr/bin/python2
# -*- coding: utf-8 -*-

import subprocess
import re, os

sc = [['-f', '60', '-a', '1', '-w', '640',   '-h', '480',  '-d', '1', '-l', '1', '-b'],
      ['-f', '30', '-a', '1', '-w', '1024',  '-h', '768',  '-d', '2', '-l', '1', '-b'],
      ['-f', '20', '-a', '2', '-w', '1400',  '-h', '1050', '-d', '4', '-l', '2', '-b'],
      ['-f', '10', '-a', '3', '-w', '1920',  '-h', '1080', '-d', '4', '-l', '2', '-b']
      ]

level = ['low', 'middle', 'hard', ' very hard']
perf = [[], [], [], []]

f = open("table_perf.tex", "wt")

th = 24

f.write("\\begin{center}\n")
f.write("\\begin{longtable}{|c|p{2cm}|p{2cm}|p{2cm}|p{2cm}|}\n")
f.write("\\hline & \\multicolumn{4}{c|}{Сложность сцены (fps)} \\\\ \n")
f.write("\\hline Кол-во потоков & " + " & ".join(level) + "\\\\ \n")

for t in range(1, th + 1):
    f.write("\\hline ")
    f.write(str(t) + " & ")
    for j in range(4):
        cmd = '../../build/rt2cpu -o ../../data/my_stul2.obj ' + " ".join(sc[j] + ['-t', str(t)])
        print (cmd)
        out = str(os.popen(cmd, "r").read())
        #out = "qwe = 22.232 fps\nqwe = 222.666 fps"
        pattern = re.compile(".*= (.*) fps")            
        ls = pattern.findall(out)
        vmax = -1
        for v in ls:
            if vmax < float(v):
                vmax = float(v)
        perf[j].append(vmax)
        f.write(" " + str(vmax) + " ")
        if j == 3:
            f.write("\\\\ \n")
        else:
            f.write("&")
f.write("\\hline\n")
f.write("\\end{longtable}\n")
f.write("\\end{center}\n\n")
    
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

plt.plot(range(1, th+1), perf[0], 'g-',  aa=True, label=level[0])
plt.plot(range(1, th+1), perf[1], 'b+-',  aa=True, label=level[1])
plt.plot(range(1, th+1), perf[2], 'ro-',  aa=True, label=level[2])
plt.plot(range(1, th+1), perf[3], 'gs-', aa=True, label=level[3])

ax.legend(loc='best')

plt.ylabel(unicode('fps', 'utf-8'))
plt.xlabel(unicode('Количесво активных потоков', 'utf-8'))
plt.title (unicode('Эффективность реализации параллельного алгоритма', 'utf-8'))
plt.grid(True)
plt.savefig("table_perf.eps")

plt.clf()

for i in range(4):
    val = perf[i][0]
    for j in range(len(perf[i])):
        perf[i][j] = float(perf[i][j]) / float(val)

ax = plt.subplot(1,1,1)

plt.plot(range(1, th+1), perf[0], 'g-',  aa=True, label=level[0])
plt.plot(range(1, th+1), perf[1], 'b+-',  aa=True, label=level[1])
plt.plot(range(1, th+1), perf[2], 'ro-',  aa=True, label=level[2])
plt.plot(range(1, th+1), perf[3], 'gs-', aa=True, label=level[3])

ax.legend(loc='lower right')

plt.ylabel(unicode('Ускорение', 'utf-8'))
plt.xlabel(unicode('Количесво активных потоков', 'utf-8'))
plt.title (unicode('Эффективность реализации параллельного алгоритма', 'utf-8'))
plt.grid(True)
plt.savefig("table_perf_eff.eps")
    