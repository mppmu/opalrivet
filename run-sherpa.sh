#!/bin/bash
set -x
export LD_LIBRARY_PATH=/usr/lib64/SHERPA-MC:$LD_LIBRARY_PATH
Sherpa EVENT_OUTPUT=HepMC_GenEvent[fifo.hepmc] 
