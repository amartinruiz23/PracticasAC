#!/bin/bash
for ((N=16384;N<2*67108864;N=N*2))
do
./SumaVectoresSecuencial $N >> salida_atc_secuencial.txt
done
