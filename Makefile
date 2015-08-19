#export X509_USER_PROXY=$(pwd)/k5-ca-proxy.pem
#GEN=sherpa
#GEN=herwig++
#GEN=pythia8

#GEN=evtgen
GEN?=pythia8
#GEN=pythia8_evtgen

NAME=JADE_OPAL_2000_S4300807a
ARCH          =   $(shell uname -m)
CXX?=g++ -fdiagnostics-color=never 
include Makefile.syst

all:	 		    output/$(GEN)_91.root \
					output/opal_9196.root \
					output/opal_9197.root \
					output/opal_9198.root \
					output/opal_9199.root \
					output/opal_9100.root \
					output/opal_130.root output/$(GEN)_130.root \
					output/opal_136.root output/$(GEN)_136.root \
					output/opal_161.root output/$(GEN)_161.root \
					output/opal_172.root output/$(GEN)_172.root \
					output/opal_183.root output/$(GEN)_183.root \
					output/opal_189.root output/$(GEN)_189.root \
					output/opal_192.root output/$(GEN)_192.root \
					output/opal_196.root output/$(GEN)_196.root \
					output/opal_202.root output/$(GEN)_202.root \
					output/opal_205.root output/$(GEN)_205.root \
					output/opal_207.root output/$(GEN)_207.root


allmc:
	 		    output/$(GEN)_91.root \
					output/$(GEN)_130.root \
					output/$(GEN)_136.root \
					output/$(GEN)_161.root \
					output/$(GEN)_172.root \
					output/$(GEN)_183.root \
					output/$(GEN)_189.root \
					output/$(GEN)_192.root \
					output/$(GEN)_196.root \
					output/$(GEN)_202.root \
					output/$(GEN)_205.root \
					output/$(GEN)_207.root
					
alldata:			\
					output/opal_9196.root \
					output/opal_9197.root \
					output/opal_9198.root \
					output/opal_9199.root \
					output/opal_9100.root \
					output/opal_130.root \
					output/opal_136.root \
					output/opal_161.root \
					output/opal_172.root \
					output/opal_183.root \
					output/opal_189.root \
					output/opal_192.root \
					output/opal_196.root \
					output/opal_202.root \
					output/opal_205.root \
					output/opal_207.root



include Makefile.software


localsystem: dirs src_Rivet


.PHONY: dirs




dirs:
	mkdir -p $(_TOPDIR)
	mkdir -p $(_TOPDIR)/{BUILD,RPMS,SOURCES,SPECS,SRPMS}
	mkdir -p ./bin/$(ARCH)
	mkdir -p ./obj/$(ARCH)
	mkdir -p ./lib/$(ARCH)
	mkdir -p output
	mkdir -p obj
	mkdir -p tmp
	mkdir -p gen
	mkdir -p run

gen/%LinkDef.h: dirs
	@rm -f gen/$*LinkDef.h
	@echo  "#ifdef __MAKECINT__"   >> gen/$*LinkDef.h
	@echo  "#pragma link C++ class "$*"+;"   >> gen/$*LinkDef.h
	@echo  "#endif"      >> gen/$*LinkDef.h

gen/%Dict.cxx: dirs src/%.h gen/%LinkDef.h
	echo "Generating dictionary $@..."
	rootcint -f $@ -c  src/$*.h gen/$*LinkDef.h



	
SOURCES=src/Helpers.cxx         src/Helpers.h \
		src/Cuts.cxx            src/Cuts.h \
		src/TSampleInfo.cxx     src/TSampleInfo.h \
		src/TFastJet.cxx        src/TFastJet.h  \
		src/TAdvancedGraph.cxx  src/TAdvancedGraph.h \
		src/TUserProofData.cxx 	src/TUserProofData.h
	



output/opal_%.root:   dirs $(SOURCES)    bin/$(ARCH)/runProof       src/opalrivetdata.C gen/DB.root
		bin/$(ARCH)/runProof  LOCAL_OPAL_$*

	
