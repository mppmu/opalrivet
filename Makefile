#export X509_USER_PROXY=$(pwd)/k5-ca-proxy.pem
#GEN=sherpa
#GEN=herwi$(CXX)
#GEN=pythia8

#GEN=evtgen
GEN?=pythia8
#GEN=pythia8_evtgen

NAME=JADE_OPAL_2000_S4300807a
ARCH          =   $(shell uname -m)
CXX?=g++


all: output/opal_136.root output/pythia8_136.root

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

.PHONY: gen/TSampleInfoLinkDef.h
gen/TSampleInfoLinkDef.h:
	@rm -f gen/TSampleInfoLinkDef.h
	@echo  "#ifdef __MAKECINT__"   >> gen/TSampleInfoLinkDef.h
	@echo  "#pragma link C++ class "TSampleInfo"+;"   >> gen/TSampleInfoLinkDef.h
	@echo  "#endif"      >> gen/TSampleInfoLinkDef.h



gen/TSampleInfoDict.cxx: src/TSampleInfo.h gen/TSampleInfoLinkDef.h
	echo "Generating dictionary $@..."
	rootcint -f $@ -c  $^


	
SOURCES=src/Helpers.cxx src/Helpers.h \
	src/Cuts.cxx src/Cuts.h \
	src/TSampleInfo.cxx src/TSampleInfo.h \
	src/TFastJet.cxx  src/TFastJet.h  \
	src/TAdvancedGraph.cxx src/TAdvancedGraph.h \
	src/TUserProofData.cxx src/TUserProofDataDict.cxx
	

	
output/opal_%.root:   dirs $(SOURCES)    bin/$(ARCH)/runProof       src/opalrivetdata.C gen/DB.root
		bin/$(ARCH)/runProof  LOCAL_OPAL_$*

	
