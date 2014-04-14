NAME=JADE_OPAL_2000_S4300807a
VERS=2.1.1
TOPDIR=./Rivet-$(VERS)	
all: 	all_94.5
	
all_%: 	
		mkdir -p run
		cp Runpythia8.dat run		
		sed -i 's@.*Beams:eCM.*@Beams:eCM = '$(shell echo  $*+$* | bc -qi | tail -n 1)'@g' run/Runpythia8.dat

		cp Runsherpa.dat run
		sed -i 's@.*BEAM_ENERGY_1.*@BEAM_ENERGY_1 = '$*';@g' run/Runsherpa.dat
		sed -i 's@.*BEAM_ENERGY_2.*@BEAM_ENERGY_2 = '$*';@g' run/Runsherpa.dat

		cp Runherwig++.dat run

		cp Makefile.run run/Makefile
		make -C run

allold_%: 	
		mkdir -p runold
		cp Run.dat runold
		sed -i 's@.*BEAM_ENERGY_1.*@BEAM_ENERGY_1 = '$*';@g' runold/Run.dat
		sed -i 's@.*BEAM_ENERGY_2.*@BEAM_ENERGY_2 = '$*';@g' runold/Run.dat
		cp Makefile.runold runold/Makefile
		make -C runold



ALL:
	rm -rf run/out_*
	make all_17.5
	mv run/out run/out_17.5
	make all_22
	mv run/out run/out_22
	make all_45.5
	mv run/out run/out_45.5
	make all_66.5
	mv run/out run/out_66.5
	make all_80.5
	mv run/out run/out_80.5
	make all_86
	mv run/out run/out_86	
	make all_91.5
	mv run/out run/out_91.5	
	make all_94.5
	mv run/out run/out_94.5	




DEVRPMS/Rivet-$(VERS).tar.gz:
		wget http://www.hepforge.org/archive/rivet/Rivet-$(VERS).tar.gz -O DEVRPMS/Rivet-$(VERS).tar.gz


DEVRPMS/TAUOLA-1.1.4.tar.gz:
		wget http://tauolapp.web.cern.ch/tauolapp/resources/TAUOLA.1.1.4/TAUOLA.1.1.4.tar.gz
		tar xvfz TAUOLA.1.1.4.tar.gz
		mv TAUOLA TAUOLA-1.1.4
		tar cvf DEVRPMS/TAUOLA-1.1.4.tar.gz TAUOLA-1.1.4
		rm -rf TAUOLA.1.1.4.tar.gz

DEVRPMS/PHOTOS-3.54.tar.gz:
		wget http://photospp.web.cern.ch/photospp/resources/PHOTOS.3.54/PHOTOS.3.54.tar.gz
		tar xvfz PHOTOS.3.54.tar.gz
		mv PHOTOS PHOTOS-3.54
		tar cvf DEVRPMS/PHOTOS-3.54.tar.gz PHOTOS-3.54
		rm -rf PHOTOS.3.54.tar.gz

