#!/bin/bash
set -x
export RIVET_REF_PATH=$(pwd)/ref::
export RIVET_INFO_PATH=$(pwd)/ref::
export RIVET_PLOT_PATH=$(pwd)/ref::
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd):$(pwd)/lib
rivet --ignore-beams --analysis=$1 -H Rivet$1.yoda   --analysis-path=$(pwd)/lib::     fifo.hepmc.hepmc2g

