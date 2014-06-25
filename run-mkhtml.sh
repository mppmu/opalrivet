#!/bin/bash
set -x

export RIVET_ANALYSIS_PATH=$(pwd)/lib::
export RIVET_REF_PATH=$(pwd)/ref::
export RIVET_INFO_PATH=$(pwd)/ref::
export RIVET_PLOT_PATH=$(pwd)/ref::



rivet-mkhtml Rivet$1.yoda  ref/$1.yoda -o out
sed -i 's@LineStyle=solid@PolyMarker=*@g' $(ls -1 out/$1/d14*.dat  out/$1/d13*.dat out/$1/d12*.dat out/$1/d11*.dat  out/$1/d10*.dat out/$1/d09*.dat out/$1/d08*.dat  out/$1/d07*.dat )

sed -i 's@LineStyle=solid@PolyMarker=*@g' $(ls -1 out/$1/d23*.dat  out/$1/d22*.dat out/$1/d21*.dat out/$1/d21*.dat  out/$1/d20*.dat out/$1/d19*.dat out/$1/d18*.dat  out/$1/d17*.dat  out/$1/d16*.dat )

sed -i 's@LineStyle=solid@PolyMarker=*@g' $(ls -1 out/$1/d43*.dat  out/$1/d42*.dat out/$1/d41*.dat out/$1/d41*.dat  out/$1/d40*.dat out/$1/d409*.dat out/$1/d408*.dat  out/$1/d407*.dat  out/$1/d406*.dat )

make-plots --pdfpng out/*.dat   out/$1/*.dat     


sed -i 's@LineStyle=solid@PolyMarker=*@g' $(ls -1 out/$1"_"Histo1D/d14*.dat  out/$1"_"Histo1D/d13*.dat out/$1"_"Histo1D/d12*.dat out/$1"_"Histo1D/d11*.dat  out/$1"_"Histo1D/d10*.dat out/$1"_"Histo1D/d09*.dat out/$1"_"Histo1D/d08*.dat  out/$1"_"Histo1D/d07*.dat )

sed -i 's@LineStyle=solid@PolyMarker=*@g' $(ls -1 out/$1"_"Histo1D/d23*.dat  out/$1"_"Histo1D/d22*.dat out/$1"_"Histo1D/d21*.dat out/$1"_"Histo1D/d21*.dat  out/$1"_"Histo1D/d20*.dat out/$1"_"Histo1D/d19*.dat out/$1"_"Histo1D/d18*.dat  out/$1"_"Histo1D/d17*.dat  out/$1"_"Histo1D/d16*.dat )

sed -i 's@LineStyle=solid@PolyMarker=*@g' $(ls -1 out/$1"_"Histo1D/d43*.dat  out/$1"_"Histo1D/d42*.dat out/$1"_"Histo1D/d41*.dat out/$1"_"Histo1D/d41*.dat  out/$1"_"Histo1D/d40*.dat out/$1"_"Histo1D/d409*.dat out/$1"_"Histo1D/d408*.dat  out/$1"_"Histo1D/d407*.dat  out/$1"_"Histo1D/d406*.dat )



sed -i 's@LineStyle=solid@PolyMarker=*@g' $(ls -1 out/$1"_"Scatter2D/d14*.dat  out/$1"_"Scatter2D/d13*.dat out/$1"_"Scatter2D/d12*.dat out/$1"_"Scatter2D/d11*.dat  out/$1"_"Scatter2D/d10*.dat out/$1"_"Scatter2D/d09*.dat out/$1"_"Scatter2D/d08*.dat  out/$1"_"Scatter2D/d07*.dat )

sed -i 's@LineStyle=solid@PolyMarker=*@g' $(ls -1 out/$1"_"Scatter2D/d23*.dat  out/$1"_"Scatter2D/d22*.dat out/$1"_"Scatter2D/d21*.dat out/$1"_"Scatter2D/d21*.dat  out/$1"_"Scatter2D/d20*.dat out/$1"_"Scatter2D/d19*.dat out/$1"_"Scatter2D/d18*.dat  out/$1"_"Scatter2D/d17*.dat  out/$1"_"Scatter2D/d16*.dat )

sed -i 's@LineStyle=solid@PolyMarker=*@g' $(ls -1 out/$1"_"Scatter2D/d43*.dat  out/$1"_"Scatter2D/d42*.dat out/$1"_"Scatter2D/d41*.dat out/$1"_"Scatter2D/d41*.dat  out/$1"_"Scatter2D/d40*.dat out/$1"_"Scatter2D/d409*.dat out/$1"_"Scatter2D/d408*.dat  out/$1"_"Scatter2D/d407*.dat  out/$1"_"Scatter2D/d406*.dat )




make-plots --pdfpng out/$1"_"Scatter2D/*.dat out/$1"_"Histo1D/*.dat