output/$(GEN)_%.root: dirs $(SOURCES)	 bin/$(ARCH)/opalrivet$(GEN) run/Run$(GEN).dat  run/Makefile DEVRPMS/Rivet/src/Analyses/JADE_OPAL_2000_S4300807a.cc
		make -C run GEN=$(GEN)
		mv run/*.root ./output

	
run/Runpythia8.dat: 	bin/$(ARCH)/opalrivet$(GEN)
		mkdir -p run		
		cp share/Runpythia8.dat run		
		sed -i 's@.*Beams:eCM.*@Beams:eCM = '$(shell echo  $* | bc -qi | tail -n 1)'@g' run/Runpythia8.dat

run/Runpythia8_nohad.dat: share/Runpythia8_nohad.dat
		cp share/Runpythia8_nohad.dat run		
		sed -i 's@.*Beams:eCM.*@Beams:eCM = '$(shell echo  $*+$* | bc -qi | tail -n 1)'@g' run/Runpythia8_nohad.dat

run/Runpythia8_evtgen.dat: share/Runpythia8_evtgen.dat
		cp share/Runpythia8_evtgen.dat run		
		sed -i 's@.*Beams:eCM.*@Beams:eCM = '$(shell echo  $*+$* | bc -qi | tail -n 1)'@g' run/Runpythia8_evtgen.dat


run/Runsherpa.dat: share/Runsherpa.dat
		cp share/Runsherpa.dat run
		sed -i 's@.*BEAM_ENERGY_1.*@BEAM_ENERGY_1 = '$*';@g' run/Runsherpa.dat
		sed -i 's@.*BEAM_ENERGY_2.*@BEAM_ENERGY_2 = '$*';@g' run/Runsherpa.dat

run/Runherwig++.dat: share/Runherwig++.dat
		cp share/Runherwig++.dat run
		sed -i 's@.*set LEPGenerator:EventHandler:LuminosityFunction:Energy.*@set LEPGenerator:EventHandler:LuminosityFunction:Energy '$(shell echo  $*+$* | bc -qi | tail -n 1)'@g' run/Runherwig++.dat
		
run/Runevtgen.dat: share/Runevtgen.dat		
		cp share/Runevtgen.dat run
		
run/Makefile: share/Makefile.run		
		cp share/Makefile.run run/Makefile


beauty:
		astyle -n --keep-one-line-blocks --style=gnu    ./*/*.h   ./*/*.cxx ./*/*.C ./*/*.hh

bin/$(ARCH)/opalrivet$(GEN):
	rm bin/$(ARCH)/opalrivet$(GEN)
	touch bin/$(ARCH)/opalrivet$(GEN)


obj/$(ARCH)/opalrivetpythia8.o:  dirs src/opalrivetpythia8.cxx
	$(CXX) -c src/opalrivetpythia8.cxx -o obj/$(ARCH)/opalrivetpythia8.o 
	
	
	
bin/$(ARCH)/opalrivetpythia8:  dirs obj/$(ARCH)/opalrivetpythia8.o
	$(CXX) -lpythia8tohepmc  obj/$(ARCH)/opalrivetpythia8.o -o ./bin/$(ARCH)/opalrivetpythia8  

bin/$(ARCH)/opalrivetpythia8_nohad:  dirs obj/$(ARCH)/opalrivetpythia8.o
	$(CXX) -lpythia8tohepmc  obj/$(ARCH)/opalrivetpythia8.o -o ./bin/$(ARCH)/opalrivetpythia8_nohad  



obj/$(ARCH)/opalrivetpythia8_evtgen.o:  dirs src/opalrivetpythia8_evtgen.cxx
	$(CXX) -c src/opalrivetpythia8_evtgen.cxx -o obj/$(ARCH)/opalrivetpythia8_evtgen.o 
	

bin/$(ARCH)/opalrivetpythia8_evtgen:  dirs obj/$(ARCH)/opalrivetpythia8_evtgen.o
	$(CXX) -lpythia8 -lHepMC  -lEvtGenExternal  obj/$(ARCH)/opalrivetpythia8_evtgen.o -o ./bin/$(ARCH)/opalrivetpythia8_evtgen



obj/$(ARCH)/opalrivetevtgen.o:  dirs src/opalrivetevtgen.cxx
	$(CXX) $(shell root-config --cflags) -c src/opalrivetevtgen.cxx -o obj/$(ARCH)/opalrivetevtgen.o
		
bin/$(ARCH)/opalrivetevtgen:  dirs obj/$(ARCH)/opalrivetevtgen.o
	$(CXX)  -lEvtGenExternal $(shell  root-config --libs)  obj/$(ARCH)/opalrivetevtgen.o -o ./bin/$(ARCH)/opalrivetevtgen  


bin/$(ARCH)/runProof: src/runProof.cxx  src/Helpers.cxx src/Helpers.h gen/TSampleInfoDict.cxx src/TSampleInfo.cxx
		mkdir -p ../bin/$(ARCH)
		$(CXX) -I. -g -DSIMPLE_HELPERS_ONLY $(shell  root-config --ldflags --glibs --cflags  ) -L$(shell root-config --config | sed 's@\ @\n@g' | grep "\-\-libdir=" | cut -f 2 -d=) -lProof  src/runProof.cxx  src/Helpers.cxx  gen/TSampleInfoDict.cxx src/TSampleInfo.cxx -o ./bin/$(ARCH)/runProof


bin/$(ARCH)/makeDB: src/makeDB.cxx  src/Helpers.cxx src/Helpers.h gen/TSampleInfoDict.cxx src/TSampleInfo.cxx src/TSampleInfo.h
		mkdir -p ../bin/$(ARCH)
		$(CXX) -I. -g -DSIMPLE_HELPERS_ONLY $(shell  root-config --ldflags --glibs --cflags  ) -L$(shell root-config --config | sed 's@\ @\n@g' | grep "\-\-libdir=" | cut -f 2 -d=) -lProof  src/makeDB.cxx  src/Helpers.cxx gen/TSampleInfoDict.cxx src/TSampleInfo.cxx  -o ./bin/$(ARCH)/makeDB



gen/DB.root: bin/$(ARCH)/makeDB
	bin/$(ARCH)/makeDB  gen/DB.root /scratch/andriish/opal/ntuple_root/qcd/
	
