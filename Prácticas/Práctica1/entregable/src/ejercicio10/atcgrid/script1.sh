#!/bin/bash
for ((N=16384;N<2*67108864;N=N*2))
do
./SumaVectoresSection $N >> salida_atcgrid_section.txt
done
