#!/bin/bash
set -x
Herwig++ read Run.dat .
Herwig++ run fifo.hepmc.hepmc2g  -N50 
# fifo.hepmc.hepmc2g 
