#!/bin/bash
set -x
#export LD_LIBRARY_PATH=/usr/lib64/SHERPA-MC:$LD_LIBRARY_PATH
#mkdir -p ../generators/bin ../generators/obj
make -C .. bin/$(uname -m)/opalrivetevtgen

if [ -f /usr/share/pythia8-data/xmldoc/Index.xml ]; then
echo "Default Pythia"
export EVTGENDIR="/usr/"
else
export PYTHIA8DATA=../top/usr/share/pythia8-data/xmldoc/
export EVTGENDIR="../"
fi
export EVTGENDIR_Z="../"
echo OK
../bin/$(uname -m)/opalrivetevtgen file  $(cat Run.dat)  $EVTGENDIR_Z/share/GENERIC.DEC fifo.hepmc.hepmc2g
