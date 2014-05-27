export ROOTSYS=$(pwd)/top/usr
export PATH=$(pwd)/top/usr/bin:$ROOTSYS/bin:$PATH
#export ROOTSYS=$(pwd)
export PYTHONPATH=$PYTHONPATH:$(pwd)/top/usr/lib64/python2.6/site-packages/rivet
export LD_LIBRARY_PATH=$(pwd)/top/usr/lib64:$ROOTSYS/lib64/root:$(pwd)/top/usr/lib64/ThePEG:$(pwd)/top/usr/lib64/SHERPA-MC:$LD_LIBRARY_PATH