output/$(GEN)_%.root: dirs $(SOURCES)	 bin/$(ARCH)/opalrivet$(GEN) run/Run$(GEN).dat_%  run/Makefile DEVRPMS/Rivet/src/Analyses/JADE_OPAL_2000_S4300807a.cc
		make -C run GEN=$(GEN) ENERGY=$*
		mv run/*.root ./output

	
run/Runpythia8.dat_%: 	bin/$(ARCH)/opalrivet$(GEN)
		mkdir -p run		
		cp share/Runpythia8.dat run/Runpythia8.dat_$*		
		sed -i 's@.*Beams:eCM.*@Beams:eCM = '$(shell echo  $* | bc -qi | tail -n 1)'@g' run/Runpythia8.dat_$*

run/Runpythia8_nohad.dat_%: share/Runpythia8_nohad.dat
		cp share/Runpythia8_nohad.dat run/Runpythia8_nohad.dat		
		sed -i 's@.*Beams:eCM.*@Beams:eCM = '$(shell echo  $*+$* | bc -qi | tail -n 1)'@g' run/Runpythia8_nohad.dat_$*

run/Runpythia8_evtgen.dat_%: share/Runpythia8_evtgen.dat
		cp share/Runpythia8_evtgen.dat run/Runpythia8_evtgen.dat_$*		
		sed -i 's@.*Beams:eCM.*@Beams:eCM = '$(shell echo  $*+$* | bc -qi | tail -n 1)'@g' run/Runpythia8_evtgen.dat_$*


run/Runsherpa.dat_%: share/Runsherpa.dat
		cp share/Runsherpa.dat run/Runsherpa.dat_$*
		sed -i 's@.*BEAM_ENERGY_1.*@BEAM_ENERGY_1 = '$(shell echo  0.5*$* | bc -qi | tail -n 1)';@g' run/Runsherpa.dat_$*
		sed -i 's@.*BEAM_ENERGY_2.*@BEAM_ENERGY_2 = '$(shell echo  0.5*$* | bc -qi | tail -n 1)';@g' run/Runsherpa.dat_$*

run/Runherwig++.dat_%: share/Runherwig++.dat
		cp share/Runherwig++.dat run/Runherwig++.dat_$*
		sed -i 's@.*set LEPGenerator:EventHandler:LuminosityFunction:Energy.*@set LEPGenerator:EventHandler:LuminosityFunction:Energy '$(shell echo  $* | bc -qi | tail -n 1)'@g' run/Runherwig++.dat_$*
		
run/Runevtgen.dat_%: share/Runevtgen.dat		
		cp share/Runevtgen.dat run/Runevtgen.dat_$*
		
run/Makefile: share/Makefile.run		
		cp share/Makefile.run run/Makefile


beauty:
		astyle -n --keep-one-line-blocks --style=gnu    ./*/*.h   ./*/*.cxx ./*/*.C ./*/*.hh

bin/$(ARCH)/opalrivet$(GEN):
	rm -f bin/$(ARCH)/opalrivet$(GEN)
	touch bin/$(ARCH)/opalrivet$(GEN)


obj/$(ARCH)/opalrivetpythia8.o:  dirs src/opalrivetpythia8.cxx
	$(CXX) -fdiagnostics-color=never   -pipe  -c src/opalrivetpythia8.cxx -o obj/$(ARCH)/opalrivetpythia8.o 
	
	
	
	
bin/$(ARCH)/opalrivetpythia8:  dirs obj/$(ARCH)/opalrivetpythia8.o
	$(CXX) -fdiagnostics-color=never   -pipe   -lpythia8 -lpythia8tohepmc -lHepMC obj/$(ARCH)/opalrivetpythia8.o -o ./bin/$(ARCH)/opalrivetpythia8  -L/lib64

bin/$(ARCH)/opalrivetpythia8_nohad:  dirs obj/$(ARCH)/opalrivetpythia8.o
	$(CXX) -fdiagnostics-color=never   -pipe   -lpythia8 -lpythia8tohepmc -lHepMC obj/$(ARCH)/opalrivetpythia8.o -o ./bin/$(ARCH)/opalrivetpythia8_nohad  -L/lib64



obj/$(ARCH)/opalrivetpythia8_evtgen.o:  dirs src/opalrivetpythia8_evtgen.cxx
	$(CXX) -fdiagnostics-color=never   -pipe  -c src/opalrivetpythia8_evtgen.cxx -o obj/$(ARCH)/opalrivetpythia8_evtgen.o -L/lib64 
	

bin/$(ARCH)/opalrivetpythia8_evtgen:  dirs obj/$(ARCH)/opalrivetpythia8_evtgen.o
	$(CXX) -fdiagnostics-color=never   -pipe  -lpythia8 -lHepMC  -lEvtGenExternal  obj/$(ARCH)/opalrivetpythia8_evtgen.o -o ./bin/$(ARCH)/opalrivetpythia8_evtgen -L/lib64



obj/$(ARCH)/opalrivetevtgen.o:  dirs src/opalrivetevtgen.cxx
	$(CXX) -fdiagnostics-color=never   -pipe  $(shell root-config --cflags) -c src/opalrivetevtgen.cxx -o obj/$(ARCH)/opalrivetevtgen.o
		
bin/$(ARCH)/opalrivetevtgen:  dirs obj/$(ARCH)/opalrivetevtgen.o
	$(CXX) -fdiagnostics-color=never   -pipe   -lEvtGenExternal $(shell  root-config --libs)  obj/$(ARCH)/opalrivetevtgen.o -o ./bin/$(ARCH)/opalrivetevtgen   -L/lib64


bin/$(ARCH)/runProof: dirs src/runProof.cxx  src/Helpers.cxx src/Helpers.h gen/TSampleInfoDict.cxx src/TSampleInfo.cxx
		$(CXX) -fdiagnostics-color=never   -pipe  -I. -g -DSIMPLE_HELPERS_ONLY $(shell  root-config --ldflags --glibs --cflags  ) -L$(shell root-config --config | sed 's@\ @\n@g' | grep "\-\-libdir=" | cut -f 2 -d=) -lProof  src/runProof.cxx  src/Helpers.cxx  gen/TSampleInfoDict.cxx src/TSampleInfo.cxx -o ./bin/$(ARCH)/runProof


bin/$(ARCH)/makeDB: dirs src/makeDB.cxx gen/TSampleInfoDict.cxx $(SOURCES)
		$(CXX) -fdiagnostics-color=never   -pipe  -I. -g -DSIMPLE_HELPERS_ONLY $(shell  root-config --ldflags --glibs --cflags  ) -L$(shell root-config --config | sed 's@\ @\n@g' | grep "\-\-libdir=" | cut -f 2 -d=) -lProof  src/makeDB.cxx  src/Helpers.cxx gen/TSampleInfoDict.cxx src/TSampleInfo.cxx  -o ./bin/$(ARCH)/makeDB



gen/DB.root: dirs bin/$(ARCH)/makeDB $(SOURCES)
	bin/$(ARCH)/makeDB  gen/DB.root $(MNT)/scratch/andriish/opal/ntuple_root/qcd/
	




bin/$(ARCH)/plots: dirs src//plots.cxx src/Helpers.cxx src/Helpers.h gen/TAdvancedGraphDict.cxx src/TAdvancedGraph.cxx src/TAdvancedGraph.h
		$(CXX) -fdiagnostics-color=never   -pipe  -I. -Isrc -I../ -g  $(shell  root-config --ldflags --glibs --cflags  ) -L$(shell root-config --config | sed 's@\ @\n@g' | grep "\-\-libdir=" | cut -f 2 -d=) -lProof  src//plots.cxx src/Helpers.cxx  gen/TAdvancedGraphDict.cxx src/TAdvancedGraph.cxx -o ./bin/$(ARCH)/plots



bin/$(ARCH)/create_manip: dirs src//create_manip.cxx src/Helpers.cxx src/Helpers.h gen/TAdvancedGraphDict.cxx src/TAdvancedGraph.cxx src/TAdvancedGraph.h
		$(CXX) -fdiagnostics-color=never   -pipe  -I. -Isrc -I../ -g  $(shell  root-config --ldflags --glibs --cflags  ) -L$(shell root-config --config | sed 's@\ @\n@g' | grep "\-\-libdir=" | cut -f 2 -d=) -lProof  src//create_manip.cxx src/Helpers.cxx  gen/TAdvancedGraphDict.cxx src/TAdvancedGraph.cxx -o ./bin/$(ARCH)/create_manip



bin/$(ARCH)/create_old: dirs src//create_old.cxx src/Helpers.cxx src/Helpers.h gen/TAdvancedGraphDict.cxx src/TAdvancedGraph.cxx src/TAdvancedGraph.h
		$(CXX) -fdiagnostics-color=never   -pipe  -I. -fdiagnostics-color=never  -Isrc -I../ -g  $(shell  root-config --ldflags --glibs --cflags  ) -L$(shell root-config --config | sed 's@\ @\n@g' | grep "\-\-libdir=" | cut -f 2 -d=) -lProof  src//create_old.cxx src/Helpers.cxx  gen/TAdvancedGraphDict.cxx src/TAdvancedGraph.cxx -o ./bin/$(ARCH)/create_old




lib/$(ARCH)/libopalrivet.so:  dirs  src/Helpers.cxx src/Helpers.h gen/TAdvancedGraphDict.cxx src/TAdvancedGraph.cxx src/TAdvancedGraph.h
	$(CXX) -fdiagnostics-color=never   -g -shared -fPIC -pipe  -I. -Isrc -I../ -g  $(shell  root-config --ldflags --glibs --cflags  ) -L$(shell root-config --config | sed 's@\ @\n@g' | grep "\-\-libdir=" | cut -f 2 -d=) -lProof   src/Helpers.cxx  gen/TAdvancedGraphDict.cxx src/TAdvancedGraph.cxx -o lib/$(ARCH)/libopalrivet.so

.rootrc: lib/$(ARCH)/libopalrivet.so
	echo Unix.*.Root.DynamicPath:  .:./lib/$(ARCH):$(shell root-config --libdir) > .rootrc
	echo Rint.Logon: ./rootlogon.C >> .rootrc
	echo 'rootlogon(){ gROOT->ProcessLine(".L ./lib/'$(ARCH)'/libopalrivet.so");}' >./rootlogon.C

#output/plots_%.root: .rootrc dirs   bin/$(ARCH)/plots output/opal_%.root output/$(GEN)_%.root
	#we need so somewhere
#	bin/$(ARCH)/plots $* output/opal_$*.root output/$(GEN)_$*.root
	

output/plots_%.root: .rootrc dirs   bin/$(ARCH)/plots output/opal_%.root output/$(GEN)_%.root output/manip_%.root output/old_%.root
	#we need so somewhere
	bin/$(ARCH)/plots $* output/opal_$*.root output/$(GEN)_$*.root output/manip_$*.root output/old_$*.root



bin/$(ARCH)/hepplotconvert: dirs   src/hepplotconvert/WriterROOT.h src/hepplotconvert/ROOTConvert.cc src/hepplotconvert/ROOTConvert.h src/hepplotconvert/ReaderROOT.cc src/hepplotconvert/ReaderROOT.h src/hepplotconvert/hepplotconvert.cxx src/hepplotconvert/WriterROOT.cc
		$(CXX) -fdiagnostics-color=never   -pipe  -fdiagnostics-color=never  -I. -g -fdiagnostics-color=never  $(shell  yoda-config --ldflags --libs --cflags  )  $(shell  root-config --ldflags --glibs --cflags  ) -L$(shell root-config --config | sed 's@\ @\n@g' | grep "\-\-libdir=" | cut -f 2 -d=) -lProof  src/hepplotconvert/WriterROOT.h src/hepplotconvert/ROOTConvert.cc src/hepplotconvert/ROOTConvert.h src/hepplotconvert/ReaderROOT.cc src/hepplotconvert/ReaderROOT.h src/hepplotconvert/hepplotconvert.cxx src/hepplotconvert/WriterROOT.cc -o ./bin/$(ARCH)/hepplotconvert

	
output/JADE_OPAL_2000_S4300807.root: bin/$(ARCH)/hepplotconvert DEVRPMS/Rivet/data/refdata/JADE_OPAL_2000_S4300807a.yoda
	bin/$(ARCH)/hepplotconvert yoda2root DEVRPMS/Rivet/data/refdata/JADE_OPAL_2000_S4300807a.yoda output/JADE_OPAL_2000_S4300807.root


output/old_%.root: dirs bin/$(ARCH)/create_old output/JADE_OPAL_2000_S4300807.root
	#cp output/JADE_OPAL_2000_S4300807.root output/old_$*.root
	bin/$(ARCH)/create_old   output/old_$*.root nevermind output/JADE_OPAL_2000_S4300807.root

toroot:
		for a in $(shell find share/TC/2012-4-27antiktQ/R0.7 | grep rzhist  | grep -v '.svn' ); do \
		h2root $$a $(echo $$a| sed 's@rzhist@root@g');\
		done
		for a in $(shell find share/TC/2012-4-27inclKt | grep rzhist  | grep -v '.svn' ); do \
		h2root $$a $(echo $$a| sed 's@rzhist@root@g');\
		done
		for a in $(shell find share/TC/2012-4-27kt | grep rzhist  | grep -v '.svn' ); do \
		h2root $$a $(echo $$a| sed 's@rzhist@root@g');\
		done

		for a in $(shell find share/TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2 | grep rzhist  | grep -v '.svn' ); do \
		h2root $$a $(echo $$a| sed 's@rzhist@root@g');\
		done




output/manip_%.root: dirs bin/$(ARCH)/create_manip
#toroot
		bin/$(ARCH)/create_manip   tmp/manip_$*_antikt.root antikt share/TC/2012-4-27antiktQ/R0.7/output_200_$*_manip.root 
		bin/$(ARCH)/create_manip   tmp/manip_$*_kt.root         kt share/TC/2012-4-27kt/output_200_$*.root 
		bin/$(ARCH)/create_manip   tmp/manip_$*_inclkt.root inclkt share/TC/2012-4-27inclKt/output_200_$*.root 
		bin/$(ARCH)/create_manip   tmp/manip_$*_siscone.root siscone share/TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_$*_manip.root 
		hadd -f output/manip_$*.root tmp/manip_$*_antikt.root tmp/manip_$*_kt.root tmp/manip_$*_inclkt.root tmp/manip_$*_siscone.root


