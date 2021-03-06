#!/bin/bash
set -x
export LD_LIBRARY_PATH=/usr/lib64/SHERPA-MC:$LD_LIBRARY_PATH
#mkdir -p ../generators/bin ../generators/obj

make -C .. bin/$(uname -m)/opalpythia8  

if [ -f /usr/share/pythia8-data/xmldoc/Index.xml ]; then
echo "Default Pythia"
else
export PYTHIA8DATA=../top/usr/share/pythia8-data/xmldoc/
fi

../bin/$(uname -m)/opalpythia8 fifo.hepmc.hepmc2g 
../bin/$(uname -m)/opalpythia8 temp.hepmc2g 
