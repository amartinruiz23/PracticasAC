#!/bin/bash
for ((N=16384;N<2*67108864;N=N*2))
do
./SumaVectoresSection $N >> salida_local_section.txt
done
