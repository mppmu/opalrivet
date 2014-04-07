#!/bin/bash
set -x
export LD_LIBRARY_PATH=/usr/lib64/SHERPA-MC:$LD_LIBRARY_PATH
export RIVET_ANALYSIS_PATH=$(pwd)/lib::
export RIVET_REF_PATH=$(pwd)/ref::
export RIVET_INFO_PATH=$(pwd)/ref::
export RIVET_PLOT_PATH=$(pwd)/ref::

rivet-mkhtml Rivet.yoda  ref/$1.yoda -o out
sed -i 's@LineStyle=solid@PolyMarker=*@g' $(ls -1 out/$1/d14*.dat  out/$1/d13*.dat out/$1/d12*.dat out/$1/d11*.dat  out/$1/d10*.dat out/$1/d09*.dat out/$1/d08*.dat  out/$1/d07*.dat )

sed -i 's@LineStyle=solid@PolyMarker=*@g' $(ls -1 out/$1/d23*.dat  out/$1/d22*.dat out/$1/d21*.dat out/$1/d21*.dat  out/$1/d20*.dat out/$1/d19*.dat out/$1/d18*.dat  out/$1/d17*.dat  out/$1/d16*.dat )


make-plots --pdfpng out/*.dat   out/$1/*.dat
#mv out/*dat out/Rivet$(NAME)
#mv out/*png out/Rivet$(NAME)
#mv out/*pdf out/Rivet$(NAME)
