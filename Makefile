#export X509_USER_PROXY=$(pwd)/k5-ca-proxy.pem
#GEN=sherpa
#GEN=herwig++
#GEN=pythia8

#GEN=evtgen
GEN?=pythia8
#GEN=pythia8_evtgen

NAME=JADE_OPAL_2000_S4300807a
ARCH          =   $(shell uname -m)
CXX?=g++

include Makefile.syst
#all:	 output/opal_136.root output/$(GEN)_136.root \
#		 output/opal_192.root output/$(GEN)_192.root \
all2:	output/opal_207.root output/$(GEN)_207.root output/manip_207.root

#include Makefile.syst
include Makefile.software
include Makefile.convert


localsystem: dirs src_Rivet


.PHONY: dirs




dirs:
	mkdir -p $(_TOPDIR)/{BUILD,RPMS,SOURCES,SPECS,SRPMS}
	mkdir -p ./bin/$(ARCH)
	mkdir -p ./obj/$(ARCH)
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



#share/TC/2012-4-27antiktQ/R0.7/output_200_207_manip.root share/TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.root share/TC/2012-4-27kt/output_200_207_manip.root share/TC/2012-4-27kt/output_200_9196_manip.root:	
#	h2root share/TC/2012-4-27antiktQ/R0.7/output_200_207_manip.root share/TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.root share/TC/2012-4-27kt/output_200_207_manip.root share/TC/2012-4-27kt/output_200_9196_manip.root


share/TC/2012-4-27%.root: share/TC/2012-4-27%.rzhist
	h2root share/TC/2012-4-27$*.rzhist share/TC/2012-4-27$*.root

#output/manip_%.root:   dirs $(SOURCES)    bin/$(ARCH)/create_manip  share/TC/2012-4-27antiktQ/R0.7/output_200_207_manip.root share/TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.root share/TC/2012-4-27kt/output_200_207_manip.root share/TC/2012-4-27kt/output_200_9196_manip.root
#		bin/$(ARCH)/create_manip output/manip_$*.root \
#		share/TC/2012-4-27antiktQ/R0.7/output_200_207_manip.root\
#		share/TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.root\		
#		share/TC/2012-4-27kt/output_200_207_manip.root\
#		share/TC/2012-4-27kt/output_200_9196_manip.root		
#		#$(shell find share/TC/2012-4-27antiktQ/R0.7/*.root )


output/manip_9196.root:   dirs $(SOURCES)    bin/$(ARCH)/create_manip  share/TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.root  share/TC/2012-4-27kt/output_200_9196_manip.root
		bin/$(ARCH)/create_manip tmp/manip_9196_antikt.root antikt share/TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.root
		bin/$(ARCH)/create_manip tmp/manip_9196_kt.root kt share/TC/2012-4-27kt/output_200_9196_manip.root		
		hadd -f output/manip_9196.root tmp/manip_9196_kt.root tmp/manip_9196_antikt.root

output/manip_207.root:   dirs $(SOURCES)    bin/$(ARCH)/create_manip  share/TC/2012-4-27antiktQ/R0.7/output_200_207_manip.root  share/TC/2012-4-27kt/output_200_207_manip.root
		bin/$(ARCH)/create_manip tmp/manip_207_antikt.root antikt share/TC/2012-4-27antiktQ/R0.7/output_200_207_manip.root
		bin/$(ARCH)/create_manip tmp/manip_207_kt.root kt share/TC/2012-4-27kt/output_200_207_manip.root		
		hadd -f output/manip_207.root tmp/manip_207_kt.root tmp/manip_207_antikt.root
		

