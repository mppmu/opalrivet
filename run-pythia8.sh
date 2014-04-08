#!/bin/bash
set -x
export LD_LIBRARY_PATH=/usr/lib64/SHERPA-MC:$LD_LIBRARY_PATH
make bin/opalrivetpythia8  -C ../generators
../generators/bin/opalrivetpythia8 fifo.hepmc.hepmc2g
