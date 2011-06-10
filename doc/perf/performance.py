#!/usr/bin/python2
# -*- coding: utf-8 -*-

import subprocess
import re, os

def calc(filename, param, label_p, label_t, label_c):
    sc = [
    ['-f', '40', '-w', '512',   '-h', '512',  '-b', '-t', '12'],
    ['-f', '30', '-w', '800',   '-h', '600',  '-b', '-t', '12'],
    ['-f', '20', '-w', '1024',  '-h', '768',  '-b', '-t', '12'],
    ['-f', '10', '-w', '1920',  '-h', '1080', '-b', '-t', '12']
    ]
    
    if label_p != "-a":
        sc[0] += ['-a', '1']
        sc[1] += ['-a', '2']
        sc[2] += ['-a', '3']
        sc[3] += ['-a', '3']        

    if label_p != "-d":
        sc[0] += ['-d', '1']
        sc[1] += ['-d', '2']
        sc[2] += ['-d', '4']
        sc[3] += ['-d', '8']        

    if label_p != "-l":
        sc[0] += ['-l', '1']
        sc[1] += ['-l', '1']
        sc[2] += ['-l', '2']
        sc[3] += ['-l', '2']        
    
    level = ['low', 'middle', 'hard', ' very hard']
    perf = [[], [], [], []]
    f = open(filename + ".tex", "wt")
    f.write("\\begin{center}\n")
    f.write("\\begin{longtable}{|c|p{2cm}|p{2cm}|p{2cm}|p{2cm}|}\n")
    f.write("\\hline & \\multicolumn{4}{c|}{Сложность сцены (fps)} \\\\ \n")
    f.write("\\hline " + label_t + " & " + " & ".join(level) + "\\\\ \n")
    for p in param:
        f.write("\\hline ")
        f.write(str(p) + " & ")
        for j in range(4):
            cmd = '../../build/rt2cpu -o ../../data/my_stul2.obj ' + " ".join(sc[j] + [label_p, str(p)])
            print (cmd)
            out = str(os.popen(cmd, "r").read())
            pattern = re.compile(".*= (.*) fps")            
            ls = pattern.findall(out)
            vmax = -1
            for v in ls:
                if vmax < float(v):
                    vmax = float(v)
            perf[j].append(vmax)
            f.write(" " + '{0:.3f}'.format(vmax) + " ")
            if j == 3:
                f.write("\\\\ \n")
            else:
                f.write("&")
    f.write("\\hline\n")
    f.write("\\caption{" + label_c + "}\\label{tab:" + filename + "}")
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
    
    plt.clf()
    ax = plt.subplot(1,1,1)
    #ax.set_yscale('log')
    
    plt.plot(param, perf[0], 'g-',  aa=True, label=level[0])
    plt.plot(param, perf[1], 'b+-', aa=True, label=level[1])
    plt.plot(param, perf[2], 'ro-', aa=True, label=level[2])
    plt.plot(param, perf[3], 'gs-', aa=True, label=level[3])
    
    ax.legend(loc='best')
    
    plt.ylabel(unicode('fps', 'utf-8'))
    plt.xlabel(unicode(label_t, 'utf-8'))
    plt.grid(True)
    plt.savefig( filename + ".pdf")

if __name__ == "__main__":
    calc("performance_aa",    [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18],  "-a",  "Кол-во субпикселей", "Зависимость скорости работы от количества субпикселей")
    calc("performance_light", [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18],  "-l",  "Кол-во источников света", "Зависимость скорости работы от количества источников света")
    calc("performance_bvh",   [8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8129, 16384],    "-bo", "Кол-во объектов в листе BVH", "Зависимость скорости работы от количества объектов в листе BVH")
    calc("performance_d",     [1, 2, 4, 8, 8, 16, 32, 64, 128, 256, 512, 1024],  "-d",  "Глубина рекурсии алгоритма", "Зависимость скорости работы от глубины рекурсии")
    calc("performance_gs",    [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12],  "-g",  "Кол-во порций данных на один поток", "Зависимость скорости работы от количества порций данных на один поток")
    