#output/old_189.root:
#d16-x01-y01

	
output/$(GEN)_%.root: dirs $(SOURCES)	 bin/$(ARCH)/opalrivet$(GEN) run/Run$(GEN).dat_%  run/Makefile DEVRPMS/Rivet/src/Analyses/JADE_OPAL_2000_S4300807a.cc
		make -C run GEN=$(GEN) ENERGY=$*
		mv run/*.root ./output

	
run/Runpythia8.dat_%: 	bin/$(ARCH)/opalrivet$(GEN)
		mkdir -p run		
		cp share/Runpythia8.dat run/Runpythia8.dat_$*		
		sed -i 's@.*Beams:eCM.*@Beams:eCM = '$(shell echo  $* | bc -qi | tail -n 1)'@g' run/Runpythia8.dat_$*

run/Runpythia8_nohad.dat_%: share/Runpythia8_nohad.dat
		cp share/Runpythia8_nohad.dat run/Runpythia8_nohad.dat_$*
		sed -i 's@.*Beams:eCM.*@Beams:eCM = '$(shell echo  $*+$* | bc -qi | tail -n 1)'@g' run/Runpythia8_nohad.dat_$*

run/Runpythia8_evtgen.dat_%: share/Runpythia8_evtgen.dat
		cp share/Runpythia8_evtgen.dat run/Runpythia8_evtgen.dat_$*		
		sed -i 's@.*Beams:eCM.*@Beams:eCM = '$(shell echo  $*+$* | bc -qi | tail -n 1)'@g' run/Runpythia8_evtgen.dat_$*


run/Runsherpa.dat_%: share/Runsherpa.dat
		cp share/Runsherpa.dat run/Runsherpa.dat_$*
		sed -i 's@.*BEAM_ENERGY_1.*@BEAM_ENERGY_1 = '$*';@g' run/Runsherpa.dat_$*
		sed -i 's@.*BEAM_ENERGY_2.*@BEAM_ENERGY_2 = '$*';@g' run/Runsherpa.dat_$*

run/Runherwig++.dat_%: share/Runherwig++.dat
		cp share/Runherwig++.dat run/Runherwig++.dat_$*
		sed -i 's@.*set LEPGenerator:EventHandler:LuminosityFunction:Energy.*@set LEPGenerator:EventHandler:LuminosityFunction:Energy '$(shell echo  $*+$* | bc -qi | tail -n 1)'@g' run/Runherwig++.dat_$*
		
run/Runevtgen.dat_%: share/Runevtgen.dat		
		cp share/Runevtgen.dat run
		
run/Makefile: share/Makefile.run		
		cp share/Makefile.run run/Makefile


beauty:
		astyle -n --keep-one-line-blocks --style=gnu    ./*/*.h   ./*/*.cxx ./*/*.C ./*/*.hh

bin/$(ARCH)/opalrivet$(GEN):
	rm bin/$(ARCH)/opalrivet$(GEN)
	touch bin/$(ARCH)/opalrivet$(GEN)


obj/$(ARCH)/opalrivetpythia8.o:  dirs src/opalrivetpythia8.cxx
	$(CXX) -pipe  -c src/opalrivetpythia8.cxx -o obj/$(ARCH)/opalrivetpythia8.o 
	
	
	
bin/$(ARCH)/opalrivetpythia8:  dirs obj/$(ARCH)/opalrivetpythia8.o
	$(CXX) -pipe  -lpythia8tohepmc  obj/$(ARCH)/opalrivetpythia8.o -o ./bin/$(ARCH)/opalrivetpythia8  

bin/$(ARCH)/opalrivetpythia8_nohad:  dirs obj/$(ARCH)/opalrivetpythia8.o
	$(CXX) -pipe  -lpythia8tohepmc  obj/$(ARCH)/opalrivetpythia8.o -o ./bin/$(ARCH)/opalrivetpythia8_nohad  



obj/$(ARCH)/opalrivetpythia8_evtgen.o:  dirs src/opalrivetpythia8_evtgen.cxx
	$(CXX) -pipe  -c src/opalrivetpythia8_evtgen.cxx -o obj/$(ARCH)/opalrivetpythia8_evtgen.o 
	

bin/$(ARCH)/opalrivetpythia8_evtgen:  dirs obj/$(ARCH)/opalrivetpythia8_evtgen.o
	$(CXX) -pipe  -lpythia8 -lHepMC  -lEvtGenExternal  obj/$(ARCH)/opalrivetpythia8_evtgen.o -o ./bin/$(ARCH)/opalrivetpythia8_evtgen



obj/$(ARCH)/opalrivetevtgen.o:  dirs src/opalrivetevtgen.cxx
	$(CXX) -pipe  $(shell root-config --cflags) -c src/opalrivetevtgen.cxx -o obj/$(ARCH)/opalrivetevtgen.o
		
bin/$(ARCH)/opalrivetevtgen:  dirs obj/$(ARCH)/opalrivetevtgen.o
	$(CXX) -pipe   -lEvtGenExternal $(shell  root-config --libs)  obj/$(ARCH)/opalrivetevtgen.o -o ./bin/$(ARCH)/opalrivetevtgen  


bin/$(ARCH)/runProof: dirs src/runProof.cxx  src/Helpers.cxx src/Helpers.h gen/TSampleInfoDict.cxx src/TSampleInfo.cxx
		$(CXX) -pipe  -I. -g -DSIMPLE_HELPERS_ONLY $(shell  root-config --ldflags --glibs --cflags  ) -L$(shell root-config --config | sed 's@\ @\n@g' | grep "\-\-libdir=" | cut -f 2 -d=) -lProof  src/runProof.cxx  src/Helpers.cxx  gen/TSampleInfoDict.cxx src/TSampleInfo.cxx -o ./bin/$(ARCH)/runProof


bin/$(ARCH)/makeDB: dirs src/makeDB.cxx gen/TSampleInfoDict.cxx $(SOURCES)
		$(CXX) -pipe  -I. -g -DSIMPLE_HELPERS_ONLY $(shell  root-config --ldflags --glibs --cflags  ) -L$(shell root-config --config | sed 's@\ @\n@g' | grep "\-\-libdir=" | cut -f 2 -d=) -lProof  src/makeDB.cxx  src/Helpers.cxx gen/TSampleInfoDict.cxx src/TSampleInfo.cxx  -o ./bin/$(ARCH)/makeDB



bin/$(ARCH)/create_manip: dirs src/convert/create_manip.cxx gen/TSampleInfoDict.cxx $(SOURCES) gen/TAdvancedGraphDict.cxx src/TAdvancedGraph.cxx
		$(CXX) -pipe  -I. -I./src -g -DSIMPLE_HELPERS_ONLY $(shell  root-config --ldflags --glibs --cflags  ) -L$(shell root-config --config | sed 's@\ @\n@g' | grep "\-\-libdir=" | cut -f 2 -d=) -lProof  src/convert/create_manip.cxx  src/Helpers.cxx gen/TSampleInfoDict.cxx src/TSampleInfo.cxx gen/TAdvancedGraphDict.cxx src/TAdvancedGraph.cxx -o ./bin/$(ARCH)/create_manip



bin/$(ARCH)/create_old: dirs src/convert/create_old.cxx gen/TSampleInfoDict.cxx $(SOURCES) gen/TAdvancedGraphDict.cxx src/TAdvancedGraph.cxx src/convert/WriterROOT.cc src/convert/ReaderROOT.cc src/convert/ROOTConvert.cc
		$(CXX) -pipe  -I. -I./src -g -DSIMPLE_HELPERS_ONLY $(shell  yoda-config  --libs --cflags  ) $(shell  root-config --ldflags --glibs --cflags  ) -L$(shell root-config --config | sed 's@\ @\n@g' | grep "\-\-libdir=" | cut -f 2 -d=) -lProof  src/convert/create_old.cxx src/convert/WriterROOT.cc src/convert/ReaderROOT.cc src/convert/ROOTConvert.cc src/Helpers.cxx gen/TSampleInfoDict.cxx src/TSampleInfo.cxx gen/TAdvancedGraphDict.cxx src/TAdvancedGraph.cxx -o ./bin/$(ARCH)/create_old



gen/DB.root: bin/$(ARCH)/makeDB $(SOURCES)
	bin/$(ARCH)/makeDB  gen/DB.root $(MNT)/scratch/andriish/opal/ntuple_root/qcd/
	



bin/$(ARCH)/hepplotconvert: src/convert/hepplotconvert.cxx  src/convert/WriterROOT.cc src/convert/ReaderROOT.cc src/convert/ROOTConvert.cc
	g++ -std=gnu++0x $(shell root-config --cflags --libs)  $(shell yoda-config  --libs) -I. -I./src/convert -I./inc src/convert/ROOTConvert.cc src/convert/WriterROOT.cc src/convert/ReaderROOT.cc src/convert/hepplotconvert.cxx    -o bin/$(ARCH)/hepplotconvert




bin/$(ARCH)/cut_and_transform: src/convert/cut_and_transform.cxx  src/convert/WriterROOT.cc src/convert/ReaderROOT.cc src/convert/ROOTConvert.cc
	g++ -std=gnu++0x $(shell root-config --cflags --libs)  $(shell yoda-config  --libs) -I. -I./src/convert -I./inc src/convert/ROOTConvert.cc src/convert/WriterROOT.cc src/convert/ReaderROOT.cc src/convert/cut_and_transform.cxx    -o bin/$(ARCH)/cut_and_transform

