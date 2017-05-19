#!/bin/bash
for ((N=16384;N<=67108865;N=N*2))
do
    (time  ./SumaVectoresFor $N ) 2>>salida_for_atc.txt
done
