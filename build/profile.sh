valgrind --tool=callgrind --dump-instr=yes --collect-jumps=yes --collect-bus=yes --simulate-cache=yes --L2=262144,8,64 --I1=32768,4,64 --D1=32768,8,64 --time-stamp=yes ./rt2cpu -t 12 -w 512 -h 512 -a 3 -d 2 -f 1 -g 8192
# --LL=12582912,16,64 --I1=32768,4,64 --D1=32768,8,64 
