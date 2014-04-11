#!/bin/bash
set -x
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib64/ThePEG
Herwig++ read Run.dat .
Herwig++ run fifo.hepmc.hepmc2g  -N50 
# fifo.hepmc.hepmc2g 
