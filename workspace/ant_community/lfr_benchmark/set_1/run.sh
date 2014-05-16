#!/bin/bash
# first argument - fileName, second - output file \

echo "$1 $2"
for i in {1..50}
do
	echo "Run $i"
	#"/home/mua193/Desktop/lfr_benchmark/set_1/ant_community" $1 >> seed
	read -ra values <<< `./ant_community $1`
	seed=${values[0]}
	nmi=`./nmi.r 5000_s_0.2_comm.dat /home/mua193/Desktop/NMI/output.dat`
	echo $nmi-$seed $'\r' >> $2
done
