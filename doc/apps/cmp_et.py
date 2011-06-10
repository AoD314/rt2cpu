#!/usr/bin/python2
# -*- coding: utf-8 -*-

import subprocess
import re, os


def app_run(i,m):
	cmd = './cmp_et -c ' + str(i) + ' -m ' + str(m) + ' | grep time ' 
	out = str(os.popen(cmd, "r").read())
	#print('out >' + out + 'EOF')
	pattern = re.compile("time: (.*)/(.*)")
	ls = pattern.findall(out)
	if len(ls) == 0:
		return 0, 0, -1
	else:
		return ls[0][0], ls[0][1], 0

mode = ['min', 'avg', 'max', 'sum']

f = open("table_cmp_et.tex", "wt")

f.write("\\begin{center}\n")
f.write("\\begin{longtable}{|c|c|c|c|c|}\n")
f.write("\\hline & \\multicolumn{4}{c|}{Режим подсчета} \\\\ \n")
f.write("\\hline \\vbox{\\hbox{\\strut Кол-во}\\hbox{итераций}} & " + " & ".join(mode) + "\\\\ \n")
f.write("\\hline ")

for i in range(1, 8):
	f.write('$10^'+str(i) + "$ & ")
	for m in range(4):
		i1, i2,	err = -1, -1, -1
		while err == -1:
			i1, i2, err = app_run(10 ** i , m)

		res = '{0:.2f}'.format(float(i2) / float(i1))
		f.write('$\\cfrac{\\strut ' + str(i2)+ '}{\\strut ' + str(i1)+ '} = ' + res +' $')

		if m == 3:
			f.write("\\\\ \n\\hline ")
		else:
			f.write(" & ")

#f.write("\\hline\n")
f.write("\\caption{Времени выполнения арифметических выражений}\\label{tab:cmp_et}")
f.write("\\end{longtable}\n")
f.write("\\end{center}\n\n")
    
###############  
