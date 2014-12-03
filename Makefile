NAME=JADE_OPAL_2000_S4300807a
TOPDIR=./Rivet-$(RIVET_VERS)	
ARCH          =   $(shell uname -m)
all: dirs	all_94.5 data_189


dirs:
	mkdir -p ./bin/$(ARCH)
	mkdir -p output
	mkdir -p obj

data_%:  bin/$(ARCH)/runProof 
#	make -C NEW
	make  'output/OPAL_'$*
#output/OPAL_%: ../bin/$(ARCH)/runProof
	bin/$(ARCH)/runProof  DCAP_OPAL_$*
#	mv 'NEW/Output/OPAL_'$*'.root' ./output

bin/$(ARCH)/runProof: src/runProof.cxx
		mkdir -p ../bin/$(ARCH)
		g++ $(shell  root-config --ldflags --libs) -lProof  Scripts/runProof.cxx  -o ./bin/$(ARCH)/runProof



	
all_%: 	
		mkdir -p run
		cp share/Runpythia8.dat run		
		sed -i 's@.*Beams:eCM.*@Beams:eCM = '$(shell echo  $*+$* | bc -qi | tail -n 1)'@g' run/Runpythia8.dat

		cp share/Runsherpa.dat run
		sed -i 's@.*BEAM_ENERGY_1.*@BEAM_ENERGY_1 = '$*';@g' run/Runsherpa.dat
		sed -i 's@.*BEAM_ENERGY_2.*@BEAM_ENERGY_2 = '$*';@g' run/Runsherpa.dat

		cp share/Runherwig++.dat run
		
		cp share/Runevtgen.dat run

		cp share/Makefile.run run/Makefile
		make bin/convert
		make -C run
		mv run/*root ./output

prof: pprroffessorr.cxx
		g++ $(shell root-config --cflags --glibs )  -lMinuit pprroffessorr.cxx -o ./prof


bin/$(ARCH)/draw: src/draw.cxx
		g++ $(shell root-config --cflags --glibs )  -lMinuit draw.cxx -o bin/$(ARCH)/draw



ALL:
	rm -rf run/out_*
	make all_65.0
	mv run/out run/out_65.0
	make all_68.0
	mv run/out run/out_68.0
	make all_80.5
	mv run/out run/out_80.5
	make all_86
	mv run/out run/out_86	
	make all_91.5
	mv run/out run/out_91.5	
	make all_94.5
	mv run/out run/out_94.5	
	make all_96.0
	mv run/out run/out_96.0
	make all_98.0
	mv run/out run/out_98.0
	make all_102.5
	mv run/out run/out_102.5
	make all_103.5
	mv run/out run/out_103.5



RIVET_VERS=2.2.0
DEVRPMS/Rivet-$(RIVET_VERS).tar.gz:
		wget http://www.hepforge.org/archive/rivet/Rivet-$(RIVET_VERS).tar.gz -O DEVRPMS/Rivet-$(RIVET_VERS).tar.gz


TAUOLA_VERS=1.1.4
#TAUOLA_VERS=1.1.5
DEVRPMS/TAUOLA-$(TAUOLA_VERS).tar.gz:
		wget http://tauolapp.web.cern.ch/tauolapp/resources/TAUOLA.$(TAUOLA_VERS)/TAUOLA.$(TAUOLA_VERS).tar.gz
		tar xvfz TAUOLA.$(TAUOLA_VERS).tar.gz
		mv TAUOLA TAUOLA-$(TAUOLA_VERS)
		tar cvf DEVRPMS/TAUOLA-$(TAUOLA_VERS).tar.gz TAUOLA-$(TAUOLA_VERS)
		rm -rf TAUOLA.$(TAUOLA_VERS).tar.gz

PHOTOS_VERS=3.54
#PHOTOS_VERS=3.56
DEVRPMS/PHOTOS-$(PHOTOS_VERS).tar.gz:
		wget http://photospp.web.cern.ch/photospp/resources/PHOTOS.$(PHOTOS_VERS)/PHOTOS.$(PHOTOS_VERS).tar.gz
		tar xvfz PHOTOS.$(PHOTOS_VERS).tar.gz
		mv PHOTOS PHOTOS-$(PHOTOS_VERS)
		tar cvf DEVRPMS/PHOTOS-$(PHOTOS_VERS).tar.gz PHOTOS-$(PHOTOS_VERS)
		rm -rf PHOTOS.$(PHOTOS_VERS).tar.gz

DEVRPMS/EvtGen-1.3.0.tar.gz:
		wget http://evtgen.warwick.ac.uk/static/srcrep/R01-03-00/EvtGen.R01-03-00.tar.gz
		tar xvfz EvtGen.R01-03-00.tar.gz
		rm -rf EvtGen-1.3.0
		mkdir -p EvtGen-1.3.0
		mv EvtGen/R01-03-00/* EvtGen-1.3.0
		tar cvf DEVRPMS/EvtGen-1.3.0.tar.gz EvtGen-1.3.0
		rm -rf EvtGen.R01-03-00.tar.gz EvtGen

DEVRPMS/HepMC-2.06.09.tar.gz: 
		wget http://lcgapp.cern.ch/project/simu/HepMC/download/HepMC-2.06.09.tar.gz -O DEVRPMS/HepMC-2.06.09.tar.gz

YODA_VERS=1.0.6
YODA_VERS=1.3.0
YODA_VERS=1.3.1
DEVRPMS/YODA-$(YODA_VERS).tar.gz: 
		rm -rf YODA-$(YODA_VERS)
#		svn export http://yoda.hepforge.org/svn/tags/yoda-1.0.0 YODA-$(YODA_VERS)
		hg clone http://yoda.hepforge.org/hg/yoda YODA-$(YODA_VERS)
		tar cf YODA-$(YODA_VERS).tar YODA-$(YODA_VERS)
		gzip YODA-$(YODA_VERS).tar
		mv YODA-$(YODA_VERS).tar.gz DEVRPMS/
		rm -rf YODA-$(YODA_VERS)
#		wget http://www.hepforge.org/archive/yoda/YODA-$(YODA_VERS).tar.gz -O DEVRPMS/YODA-$(YODA_VERS).tar.gz

FASTJET_VERS=3.0.2
DEVRPMS/fastjet-$(FASTJET_VERS).tar.gz: 
		wget http://www.fastjet.fr/repo/fastjet-$(FASTJET_VERS).tar.gz -O DEVRPMS/fastjet-$(FASTJET_VERS).tar.gz



DEVRPMS/pythia8180.tgz:
		wget http://home.thep.lu.se/~torbjorn/pythia8/pythia8180.tgz -O DEVRPMS/pythia8180.tgz


SHERPA_VERS=2.1.0
DEVRPMS/SHERPA-MC-$(SHERPA_VERS).tar.gz:
		wget http://www.hepforge.org/archive/sherpa/SHERPA-MC-$(SHERPA_VERS).tar.gz -O DEVRPMS/SHERPA-MC-$(SHERPA_VERS).tar.gz

DEVRPMS/ThePEG-1.9.0.tar.bz2:
		wget http://www.hepforge.org/archive/thepeg/ThePEG-1.9.0.tar.bz2 -O DEVRPMS/ThePEG-1.9.0.tar.bz2

DEVRPMS/Herwig++-2.7.0.tar.bz2:
	wget http://www.hepforge.org/archive/herwig/Herwig++-2.7.0.tar.bz2 -O DEVRPMS/Herwig++-2.7.0.tar.bz2

DEVRPMS/Cython-0.19.tar.gz:
	wget http://www.cython.org/release/Cython-0.19.tar.gz -O DEVRPMS/Cython-0.19.tar.gz


DEVRPMS/AGILe-1.4.1.tar.gz:
	wget http://www.hepforge.org/archive/agile/AGILe-1.4.1.tar.gz -O DEVRPMS/AGILe-1.4.1.tar.gz


getallsrc: DEVRPMS/fastjet-3.0.2.tar.gz DEVRPMS/Cython-0.19.tar.gz DEVRPMS/pythia8180.tgz DEVRPMS/TAUOLA-1.1.4.tar.gz DEVRPMS/PHOTOS-3.54.tar.gz DEVRPMS/EvtGen-1.3.0.tar.gz DEVRPMS/HepMC-2.06.09.tar.gz DEVRPMS/YODA-1.0.6.tar.gz DEVRPMS/SHERPA-MC-2.1.0.tar.gz DEVRPMS/ThePEG-1.9.0.tar.bz2 DEVRPMS/Herwig++-2.7.0.tar.bz2  DEVRPMS/Cython-0.19.tar.gz DEVRPMS/AGILe-1.4.1.tar.gz


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

binrpm_%: srcrpm srcrpm_$**
		rpmbuild --rebuild ~/rpmbuild/SRPMS/$**

allbinrpm: binrpm_YODA binrpm_AGILe binrpm_Cython binrpm_HepMC binrpm_PHOTOS binrpm_TAUOLA binrpm_Herwig++ binrpm_ThePEG  binrpm
	

beauty:
		astyle -n --keep-one-line-blocks --style=gnu    ./*cc
		
srcrpm: DEVRPMS/Rivet-$(RIVET_VERS).tar.gz 
	rm -rf DEVRPMS/Rivet-$(RIVET_VERS)
	rm -rf DEVRPMS/Rivet-$(RIVET_VERS)_orig	
	tar -zxf  DEVRPMS/Rivet-$(RIVET_VERS).tar.gz 
	cp -R	Rivet-$(RIVET_VERS) DEVRPMS/Rivet-$(RIVET_VERS)_orig
	mv 	Rivet-$(RIVET_VERS) DEVRPMS/
	rm -rf patch-Rivet-*.txt
	cp -R update/* DEVRPMS/Rivet-$(RIVET_VERS)/
	
	diff -Naur  -x   *RivetPaths.* -x *rivet.pxd* DEVRPMS/Rivet-$(RIVET_VERS)_orig  DEVRPMS/Rivet-$(RIVET_VERS) > DEVRPMS/patch-Rivet-0.txt  || exit 0
	diff -Naur                                    DEVRPMS/Rivet-$(RIVET_VERS)_orig/src/Tools/RivetPaths.cc  DEVRPMS/Rivet-$(RIVET_VERS)/src/Tools/RivetPaths.cc > DEVRPMS/patch-Rivet-1.txt || exit 0
	diff -Naur                                    DEVRPMS/Rivet-$(RIVET_VERS)_orig/src/Tools/RivetPaths.cc  DEVRPMS/Rivet-$(RIVET_VERS)/src/Tools/RivetPaths.cc >> DEVRPMS/patch-Rivet-1.txt || exit 0
	diff -Naur                                    DEVRPMS/Rivet-$(RIVET_VERS)_orig/include/Rivet/Tools/RivetPaths.hh  DEVRPMS/Rivet-$(RIVET_VERS)/include/Rivet/Tools/RivetPaths.hh >> DEVRPMS/patch-Rivet-1.txt || exit 0
	diff -Naur                                    DEVRPMS/Rivet-$(RIVET_VERS)_orig//pyext/rivet/rivet.pxd  DEVRPMS/Rivet-$(RIVET_VERS)/pyext/rivet/rivet.pxd >> DEVRPMS/patch-Rivet-1.txt || exit 0
	sed -i 's@DEVRPMS/Rivet-$(RIVET_VERS)_orig@.@g' DEVRPMS/patch-Rivet-*.txt
	sed -i 's@DEVRPMS/Rivet-$(RIVET_VERS)@.@g' DEVRPMS/patch-Rivet-*.txt

#diff -Naur EvtGen-1.3.0_orig EvtGen-1.3.0  | sed 's@EvtGen-1.3.0/@./@g' | sed 's@EvtGen-1.3.0_orig/@./@g'
#diff -Naur Herwig++-2.7.0_orig Herwig++-2.7.0  | sed 's@Herwig++-2.7.0/@./@g' | sed 's@Herwig++-2.7.0_orig/@./@g'
#diff -Naur  -x  *Makefile.in* acloc* YODA-1.0.6_orig YODA-1.0.6  | sed 's@YODA-1.0.6/@./@g' | sed 's@YODA-1.0.6_orig/@./@g'
#diff -Naur  -x  *Makefile.in* -x acloc* YODA-1.0.6_orig YODA-1.0.6  | sed 's@YODA-1.0.6/@./@g' | sed 's@YODA-1.0.6_orig/@./@g' >DEVRPMS/patch-YODA-0.txt
binrpm: srcrpm
		cp DEVRPMS/patch-Rivet-*.txt   /home/andriish/rpmbuild/SOURCES/
		cp DEVRPMS/Rivet-$(RIVET_VERS).tar.gz  /home/andriish/rpmbuild/SOURCES/
		rpmbuild -bs DEVRPMS/Rivet.spec
		rpmbuild --rebuild /home/andriish/rpmbuild/SRPMS/Rivet-$(RIVET_VERS)-1.src.rpm


YODA: DEVRPMS/YODA-$(YODA_VERS).tar.gz
	mkdir -p tmp
	rm -rf ./tmp/YODA-$(YODA_VERS) ./tmp/YODA-$(YODA_VERS)_orig
	tar xvfz DEVRPMS/YODA-$(YODA_VERS).tar.gz  -C ./tmp
	cp -R ./tmp/YODA-$(YODA_VERS) ./tmp/YODA-$(YODA_VERS)_orig
	cp -R DEVRPMS/YODA/*  ./tmp/YODA-$(YODA_VERS)/


YODApatch: YODA
	diff -Naur -x *svn* -x  *Makefile.in* -x acloc* ./tmp/YODA-$(YODA_VERS)_orig ./tmp/YODA-$(YODA_VERS)  | sed 's@./tmp/YODA-'$(YODA_VERS)'/@./@g' | sed 's@./tmp/YODA-'$(YODA_VERS)'_orig/@./@g' > DEVRPMS/patch-YODA-0.txt

srcrpm_YODA: YODA YODApatch
	sed -i 's@.*Version.*@Version: '$(YODA_VERS)'@g'  DEVRPMS/YODA.spec
	cp DEVRPMS/YODA-$(YODA_VERS).tar.gz $(HOME)/rpmbuild/SOURCES
	cp DEVRPMS/patch-YODA-0.txt $(HOME)/rpmbuild/SOURCES
	echo '%_topdir %(echo '$(HOME)'/rpmbuild)' > $(HOME)/.rpmmacros
	rpmbuild -bs DEVRPMS/YODA.spec
binrpm_YODA: srcrpm_YODA
	rpmbuild --rebuild $(HOME)/rpmbuild/SRPMS/YODA-$(YODA_VERS)*


Rivet: DEVRPMS/Rivet-$(RIVET_VERS).tar.gz
	mkdir -p tmp
	rm -rf ./tmp/Rivet-$(RIVET_VERS) ./tmp/Rivet-$(RIVET_VERS)_orig
	tar xvfz DEVRPMS/Rivet-$(RIVET_VERS).tar.gz  -C ./tmp
	cp -R ./tmp/Rivet-$(RIVET_VERS) ./tmp/Rivet-$(RIVET_VERS)_orig
	cp -R DEVRPMS/Rivet/*  ./tmp/Rivet-$(RIVET_VERS)/


Rivetpatch: Rivet
	diff -Naur -x *svn* -x  *Makefile.in* -x acloc* ./tmp/Rivet-$(RIVET_VERS)_orig ./tmp/Rivet-$(RIVET_VERS)  | sed 's@./tmp/Rivet-'$(RIVET_VERS)'/@./@g' | sed 's@./tmp/Rivet-'$(RIVET_VERS)'_orig/@./@g' > DEVRPMS/patch-Rivet-0.txt

srcrpm_Rivet: Rivet Rivetpatch
	sed -i 's@.*Version.*@Version: '$(RIVET_VERS)'@g'  DEVRPMS/Rivet.spec
	cp DEVRPMS/Rivet-$(RIVET_VERS).tar.gz $(HOME)/rpmbuild/SOURCES
	cp DEVRPMS/patch-Rivet-0.txt $(HOME)/rpmbuild/SOURCES
	echo '%_topdir %(echo '$(HOME)'/rpmbuild)' > $(HOME)/.rpmmacros
	rpmbuild -bs DEVRPMS/Rivet.spec
binrpm_Rivet: srcrpm_Rivet
	rpmbuild --rebuild $(HOME)/rpmbuild/SRPMS/Rivet-$(RIVET_VERS)*



convert: bin/cut_and_transform
		rm -rf newdata.yoda
# to have yoda files run
#	for a in $(find 2012-4-27antiktQ | grep rzhist  | grep -v '.svn' ); do h2root $a $(echo $a| sed 's@rzhist@root@g');   ./yodaconvert  root2yoda   $(echo $a| sed 's@rzhist@root@g') $(echo $a| sed 's@rzhist@yoda@g'); done

	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.root/h1860022 /REF/JADE_OPAL_2000_S4300807a/d1009-x01-y01    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.root/h1860023 /REF/JADE_OPAL_2000_S4300807a/d1009-x01-y02    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.root/h1860024 /REF/JADE_OPAL_2000_S4300807a/d1009-x01-y03    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.root/h1860025 /REF/JADE_OPAL_2000_S4300807a/d1009-x01-y04    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.root/h1860026 /REF/JADE_OPAL_2000_S4300807a/d1009-x01-y05    >> newdata.yoda


	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_207_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_207_manip.root/h9860022 /REF/JADE_OPAL_2000_S4300807a/d1014-x01-y01   >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_207_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_207_manip.root/h9860023 /REF/JADE_OPAL_2000_S4300807a/d1014-x01-y02    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_207_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_207_manip.root/h9860024 /REF/JADE_OPAL_2000_S4300807a/d1014-x01-y03    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_207_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_207_manip.root/h9860025 /REF/JADE_OPAL_2000_S4300807a/d1014-x01-y04    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_207_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_207_manip.root/h9860026 /REF/JADE_OPAL_2000_S4300807a/d1014-x01-y05    >> newdata.yoda


########

	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27inclKt/output_200_9196_manip.yoda  /TC/2012-4-27inclKt/output_200_9196_manip.root/h1860022 /REF/JADE_OPAL_2000_S4300807a/d2009-x01-y01    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27inclKt/output_200_9196_manip.yoda  /TC/2012-4-27inclKt/output_200_9196_manip.root/h1860023 /REF/JADE_OPAL_2000_S4300807a/d2009-x01-y02    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27inclKt/output_200_9196_manip.yoda  /TC/2012-4-27inclKt/output_200_9196_manip.root/h1860024 /REF/JADE_OPAL_2000_S4300807a/d2009-x01-y03    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27inclKt/output_200_9196_manip.yoda  /TC/2012-4-27inclKt/output_200_9196_manip.root/h1860025 /REF/JADE_OPAL_2000_S4300807a/d2009-x01-y04    >> newdata.yoda


	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27inclKt/output_200_207_manip.yoda  /TC/2012-4-27inclKt/output_200_207_manip.root/h9860022 /REF/JADE_OPAL_2000_S4300807a/d2014-x01-y01   >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27inclKt/output_200_207_manip.yoda  /TC/2012-4-27inclKt/output_200_207_manip.root/h9860023 /REF/JADE_OPAL_2000_S4300807a/d2014-x01-y02    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27inclKt/output_200_207_manip.yoda  /TC/2012-4-27inclKt/output_200_207_manip.root/h9860024 /REF/JADE_OPAL_2000_S4300807a/d2014-x01-y03    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27inclKt/output_200_207_manip.yoda  /TC/2012-4-27inclKt/output_200_207_manip.root/h9860025 /REF/JADE_OPAL_2000_S4300807a/d2014-x01-y04    >> newdata.yoda




########

	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27kt/output_200_9196_manip.yoda  /TC/2012-4-27kt/output_200_9196_manip.root/h1860022 /REF/JADE_OPAL_2000_S4300807a/d3009-x01-y01    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27kt/output_200_9196_manip.yoda  /TC/2012-4-27kt/output_200_9196_manip.root/h1860023 /REF/JADE_OPAL_2000_S4300807a/d3009-x01-y02    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27kt/output_200_9196_manip.yoda  /TC/2012-4-27kt/output_200_9196_manip.root/h1860024 /REF/JADE_OPAL_2000_S4300807a/d3009-x01-y03    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27kt/output_200_9196_manip.yoda  /TC/2012-4-27kt/output_200_9196_manip.root/h1860025 /REF/JADE_OPAL_2000_S4300807a/d3009-x01-y04    >> newdata.yoda


	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27kt/output_200_207_manip.yoda  /TC/2012-4-27kt/output_200_207_manip.root/h9860022 /REF/JADE_OPAL_2000_S4300807a/d3014-x01-y01   >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27kt/output_200_207_manip.yoda  /TC/2012-4-27kt/output_200_207_manip.root/h9860023 /REF/JADE_OPAL_2000_S4300807a/d3014-x01-y02    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27kt/output_200_207_manip.yoda  /TC/2012-4-27kt/output_200_207_manip.root/h9860024 /REF/JADE_OPAL_2000_S4300807a/d3014-x01-y03    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27kt/output_200_207_manip.yoda  /TC/2012-4-27kt/output_200_207_manip.root/h9860025 /REF/JADE_OPAL_2000_S4300807a/d3014-x01-y04    >> newdata.yoda



########

	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_9196_manip.root/h1860022 /REF/JADE_OPAL_2000_S4300807a/d4009-x01-y01    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_9196_manip.root/h1860023 /REF/JADE_OPAL_2000_S4300807a/d4009-x01-y02    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_9196_manip.root/h1860024 /REF/JADE_OPAL_2000_S4300807a/d4009-x01-y03    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_9196_manip.root/h1860025 /REF/JADE_OPAL_2000_S4300807a/d4009-x01-y04    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_9196_manip.root/h1860026 /REF/JADE_OPAL_2000_S4300807a/d4009-x01-y05    >> newdata.yoda



	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_207_manip.root/h9860022 /REF/JADE_OPAL_2000_S4300807a/d4014-x01-y01   >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_207_manip.root/h9860023 /REF/JADE_OPAL_2000_S4300807a/d4014-x01-y02    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_207_manip.root/h9860024 /REF/JADE_OPAL_2000_S4300807a/d4014-x01-y03    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_207_manip.root/h9860025 /REF/JADE_OPAL_2000_S4300807a/d4014-x01-y04    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_207_manip.root/h9860026 /REF/JADE_OPAL_2000_S4300807a/d4014-x01-y05    >> newdata.yoda




	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_9196_manip.root/h1860022 /REF/JADE_OPAL_2000_S4300807a/d4109-x01-y01    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_9196_manip.root/h1860023 /REF/JADE_OPAL_2000_S4300807a/d4109-x01-y02    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_9196_manip.root/h1860024 /REF/JADE_OPAL_2000_S4300807a/d4109-x01-y03    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_9196_manip.root/h1860025 /REF/JADE_OPAL_2000_S4300807a/d4109-x01-y04    >> newdata.yoda


	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_207_manip.root/h9860022 /REF/JADE_OPAL_2000_S4300807a/d4114-x01-y01   >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_207_manip.root/h9860023 /REF/JADE_OPAL_2000_S4300807a/d4114-x01-y02    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_207_manip.root/h9860024 /REF/JADE_OPAL_2000_S4300807a/d4114-x01-y03    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_207_manip.root/h9860025 /REF/JADE_OPAL_2000_S4300807a/d4114-x01-y04    >> newdata.yoda



	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_9196_manip.root/h1860022 /REF/JADE_OPAL_2000_S4300807a/d4209-x01-y01    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_9196_manip.root/h1860023 /REF/JADE_OPAL_2000_S4300807a/d4209-x01-y02    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_9196_manip.root/h1860024 /REF/JADE_OPAL_2000_S4300807a/d4209-x01-y03    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_9196_manip.root/h1860025 /REF/JADE_OPAL_2000_S4300807a/d4209-x01-y04    >> newdata.yoda


	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_207_manip.root/h9860022 /REF/JADE_OPAL_2000_S4300807a/d4214-x01-y01   >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_207_manip.root/h9860023 /REF/JADE_OPAL_2000_S4300807a/d4214-x01-y02   >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_207_manip.root/h9860024 /REF/JADE_OPAL_2000_S4300807a/d4214-x01-y03    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_207_manip.root/h9860025 /REF/JADE_OPAL_2000_S4300807a/d4214-x01-y04  >> newdata.yoda

	cat DEVRPMS/Rivet/data/refdata/JADE_OPAL_2000_S4300807a.yoda.in > DEVRPMS/Rivet/data/refdata/JADE_OPAL_2000_S4300807a.yoda
	cat newdata.yoda >> DEVRPMS/Rivet/data/refdata/JADE_OPAL_2000_S4300807a.yoda

./bin/$(ARCH)/yodaconvert: src/yodaconvert.cc
		g++ -std=c++0x src/yodaconvert.cc -DENABLE_ROOT  $(shell yoda-config --cppflags --libs)  $(shell root-config --cflags --libs --ldflags)  -o ./bin/$(ARCH)/yodaconvert


./bin/$(ARCH)/cut_and_transform: src/cut_and_transform.cc
#				g++ -std=c++0x cut_and_transform.cc  $(shell root-config --cflags --libs --ldflags) $(shell yoda-config  --libs --cppflags)  -o cut_and_transform
				g++ -std=c++0x src/cut_and_transform.cc  $(shell root-config  --cflags --libs --ldflags) $(shell yoda-config  --libs --cppflags)  -o ./bin/$(ARCH)/cut_and_transform

#				g++ -std=c++0x cut_and_transform.cc -L./YODA-1.0.6/z/lib -lYODA $(shell root-config --cflags --libs --ldflags) -I./YODA-1.0.6/include  -o cut_and_transform



obj/opalrivetpythia8.o: src/opalrivetpythia8.cc
	gcc -c src/opalrivetpythia8.cc -o obj/opalrivetpythia8.o -I./  -I../top/usr/include
	
	
	
./bin/$(ARCH)/opalrivetpythia8: obj/opalrivetpythia8.o
	gcc -lpythia8tohepmc  obj/opalrivetpythia8.o -o ./bin/$(ARCH)/opalrivetpythia8  -L../top/usr/lib64




./bin/$(ARCH)/opalrivetevtgen.o: src/opalrivetevtgen.cc
	gcc $(shell root-config --cflags) -c src/opalrivetevtgen.cc -o obj/opalrivetevtgen.o -I./  -I../top/usr/include
	
	
	
./bin/$(ARCH)/opalrivetevtgen: obj/opalrivetevtgen.o
	gcc  -lEvtGenExternal $(shell  root-config --libs)  obj/opalrivetevtgen.o -o ./bin/$(ARCH)/opalrivetevtgen  -L../top/usr/lib64




