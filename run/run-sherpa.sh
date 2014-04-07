#!/bin/bash
set -x
export LD_LIBRARY_PATH=/usr/lib64/SHERPA-MC:$LD_LIBRARY_PATH
export RIVET_ANALYSIS_PATH=$(pwd)/lib::
export RIVET_REF_PATH=$(pwd)/ref::
export RIVET_INFO_PATH=$(pwd)/ref::
export RIVET_PLOT_PATH=$(pwd)/ref::

Sherpa EVENT_OUTPUT=HepMC_GenEvent[fifo.hepmc] 