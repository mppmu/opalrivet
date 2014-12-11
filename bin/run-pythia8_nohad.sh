#!/bin/bash
set -x
export LD_LIBRARY_PATH=/usr/lib64/SHERPA-MC:$LD_LIBRARY_PATH
#mkdir -p ../generators/bin ../generators/obj

make -C .. bin/$(uname -m)/opalrivetpythia8_nohad

if [ -f /usr/share/pythia8-data/xmldoc/Index.xml ]; then
echo "Default Pythia"
else
export PYTHIA8DATA=../top/usr/share/pythia8-data/xmldoc/
fi

../bin/$(uname -m)/opalrivetpythia8_nohad fifo.hepmc.hepmc2g 
