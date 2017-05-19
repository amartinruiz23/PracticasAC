#!/bin/bash

echo "1 thread"
export OMP_NUM_THREADS=1

./pmm-OpenMP 100
./pmm-OpenMP 1500
echo "2 thread"
export OMP_NUM_THREADS=2

./pmm-OpenMP 100
./pmm-OpenMP 1500
echo "3 thread"
export OMP_NUM_THREADS=3

./pmm-OpenMP 100
./pmm-OpenMP 1500
echo "4 thread"
export OMP_NUM_THREADS=4

./pmm-OpenMP 100
./pmm-OpenMP 1500
