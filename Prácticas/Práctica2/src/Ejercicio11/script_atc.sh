#!/bin/bash
for ((i=1;i<=12;i=i+1))
do
    echo "NUMERO DE THREADS: $i" >> dat.txt
    export OMP_NUM_THREADS=$i
    for((j=1000;j<=10000;j=j+1000))
    do
      ./pmv-OpenMP-reduction $j >> dat.txt
    done
done
