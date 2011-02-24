
list_mlib=`find ./mlib -type f -name '*.[c,h]pp'`
list_rt2=`find ./rt2 -type f -name '*.[c,h]pp'`
list_tests=`find ./tests -type f -name '*.[c,h]pp'`
list_all=`find . -type f -name '*.[c,h]pp'`
list_tex=`find . -type f -name '*.tex'`
list_python=`find . -type f -name '*.py'`

printf "\nmodule mlib:\n"
printf "Lines:   Count byte:      File name:\n"

for arg in $list_mlib 
do
cl=`cat $arg | wc -l`
sl=`cat $arg | wc -c`
name=`basename $arg`
printf "%5d %13d %5s %-30s\n" $cl $sl " " "$name"
done

printf "\nmodule rt2:\n"
printf "Lines:   Count byte:      File name:\n"

for arg in $list_rt2
do
cl=`cat $arg | wc -l`
sl=`cat $arg | wc -c`
name=`basename $arg`
printf "%5d %13d %5s %-30s\n" $cl $sl " " "$name"
done

printf "\nmodule tests:\n"
printf "Lines:   Count byte:      File name:\n"

for arg in $list_tests
do
cl=`cat $arg | wc -l`
sl=`cat $arg | wc -c`
name=`basename $arg`
printf "%5d %13d %5s %-30s\n" $cl $sl " " "$name"
done

printf "\nmodule docs:\n"
printf "Lines:   Count byte:      File name:\n"

for arg in $list_tex
do
cl=`cat $arg | wc -l`
sl=`cat $arg | wc -c`
name=`basename $arg`
printf "%5d %13d %5s %-30s\n" $cl $sl " " "$name"
done

printf "\nmodule python:\n"
printf "Lines:   Count byte:      File name:\n"

for arg in $list_python
do
cl=`cat $arg | wc -l`
sl=`cat $arg | wc -c`
name=`basename $arg`
printf "%5d %13d %5s %-30s\n" $cl $sl " " "$name"
done

printf "\nAll:\n"
all_l=`find . -type f -name '*.[c,h]pp' -exec cat {} \; | wc -l`
all_t=`find . -type f -name '*.tex' -exec cat {} \; | wc -l`
all_p=`find . -type f -name '*.py' -exec cat {} \; | wc -l`
all_c=`find . -type f -name '*.[c,h]pp' -exec cat {} \; | wc -c`
files=`find . -type f -name '*.[h,c]pp' | wc -l` 
echo "Total count source files : $files"
echo "Total lines source code : $all_l"
echo "Total lines docs : $all_t"
echo "Total lines python scripts : $all_p"
kb=`echo $all_c/1024 | bc `
echo "Total size source code  : $all_c byte = $kb KByte"
total=`echo $all_l+$all_t+$all_p | bc`
echo " "
echo "TOTAL LINE WORK: $total"

