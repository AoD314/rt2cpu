#!/usr/bin/python3

import subprocess
import re

sc = [['-f', '50', '-a', '1', '-w', '640',   '-h', '480',  '-d', '1', '-l', '1'],
      ['-f', '20', '-a', '1', '-w', '1024',  '-h', '768',  '-d', '2', '-l', '1'],
      ['-f', '10', '-a', '2', '-w', '1400',  '-h', '1050', '-d', '4', '-l', '2'],
      ['-f', '2',  '-a', '3', '-w', '1920',  '-h', '1080', '-d', '4', '-l', '2']
      ]

level = ['low', 'middle', 'hard', ' very hard']

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
                out = subprocess.getoutput(cmd)
                #out = "qwe = 22.232 fps\nqwe = 222.666 fps"
                pattern = re.compile(".*= (.*) fps")            
                ls = pattern.findall(out)
                vmax = -1
                for v in ls:
                    if vmax < float(v):
                        vmax = float(v)            
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