#!/bin/bash
for ((N=16384;N<2*67108864;N=N*2))
do
./SumaVectoresFor $N >> salida_atcgrid_for.txt
done
