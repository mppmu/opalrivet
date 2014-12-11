#!/bin/bash
set -x
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib64/ThePEG
mv Run.dat Run.in
Herwig++ read Run.in 
rm -f Run.hepmc
ln -s fifo.hepmc.hepmc2g Run.hepmc
Herwig++ run Run.run   -N 50000 



# fifo.hepmc.hepmc2g 