DEVRPMS/EvtGen-1.3.0.tar.gz:
		wget http://evtgen.warwick.ac.uk/static/srcrep/R01-03-00/EvtGen.R01-03-00.tar.gz
		tar xvfz EvtGen.R01-03-00.tar.gz
		mkdir -p EvtGen-1.3.0
		mv EvtGen/R01-03-00/* EvtGen-1.3.0
		tar cvf DEVRPMS/EvtGen-1.3.0.tar.gz EvtGen-1.3.0
		rm -rf EvtGen.R01-03-00.tar.gz EvtGen

DEVRPMS/HepMC-2.06.09.tar.gz: 
		wget http://lcgapp.cern.ch/project/simu/HepMC/download/HepMC-2.06.09.tar.gz -O DEVRPMS/HepMC-2.06.09.tar.gz

DEVRPMS/YODA-1.0.6.tar.gz: 
		wget http://www.hepforge.org/archive/yoda/YODA-1.0.6.tar.gz -O DEVRPMS/YODA-1.0.6.tar.gz

DEVRPMS/pythia8180.tgz:
		wget http://home.thep.lu.se/~torbjorn/pythia8/pythia8180.tgz -O DEVRPMS/pythia8180.tgz
 
DEVRPMS/SHERPA-MC-2.1.0.tar.gz:
		wget http://www.hepforge.org/archive/sherpa/SHERPA-MC-2.1.0.tar.gz -O DEVRPMS/SHERPA-MC-2.1.0.tar.gz

DEVRPMS/ThePEG-1.9.0.tar.bz2:
		wget http://www.hepforge.org/archive/thepeg/ThePEG-1.9.0.tar.bz2 -O DEVRPMS/ThePEG-1.9.0.tar.bz2

DEVRPMS/Herwig++-2.7.0.tar.bz2:
	wget http://www.hepforge.org/archive/herwig/Herwig++-2.7.0.tar.bz2 -O DEVRPMS/Herwig++-2.7.0.tar.bz2

DEVRPMS/Cython-0.19.tar.gz:
	wget http://www.cython.org/release/Cython-0.19.tar.gz -O DEVRPMS/Cython-0.19.tar.gz


DEVRPMS/AGILe-1.4.1.tar.gz:
	wget http://www.hepforge.org/archive/agile/AGILe-1.4.1.tar.gz -O DEVRPMS/AGILe-1.4.1.tar.gz


getallsrc: DEVRPMS/Cython-0.19.tar.gz DEVRPMS/pythia8180.tgz DEVRPMS/TAUOLA-1.1.4.tar.gz DEVRPMS/PHOTOS-3.54.tar.gz DEVRPMS/EvtGen-1.3.0.tar.gz DEVRPMS/HepMC-2.06.09.tar.gz DEVRPMS/YODA-1.0.6.tar.gz DEVRPMS/SHERPA-MC-2.1.0.tar.gz DEVRPMS/ThePEG-1.9.0.tar.bz2 DEVRPMS/Herwig++-2.7.0.tar.bz2  DEVRPMS/Cython-0.19.tar.gz DEVRPMS/AGILe-1.4.1.tar.gz


installallsrc: getallsrc   DEVRPMS/HepMC-examples-hwaend.patch DEVRPMS/HepMC-examples-makefile.patch DEVRPMS/HepMC-fix-typo-hierachy-hierarchy.patch DEVRPMS/HepMC-linking.patch DEVRPMS/patch-EvtGen-0.txt DEVRPMS/patch-PHOTOS-0.txt DEVRPMS/patch-TAUOLA-0.txt DEVRPMS/patch-ThePEG-0.txt DEVRPMS/pythia8-fix-soname.patch DEVRPMS/pythia8-hepmc-version.patch DEVRPMS/pythia8-xmldir.patch
		cp  DEVRPMS/*patch* ~/rpmbuild/SOURCES/
		cp DEVRPMS/*tar.gz ~/rpmbuild/SOURCES/
		cp DEVRPMS/*tar.bz2 ~/rpmbuild/SOURCES/
		cp DEVRPMS/*tgz ~/rpmbuild/SOURCES/		


getsrc_%:
	 S_URL=$(shell cat 'DEVRPMS/'$*'.spec' | grep Source0: | sed 's@Source0:@@g'    )
	 S_NAME=$(shell cat 'DEVRPMS/'$*'.spec' | grep Name: | cut -f 2 -d: | )
	 S_VERSION=$(shell cat 'DEVRPMS/'$*'.spec' | grep Version: | cut -f 2 -d:  )
	 S_DOWN= $(shell echo $(S_URL) | sed 's@%{version}@'$(S_VERSION)'@g' | sed 's@%{name}@'$(S_NAME)'@g' )
	 wget $(S_DOWN)
	 
	 
srcrpm_%: installallsrc
	rpmbuild -bs DEVRPMS/$*.spec

binrpm_%: 
		rpmbuild --rebuild ~/rpmbuild/SRPMS/$**



beauty:
		astyle -n --keep-one-line-blocks --style=gnu   src/*
		
srcrpm: DEVRPMS/Rivet-$(VERS).tar.gz 
	rm -rf DEVRPMS/Rivet-$(VERS)
	rm -rf DEVRPMS/Rivet-$(VERS)_orig	
	tar -zxf  DEVRPMS/Rivet-$(VERS).tar.gz 
	cp -R	Rivet-$(VERS) DEVRPMS/Rivet-$(VERS)_orig
	mv 	Rivet-$(VERS) DEVRPMS/
	rm -rf patch-Rivet-*.txt
	cp -R update/* DEVRPMS/Rivet-$(VERS)/
	
	diff -Naur  -x   *RivetPaths.* -x *rivet.pxd* DEVRPMS/Rivet-$(VERS)_orig  DEVRPMS/Rivet-$(VERS) > DEVRPMS/patch-Rivet-0.txt
	diff -Naur                                    DEVRPMS/Rivet-$(VERS)_orig/src/Tools/RivetPaths.cc  DEVRPMS/Rivet-$(VERS)/src/Tools/RivetPaths.cc > DEVRPMS/patch-Rivet-1.txt
	diff -Naur                                    DEVRPMS/Rivet-$(VERS)_orig/src/Tools/RivetPaths.cc  DEVRPMS/Rivet-$(VERS)/src/Tools/RivetPaths.cc >> DEVRPMS/patch-Rivet-1.txt
	diff -Naur                                    DEVRPMS/Rivet-$(VERS)_orig/include/Rivet/Tools/RivetPaths.hh  DEVRPMS/Rivet-$(VERS)/include/Rivet/Tools/RivetPaths.hh >> DEVRPMS/patch-Rivet-1.txt
	diff -Naur                                    DEVRPMS/Rivet-$(VERS)_orig//pyext/rivet/rivet.pxd  DEVRPMS/Rivet-$(VERS)/pyext/rivet/rivet.pxd >> DEVRPMS/patch-Rivet-1.txt
	sed -i 's@DEVRPMS/Rivet-$(VERS)_orig@.@g' DEVRPMS/patch-Rivet-*.txt
	sed -i 's@DEVRPMS/Rivet-$(VERS)@.@g' DEVRPMS/patch-Rivet-*.txt

#diff -Naur EvtGen-1.3.0_orig EvtGen-1.3.0  | sed 's@EvtGen-1.3.0/@./@g' | sed 's@EvtGen-1.3.0_orig/@./@g'
#diff -Naur Herwig++-2.7.0_orig Herwig++-2.7.0  | sed 's@Herwig++-2.7.0/@./@g' | sed 's@Herwig++-2.7.0_orig/@./@g'
#diff -Naur  -x  *Makefile.in* acloc* YODA-1.0.6_orig YODA-1.0.6  | sed 's@YODA-1.0.6/@./@g' | sed 's@YODA-1.0.6_orig/@./@g'
#diff -Naur  -x  *Makefile.in* -x acloc* YODA-1.0.6_orig YODA-1.0.6  | sed 's@YODA-1.0.6/@./@g' | sed 's@YODA-1.0.6_orig/@./@g' >DEVRPMS/patch-YODA-0.txt
binrpm:
		cp DEVRPMS/patch-Rivet-*.txt   /home/andriish/rpmbuild/SOURCES/
		cp DEVRPMS/Rivet-$(VERS).tar.gz  /home/andriish/rpmbuild/SOURCES/
		rpmbuild -bs DEVRPMS/Rivet.spec
		rpmbuild --rebuild /home/andriish/rpmbuild/SRPMS/Rivet-$(VERS)-1.src.rpm


YODA:
	cp -R DEVRPMS/YODA/*  ./YODA-1.0.6
	diff -Naur  -x  *Makefile.in* acloc* YODA-1.0.6_orig YODA-1.0.6  | sed 's@YODA-1.0.6/@./@g' | sed 's@YODA-1.0.6_orig/@./@g' > DEVRPMS/patch-YODA-0.txt
	
	
test:
		g++ ReaderROOTtest.cc -L./YODA-1.0.6/z/lib -lYODA $(shell root-config --cflags --libs --ldflags) -I./YODA-1.0.6/include  -o ReaderROOTtest
#	g++ -c ReaderROOTtest.cc -I./YODA-1.0.6/include $(shell root-config --cflags )   -o ReaderROOTtest.o
#	g++ -c YODA-1.0.6/./src/ReaderROOT.cc -I./YODA-1.0.6/include $(shell root-config --cflags ) -o ReaderROOT.o
#	g++ ReaderROOTtest.o ReaderROOT.o -L./YODA-1.0.6/./src/.libs/libYODA.so -lYODA $(shell root-config --ldflags --glibs ) -o ReaderROOTtest
