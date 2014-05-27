mkdir -p RPMS
cd RPMS

rm -f *rpm.*
rm -f *.rpm
wget http://linuxsoft.cern.ch/epel/6/i386/cernlib-2006-35.el6.i686.rpm         
wget --no-check-certificate  http://linuxsoft.cern.ch/epel/6/i386/cernlib-devel-2006-35.el6.i686.rpm
wget --no-check-certificate  http://linuxsoft.cern.ch/epel/6/i386/cernlib-g77-2006-34.el6.i686.rpm
wget --no-check-certificate  http://linuxsoft.cern.ch/epel/6/i386/cernlib-g77-devel-2006-34.el6.i686.rpm
wget --no-check-certificate  http://linuxsoft.cern.ch/epel/6/i386/cernlib-g77-static-2006-34.el6.i686.rpm
wget --no-check-certificate  http://linuxsoft.cern.ch/epel/6/i386/cernlib-g77-utils-2006-34.el6.i686.rpm
wget --no-check-certificate  http://linuxsoft.cern.ch/epel/6/i386/cernlib-packlib-2006-34.el6.i686.rpm
wget --no-check-certificate  http://linuxsoft.cern.ch/epel/6/i386/cernlib-packlib-g77-2006-34.el6.i686.rpm
wget --no-check-certificate  http://linuxsoft.cern.ch/epel/6/i386/cernlib-packlib-gfortran-2006-35.el6.i686.rpm
wget --no-check-certificate  http://linuxsoft.cern.ch/epel/6/i386/cernlib-static-2006-35.el6.i686.rpm
wget --no-check-certificate  http://linuxsoft.cern.ch/epel/6/i386/cernlib-utils-2006-35.el6.i686.rpm



wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/AGILe-1.4.1-1.x86_64.rpm
#wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/AGILe-debuginfo-1.4.1-1.x86_64.rpm
wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/AGILe-devel-1.4.1-1.x86_64.rpm
wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/HepMC-2.06.09-3.el6.x86_64.rpm
#wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/HepMC-debuginfo-2.06.09-3.el6.x86_64.rpm
wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/HepMC-devel-2.06.09-3.el6.x86_64.rpm
wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/Herwig++-2.7.0-1.x86_64.rpm
#wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/Herwig++-debuginfo-2.7.0-1.x86_64.rpm
wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/Herwig++-devel-2.7.0-1.x86_64.rpm
wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/PHOTOS-3.54-1.x86_64.rpm
#wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/PHOTOS-debuginfo-3.54-1.x86_64.rpm
wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/PHOTOS-devel-3.54-1.x86_64.rpm
wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/pythia8-8.1.80-1.el6.x86_64.rpm
#wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/pythia8-debuginfo-8.1.80-1.el6.x86_64.rpm
wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/pythia8-devel-8.1.80-1.el6.x86_64.rpm
wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/pythia8-hepmcinterface-8.1.80-1.el6.x86_64.rpm
wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/pythia8-hepmcinterface-devel-8.1.80-1.el6.x86_64.rpm
wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/Rivet-2.1.1-1.x86_64.rpm
#wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/Rivet-debuginfo-2.1.1-1.x86_64.rpm
wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/Rivet-devel-2.1.1-1.x86_64.rpm
wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/TAUOLA-1.1.4-1.x86_64.rpm
#wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/TAUOLA-debuginfo-1.1.4-1.x86_64.rpm
wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/TAUOLA-devel-1.1.4-1.x86_64.rpm
wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/ThePEG-1.9.0-1.x86_64.rpm
#wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/ThePEG-debuginfo-1.9.0-1.x86_64.rpm
wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/ThePEG-devel-1.9.0-1.x86_64.rpm
wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/YODA-1.0.6-1.x86_64.rpm
#wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/YODA-debuginfo-1.0.6-1.x86_64.rpm
wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/YODA-devel-1.0.6-1.x86_64.rpm


wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/SHERPA-MC-2.1.0-1.x86_64.rpm
#wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/SHERPA-MC-debuginfo-2.1.0-1.x86_64.rpm
wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/SHERPA-MC-devel-2.1.0-1.x86_64.rpm






wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/fastjet-3.0.2-1.x86_64.rpm
#wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/fastjet-debuginfo-3.0.2-1.x86_64.rpm
wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/fastjet-devel-3.0.2-1.x86_64.rpm
wget --no-check-certificate  https://www.mpp.mpg.de/~andriish/rpms/x86_64/fastjet-static-devel-3.0.2-1.x86_64.rpm




#wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-core-5.34.18-1.el6.x86_64.rpm
#wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-5.34.18-1.el6.x86_64.rpm
#wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-cint-5.34.18-1.el6.x86_64.rpm
#wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-io-5.34.18-1.el6.x86_64.rpm
#wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-hist-5.34.18-1.el6.x86_64.rpm
#wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-graf-5.34.18-1.el6.x86_64.rpm
#wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-graf-5.34.18-1.el6.x86_64.rpm
#wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-mathcore-5.34.18-1.el6.x86_64.rpm
#wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-net-5.34.18-1.el6.x86_64.rpm




wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-5.34.18-1.el6.x86_64.rpm
wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-cint-5.34.18-1.el6.x86_64.rpm
wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-cintex-5.34.18-1.el6.x86_64.rpm
wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-core-5.34.18-1.el6.x86_64.rpm
wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-genvector-5.34.18-1.el6.x86_64.rpm
wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-geom-5.34.18-1.el6.x86_64.rpm
wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-graf-5.34.18-1.el6.x86_64.rpm
wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-graf-asimage-5.34.18-1.el6.x86_64.rpm
wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-graf-fitsio-5.34.18-1.el6.x86_64.rpm
wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-graf-gpad-5.34.18-1.el6.x86_64.rpm
wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-graf-postscript-5.34.18-1.el6.x86_64.rpm
wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-graf-x11-5.34.18-1.el6.x86_64.rpm
wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-graf3d-5.34.18-1.el6.x86_64.rpm
wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-gui-5.34.18-1.el6.x86_64.rpm
wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-hist-5.34.18-1.el6.x86_64.rpm
wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-html-5.34.18-1.el6.x86_64.rpm
wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-io-5.34.18-1.el6.x86_64.rpm
wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-mathcore-5.34.18-1.el6.x86_64.rpm
wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-matrix-5.34.18-1.el6.x86_64.rpm
wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-net-5.34.18-1.el6.x86_64.rpm
wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-physics-5.34.18-1.el6.x86_64.rpm
wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-quadp-5.34.18-1.el6.x86_64.rpm
wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-reflex-5.34.18-1.el6.x86_64.rpm
wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-smatrix-5.34.18-1.el6.x86_64.rpm
wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-tree-5.34.18-1.el6.x86_64.rpm

wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/root-python-5.34.18-1.el6.x86_64.rpm

wget --no-check-certificate  http://ftp.pbone.net/mirror/download.fedora.redhat.com/pub/fedora/epel/6/x86_64/libAfterImage-1.20-1.el6.x86_64.rpm

cd ..
rm -rf top
mkdir -p top
cd top
for a in $(ls -1 ../RPMS/*rpm); do
rpm2cpio $a | cpio -i --make-directories 
done

set -x
cd ..
. ./init-post-install.sh

cp $(which rivet-buildplugin) $(which rivet-buildplugin).old
cat $(which rivet-buildplugin).old  | sed  's@yoda="/usr@yoda="'$(pwd)/top/usr'@g' | sed  's@hepmc="/usr@hepmc="'$(pwd)/top/usr'@g' | sed  's@rivet="/usr@rivet="'$(pwd)/top/usr'@g' | sed  's@ifastjet="/usr@ifastjet="'$(pwd)/top/usr'@g' | sed  's@lfastjet="@lfastjet="-L'$(pwd)/top/usr'@g'  > $(which rivet-buildplugin)


cp $(which yoda-config)  $(which yoda-config).old
cat $(which yoda-config).old  |      sed  's@/usr/bin/env\ bash@/bin/bash@g' | sed  's@/usr@'$(pwd)/top/usr'@g' >  $(which yoda-config)



cp $(which root-config)  $(which root-config).old
cat $(which root-config).old  | sed  's@dir=/usr@dir='$(pwd)/top/usr'@g' >  $(which root-config)
