P=sfs
C='sfs_test.c disk_emu.c'
FLAGS='-o2 -Wall'

gcc $FLAGS $C -o $P
./$P
rm $P
