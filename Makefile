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
		make convert
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
		rm -rf EvtGen-1.3.0
		mkdir -p EvtGen-1.3.0
		mv EvtGen/R01-03-00/* EvtGen-1.3.0
		tar cvf DEVRPMS/EvtGen-1.3.0.tar.gz EvtGen-1.3.0
		rm -rf EvtGen.R01-03-00.tar.gz EvtGen

DEVRPMS/HepMC-2.06.09.tar.gz: 
		wget http://lcgapp.cern.ch/project/simu/HepMC/download/HepMC-2.06.09.tar.gz -O DEVRPMS/HepMC-2.06.09.tar.gz

DEVRPMS/YODA-1.0.6.tar.gz: 
		wget http://www.hepforge.org/archive/yoda/YODA-1.0.6.tar.gz -O DEVRPMS/YODA-1.0.6.tar.gz

DEVRPMS/fastjet-3.0.2.tar.gz: 
		wget http://www.fastjet.fr/repo/fastjet-3.0.2.tar.gz -O DEVRPMS/fastjet-3.0.2.tar.gz



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
		
srcrpm: DEVRPMS/Rivet-$(VERS).tar.gz 
	rm -rf DEVRPMS/Rivet-$(VERS)
	rm -rf DEVRPMS/Rivet-$(VERS)_orig	
	tar -zxf  DEVRPMS/Rivet-$(VERS).tar.gz 
	cp -R	Rivet-$(VERS) DEVRPMS/Rivet-$(VERS)_orig
	mv 	Rivet-$(VERS) DEVRPMS/
	rm -rf patch-Rivet-*.txt
	cp -R update/* DEVRPMS/Rivet-$(VERS)/
	
	diff -Naur  -x   *RivetPaths.* -x *rivet.pxd* DEVRPMS/Rivet-$(VERS)_orig  DEVRPMS/Rivet-$(VERS) > DEVRPMS/patch-Rivet-0.txt  || exit 0
	diff -Naur                                    DEVRPMS/Rivet-$(VERS)_orig/src/Tools/RivetPaths.cc  DEVRPMS/Rivet-$(VERS)/src/Tools/RivetPaths.cc > DEVRPMS/patch-Rivet-1.txt || exit 0
	diff -Naur                                    DEVRPMS/Rivet-$(VERS)_orig/src/Tools/RivetPaths.cc  DEVRPMS/Rivet-$(VERS)/src/Tools/RivetPaths.cc >> DEVRPMS/patch-Rivet-1.txt || exit 0
	diff -Naur                                    DEVRPMS/Rivet-$(VERS)_orig/include/Rivet/Tools/RivetPaths.hh  DEVRPMS/Rivet-$(VERS)/include/Rivet/Tools/RivetPaths.hh >> DEVRPMS/patch-Rivet-1.txt || exit 0
	diff -Naur                                    DEVRPMS/Rivet-$(VERS)_orig//pyext/rivet/rivet.pxd  DEVRPMS/Rivet-$(VERS)/pyext/rivet/rivet.pxd >> DEVRPMS/patch-Rivet-1.txt || exit 0
	sed -i 's@DEVRPMS/Rivet-$(VERS)_orig@.@g' DEVRPMS/patch-Rivet-*.txt
	sed -i 's@DEVRPMS/Rivet-$(VERS)@.@g' DEVRPMS/patch-Rivet-*.txt

#diff -Naur EvtGen-1.3.0_orig EvtGen-1.3.0  | sed 's@EvtGen-1.3.0/@./@g' | sed 's@EvtGen-1.3.0_orig/@./@g'
#diff -Naur Herwig++-2.7.0_orig Herwig++-2.7.0  | sed 's@Herwig++-2.7.0/@./@g' | sed 's@Herwig++-2.7.0_orig/@./@g'
#diff -Naur  -x  *Makefile.in* acloc* YODA-1.0.6_orig YODA-1.0.6  | sed 's@YODA-1.0.6/@./@g' | sed 's@YODA-1.0.6_orig/@./@g'
#diff -Naur  -x  *Makefile.in* -x acloc* YODA-1.0.6_orig YODA-1.0.6  | sed 's@YODA-1.0.6/@./@g' | sed 's@YODA-1.0.6_orig/@./@g' >DEVRPMS/patch-YODA-0.txt
binrpm: srcrpm
		cp DEVRPMS/patch-Rivet-*.txt   /home/andriish/rpmbuild/SOURCES/
		cp DEVRPMS/Rivet-$(VERS).tar.gz  /home/andriish/rpmbuild/SOURCES/
		rpmbuild -bs DEVRPMS/Rivet.spec
		rpmbuild --rebuild /home/andriish/rpmbuild/SRPMS/Rivet-$(VERS)-1.src.rpm


YODA: DEVRPMS/YODA-1.0.6.tar.gz
	rm -rf ./YODA-1.0.6 ./YODA-1.0.6_orig
	tar xvfz DEVRPMS/YODA-1.0.6.tar.gz 
	cp -R ./YODA-1.0.6 ./YODA-1.0.6_orig
	rm -f ./YODA-1.0.6/bin/*2*
	rm -f ./YODA-1.0.6/pyext/yoda/script*
##	rm -f ./YODA-1.0.6/pyext/yoda/*root*
	cp -R DEVRPMS/YODA/bin/*  ./YODA-1.0.6/bin
	cp -R DEVRPMS/YODA/include/*  ./YODA-1.0.6/include
	cp -R DEVRPMS/YODA/pyext/*  ./YODA-1.0.6/pyext
	cp -R DEVRPMS/YODA/src/*  ./YODA-1.0.6/src

YODApatch: YODA
	diff -Naur -x *svn* -x  *Makefile.in* -x acloc* YODA-1.0.6_orig YODA-1.0.6  | sed 's@YODA-1.0.6/@./@g' | sed 's@YODA-1.0.6_orig/@./@g' > DEVRPMS/patch-YODA-0.txt

	

zz:
	autoreconf
	./configure  --prefix=$(pwd)/z --enable-root --disable-pyext
	make -j 4
	make install



convert: cut_and_transform
		rm -rf newdata.yoda
# to have yoda files run
#	for a in $(find 2012-4-27antiktQ | grep rzhist  | grep -v '.svn' ); do h2root $a $(echo $a| sed 's@rzhist@root@g');   ./yodaconvert  root2yoda   $(echo $a| sed 's@rzhist@root@g') $(echo $a| sed 's@rzhist@yoda@g'); done

	./cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.root/h1860022 /REF/JADE_OPAL_2000_S4300807a/d1009-x01-y01    >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.root/h1860023 /REF/JADE_OPAL_2000_S4300807a/d1009-x01-y02    >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.root/h1860024 /REF/JADE_OPAL_2000_S4300807a/d1009-x01-y03    >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.root/h1860025 /REF/JADE_OPAL_2000_S4300807a/d1009-x01-y04    >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.root/h1860026 /REF/JADE_OPAL_2000_S4300807a/d1009-x01-y05    >> newdata.yoda


	./cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_207_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_207_manip.root/h9860022 /REF/JADE_OPAL_2000_S4300807a/d1014-x01-y01   >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_207_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_207_manip.root/h9860023 /REF/JADE_OPAL_2000_S4300807a/d1014-x01-y02    >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_207_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_207_manip.root/h9860024 /REF/JADE_OPAL_2000_S4300807a/d1014-x01-y03    >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_207_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_207_manip.root/h9860025 /REF/JADE_OPAL_2000_S4300807a/d1014-x01-y04    >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_207_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_207_manip.root/h9860026 /REF/JADE_OPAL_2000_S4300807a/d1014-x01-y05    >> newdata.yoda


########

	./cut_and_transform yes  TC/2012-4-27inclKt/output_200_9196_manip.yoda  /TC/2012-4-27inclKt/output_200_9196_manip.root/h1860022 /REF/JADE_OPAL_2000_S4300807a/d2009-x01-y01    >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27inclKt/output_200_9196_manip.yoda  /TC/2012-4-27inclKt/output_200_9196_manip.root/h1860023 /REF/JADE_OPAL_2000_S4300807a/d2009-x01-y02    >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27inclKt/output_200_9196_manip.yoda  /TC/2012-4-27inclKt/output_200_9196_manip.root/h1860024 /REF/JADE_OPAL_2000_S4300807a/d2009-x01-y03    >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27inclKt/output_200_9196_manip.yoda  /TC/2012-4-27inclKt/output_200_9196_manip.root/h1860025 /REF/JADE_OPAL_2000_S4300807a/d2009-x01-y04    >> newdata.yoda


	./cut_and_transform yes  TC/2012-4-27inclKt/output_200_207_manip.yoda  /TC/2012-4-27inclKt/output_200_207_manip.root/h9860022 /REF/JADE_OPAL_2000_S4300807a/d2014-x01-y01   >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27inclKt/output_200_207_manip.yoda  /TC/2012-4-27inclKt/output_200_207_manip.root/h9860023 /REF/JADE_OPAL_2000_S4300807a/d2014-x01-y02    >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27inclKt/output_200_207_manip.yoda  /TC/2012-4-27inclKt/output_200_207_manip.root/h9860024 /REF/JADE_OPAL_2000_S4300807a/d2014-x01-y03    >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27inclKt/output_200_207_manip.yoda  /TC/2012-4-27inclKt/output_200_207_manip.root/h9860025 /REF/JADE_OPAL_2000_S4300807a/d2014-x01-y04    >> newdata.yoda




########

	./cut_and_transform yes  TC/2012-4-27kt/output_200_9196_manip.yoda  /TC/2012-4-27kt/output_200_9196_manip.root/h1860022 /REF/JADE_OPAL_2000_S4300807a/d3009-x01-y01    >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27kt/output_200_9196_manip.yoda  /TC/2012-4-27kt/output_200_9196_manip.root/h1860023 /REF/JADE_OPAL_2000_S4300807a/d3009-x01-y02    >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27kt/output_200_9196_manip.yoda  /TC/2012-4-27kt/output_200_9196_manip.root/h1860024 /REF/JADE_OPAL_2000_S4300807a/d3009-x01-y03    >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27kt/output_200_9196_manip.yoda  /TC/2012-4-27kt/output_200_9196_manip.root/h1860025 /REF/JADE_OPAL_2000_S4300807a/d3009-x01-y04    >> newdata.yoda


	./cut_and_transform yes  TC/2012-4-27kt/output_200_207_manip.yoda  /TC/2012-4-27kt/output_200_207_manip.root/h9860022 /REF/JADE_OPAL_2000_S4300807a/d3014-x01-y01   >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27kt/output_200_207_manip.yoda  /TC/2012-4-27kt/output_200_207_manip.root/h9860023 /REF/JADE_OPAL_2000_S4300807a/d3014-x01-y02    >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27kt/output_200_207_manip.yoda  /TC/2012-4-27kt/output_200_207_manip.root/h9860024 /REF/JADE_OPAL_2000_S4300807a/d3014-x01-y03    >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27kt/output_200_207_manip.yoda  /TC/2012-4-27kt/output_200_207_manip.root/h9860025 /REF/JADE_OPAL_2000_S4300807a/d3014-x01-y04    >> newdata.yoda



########

	./cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_9196_manip.root/h1860022 /REF/JADE_OPAL_2000_S4300807a/d4009-x01-y01    >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_9196_manip.root/h1860023 /REF/JADE_OPAL_2000_S4300807a/d4009-x01-y02    >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_9196_manip.root/h1860024 /REF/JADE_OPAL_2000_S4300807a/d4009-x01-y03    >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_9196_manip.root/h1860025 /REF/JADE_OPAL_2000_S4300807a/d4009-x01-y04    >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_9196_manip.root/h1860026 /REF/JADE_OPAL_2000_S4300807a/d4009-x01-y05    >> newdata.yoda



	./cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_207_manip.root/h9860022 /REF/JADE_OPAL_2000_S4300807a/d4014-x01-y01   >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_207_manip.root/h9860023 /REF/JADE_OPAL_2000_S4300807a/d4014-x01-y02    >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_207_manip.root/h9860024 /REF/JADE_OPAL_2000_S4300807a/d4014-x01-y03    >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_207_manip.root/h9860025 /REF/JADE_OPAL_2000_S4300807a/d4014-x01-y04    >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_207_manip.root/h9860026 /REF/JADE_OPAL_2000_S4300807a/d4014-x01-y05    >> newdata.yoda




	./cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_9196_manip.root/h1860022 /REF/JADE_OPAL_2000_S4300807a/d4109-x01-y01    >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_9196_manip.root/h1860023 /REF/JADE_OPAL_2000_S4300807a/d4109-x01-y02    >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_9196_manip.root/h1860024 /REF/JADE_OPAL_2000_S4300807a/d4109-x01-y03    >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_9196_manip.root/h1860025 /REF/JADE_OPAL_2000_S4300807a/d4109-x01-y04    >> newdata.yoda


	./cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_207_manip.root/h9860022 /REF/JADE_OPAL_2000_S4300807a/d4114-x01-y01   >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_207_manip.root/h9860023 /REF/JADE_OPAL_2000_S4300807a/d4114-x01-y02    >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_207_manip.root/h9860024 /REF/JADE_OPAL_2000_S4300807a/d4114-x01-y03    >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_207_manip.root/h9860025 /REF/JADE_OPAL_2000_S4300807a/d4114-x01-y04    >> newdata.yoda



	./cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_9196_manip.root/h1860022 /REF/JADE_OPAL_2000_S4300807a/d4209-x01-y01    >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_9196_manip.root/h1860023 /REF/JADE_OPAL_2000_S4300807a/d4209-x01-y02    >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_9196_manip.root/h1860024 /REF/JADE_OPAL_2000_S4300807a/d4209-x01-y03    >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_9196_manip.root/h1860025 /REF/JADE_OPAL_2000_S4300807a/d4209-x01-y04    >> newdata.yoda


	./cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_207_manip.root/h9860022 /REF/JADE_OPAL_2000_S4300807a/d4214-x01-y01   >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_207_manip.root/h9860023 /REF/JADE_OPAL_2000_S4300807a/d4214-x01-y02   >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_207_manip.root/h9860024 /REF/JADE_OPAL_2000_S4300807a/d4214-x01-y03    >> newdata.yoda
	./cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_207_manip.root/h9860025 /REF/JADE_OPAL_2000_S4300807a/d4214-x01-y04  >> newdata.yoda

	cat update/data/refdata/JADE_OPAL_2000_S4300807a.yoda.in > update/data/refdata/JADE_OPAL_2000_S4300807a.yoda
	cat newdata.yoda >> update/data/refdata/JADE_OPAL_2000_S4300807a.yoda

yodaconvert:
		g++ -std=c++0x yodaconvert.cc -L./YODA-1.0.6/z/lib -lYODA $(shell root-config --cflags --libs --ldflags) -I./YODA-1.0.6/include  -o yodaconvert


cut_and_transform: cut_and_transform.cc
#				g++ -std=c++0x cut_and_transform.cc  $(shell root-config --cflags --libs --ldflags) $(shell yoda-config  --libs --cppflags)  -o cut_and_transform
				g++ -std=c++0x cut_and_transform.cc  $(shell root-config  --cflags --libs --ldflags) $(shell yoda-config  --libs --cppflags)  -o cut_and_transform

#				g++ -std=c++0x cut_and_transform.cc -L./YODA-1.0.6/z/lib -lYODA $(shell root-config --cflags --libs --ldflags) -I./YODA-1.0.6/include  -o cut_and_transform





