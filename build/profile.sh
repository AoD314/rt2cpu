valgrind --tool=callgrind --dump-instr=yes --collect-jumps=yes --collect-bus=yes --simulate-cache=yes --L2=262144,8,64 --I1=32768,4,64 --D1=32768,8,64 --time-stamp=yes ./rt2cpu -f 1 -w 1024 -h 1024 -d 2 -l 2 -a 6
# --LL=12582912,16,64 --I1=32768,4,64 --D1=32768,8,64 
