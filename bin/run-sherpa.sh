#!/bin/bash
set -x
export LD_LIBRARY_PATH=/usr/lib64/SHERPA-MC:$LD_LIBRARY_PATH
EN=$(cat Run.dat | grep BEAM_ENERGY_1  | tr -d ' '| sed 's@\;@*2@g' | cut -f2 -d=  | bc -qi | tail -n 1)
mkdir ../RES/sherpa_$EN -p
Sherpa EVENT_OUTPUT=HepMC_GenEvent[fifo.hepmc] RESULT_DIRECTORY=$(pwd)/../RES/sherpa_$EN/ SHERPA_LIB_PATH=$(pwd)/../RES/sherpa_$EN/Process/Amegic/lib
