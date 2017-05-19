#!/bin/bash

echo "Static por defecto"
export OMP_SCHEDULE="static"
./pmtv-paralelo 5000
echo "Static chunk 1"
export OMP_SCHEDULE="static,1"
./pmtv-paralelo 5000
echo "Static chunk 64"
export OMP_SCHEDULE="static,64"
./pmtv-paralelo 5000
echo "Dynamic por defecto"
export OMP_SCHEDULE="dynamic"
./pmtv-paralelo 5000
echo "Dynamic chunk 1"
export OMP_SCHEDULE="dynamic,1"
./pmtv-paralelo 5000
echo "Dynamic chunk 64"
export OMP_SCHEDULE="dynamic,64"
./pmtv-paralelo 5000
echo "Guided por defecto"
export OMP_SCHEDULE="guided"
./pmtv-paralelo 5000
echo "Guided chunk 1"
export OMP_SCHEDULE="guided,1"
./pmtv-paralelo 5000
echo "Guided chunk 64"
export OMP_SCHEDULE="guided,64"
./pmtv-paralelo 5000
