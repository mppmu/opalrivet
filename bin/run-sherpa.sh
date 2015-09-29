#!/bin/bash
set -x
export LD_LIBRARY_PATH=/usr/lib64/SHERPA-MC:$LD_LIBRARY_PATH
EN=$(cat Run.dat | grep BEAM_ENERGY_1  | tr -d ' '| sed 's@\;@*2@g' | cut -f2 -d=  | bc -qi | tail -n 1)
mkdir ../output/generators/sherpa_$EN -p
rm -rf Results
rm -rf Process
rm -rf Results.db
cp -r ../output/generators/sherpa_$EN/* ./
Sherpa EVENT_OUTPUT=HepMC_GenEvent[fifo.hepmc]
cp -r Process    ../output/generators/sherpa_$EN/
cp -r Results    ../output/generators/sherpa_$EN/
cp -r Results.db ../output/generators/sherpa_$EN/
