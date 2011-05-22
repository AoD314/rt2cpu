#!/usr/bin/python

import sys
import os
import re

########################################

files = []
names = os.listdir('/work/projects/rt2cpu/doc/src/')
for name in names:
	if (name.find('.cpp') != -1):
		files.append(name[:-4])
		#print name[:-4]

########################################

color_key = 'blue'
keyword = ['asm', 'auto', 'break', 'case', 'catch', 'char', 'class', 'const', 'continue', 'default', 'do', 'double', 'else', 'enum', 'extern', 'float', 'for', 'friend', 'goto', 'if', 'inline', 'int', 'long', 'namespace', 'new', 'operator', 'private', 'protected', 'public', 'register', 'return', 'short', 'signed', 'sizeof', 'static', 'struct', 'switch', 'template', 'this', 'throw', 'try', 'typedef', 'typeid', 'typename', 'union', 'unsigned', 'using', 'virtual', 'void', 'volatile', 'while']

dic_replace = {}

def gettex(str):
	if (str in keyword):
		return '\\textcolor{' + color_key + '}{' + str + '}'
  
	if (str in ['{', '}', '#', '%', '&', '$', '_', ' ']):
		return '\\' + str
 
 	if (str == '~'):
		return '$\\sim$'

	if (str == '\n'):
		return '\\\\\n'
	
	if (str == '\\'):
		return '$\\backslash$'
	
	if (str == "..."):
		return ' \dots '
	
	if (str in ['<', '>', '=']):
		return '$'+ str +'$'

	if (str in ['\t']):
		return '\\ \\ \\ \\ '
	
	if (str in ['"']):
		return '\'\''

	return str

########################################

chars = ['<', '>', '=', ' ']

print "total files: " + str(len(files))
iii = 0

for file_n in files:
	print '[' + str(iii) + '] converting ' + file_n + ' ...'
	iii = iii + 1
	file = open( file_n + '.cpp')
	text = ''
	j = 1
	for s in file:

		js = str(j)
		if (j<10):
			js = '0' + js

		text = text + '\mbox{} ' + js + ': '
		
		try:
			while (s != ''):
				i = 0
			
				if (s[i] in 'qwertyuiopasdfghjklzxcvbnmQWERTYUIOPLKJHGFDSAZXCVBNM'):
					token = ''
					while (s[i] in 'qwertyuiopasdfghjklzxcvbnmQWERTYUIOPLKJHGFDSAZXCVBNM'):
						token = token + s[i]
						i = i + 1
					text = text + gettex(token)
					#print '{' + token + ' -> '  + gettex(token) + '}'
					s = s[i:]
				else:
					if (s[i:i+3] == "..."):
						text = text = gettex(s[i:i+3])
						#print '{' + s[i] + ' -> '  + gettex(s[i:i+3]) + '}'
						i = i + 3
						s = s[i:]
					else:
						text = text + gettex(s[i])
						#print '{' + s[i] + ' -> '  + gettex(s[i]) + '}'
						i = i + 1
						s = s[i:]
		except Exception:
			s = ''

		j = j + 1


	text = '\\spacing{0.8}{\\noindent \\tt \\footnotesize \n' + text[:-3] + '}\\spacing{\\heightline}'

	f = open( file_n + '.tex' , 'w')
	f.write(text)
	f.close()

print 'done.'
