P=sfs
C='sfs_test.c disk_emu.c'
FLAGS='-o2 -Wall'

echo Compiling...
gcc $FLAGS $C -o $P

if [ "${1}" = "debug" ]
then
	echo Debugging...	
	gdb ./$P
else
	echo ${1}; echo Running...
	./$P
fi
rm $P disk.sfs
