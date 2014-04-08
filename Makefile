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
		wget http://www.hepforge.org/archive/rivet/Rivet-$(VERS).tar.gz
		mv Rivet-$(VERS).tar.gz DEVRPMS/


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
		

binrpm:
		cp DEVRPMS/patch-Rivet-*.txt   /home/andriish/rpmbuild/SOURCES/
		cp DEVRPMS/Rivet-$(VERS).tar.gz  /home/andriish/rpmbuild/SOURCES/
		rpmbuild -bs DEVRPMS/Rivet.spec
		rpmbuild --rebuild /home/andriish/rpmbuild/SRPMS/Rivet-$(VERS)-1.src.rpm
