#!/bin/bash
set -x
export LD_LIBRARY_PATH=/usr/lib64/SHERPA-MC:$LD_LIBRARY_PATH
#mkdir -p ../generators/bin ../generators/obj

make -C .. bin/$(uname -m)/opalpythia8_evtgen 

if [ -f /usr/share/pythia8-data/xmldoc/Index.xml ]; then
echo "Default Pythia"
else
export PYTHIA8DATA=../top/usr/share/pythia8-data/xmldoc/
fi

export PYTHIA8DATA=/usr/share/pythia8-data/xmldoc/
export EVTGENDIR="/usr/"
../bin/$(uname -m)/opalpythia8_evtgen fifo.hepmc.hepmc2g 
