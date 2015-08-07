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
include Makefile.convert


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
		sed -i 's@.*BEAM_ENERGY_1.*@BEAM_ENERGY_1 = '$*';@g' run/Runsherpa.dat_$*
		sed -i 's@.*BEAM_ENERGY_2.*@BEAM_ENERGY_2 = '$*';@g' run/Runsherpa.dat_$*

run/Runherwig++.dat_%: share/Runherwig++.dat
		cp share/Runherwig++.dat run/Runherwig++.dat_$*
		sed -i 's@.*set LEPGenerator:EventHandler:LuminosityFunction:Energy.*@set LEPGenerator:EventHandler:LuminosityFunction:Energy '$(shell echo  $*+$* | bc -qi | tail -n 1)'@g' run/Runherwig++.dat_$*
		
run/Runevtgen.dat_%: share/Runevtgen.dat		
		cp share/Runevtgen.dat run/Runevtgen.dat_$*
		
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
	$(CXX) -pipe   -lpythia8 -lpythia8tohepmc -lHepMC obj/$(ARCH)/opalrivetpythia8.o -o ./bin/$(ARCH)/opalrivetpythia8  -L/lib64

bin/$(ARCH)/opalrivetpythia8_nohad:  dirs obj/$(ARCH)/opalrivetpythia8.o
	$(CXX) -pipe   -lpythia8 -lpythia8tohepmc -lHepMC obj/$(ARCH)/opalrivetpythia8.o -o ./bin/$(ARCH)/opalrivetpythia8_nohad  -L/lib64



obj/$(ARCH)/opalrivetpythia8_evtgen.o:  dirs src/opalrivetpythia8_evtgen.cxx
	$(CXX) -pipe  -c src/opalrivetpythia8_evtgen.cxx -o obj/$(ARCH)/opalrivetpythia8_evtgen.o -L/lib64 
	

bin/$(ARCH)/opalrivetpythia8_evtgen:  dirs obj/$(ARCH)/opalrivetpythia8_evtgen.o
	$(CXX) -pipe  -lpythia8 -lHepMC  -lEvtGenExternal  obj/$(ARCH)/opalrivetpythia8_evtgen.o -o ./bin/$(ARCH)/opalrivetpythia8_evtgen -L/lib64



obj/$(ARCH)/opalrivetevtgen.o:  dirs src/opalrivetevtgen.cxx
	$(CXX) -pipe  $(shell root-config --cflags) -c src/opalrivetevtgen.cxx -o obj/$(ARCH)/opalrivetevtgen.o
		
bin/$(ARCH)/opalrivetevtgen:  dirs obj/$(ARCH)/opalrivetevtgen.o
	$(CXX) -pipe   -lEvtGenExternal $(shell  root-config --libs)  obj/$(ARCH)/opalrivetevtgen.o -o ./bin/$(ARCH)/opalrivetevtgen   -L/lib64


bin/$(ARCH)/runProof: dirs src/runProof.cxx  src/Helpers.cxx src/Helpers.h gen/TSampleInfoDict.cxx src/TSampleInfo.cxx
		$(CXX) -pipe  -I. -g -DSIMPLE_HELPERS_ONLY $(shell  root-config --ldflags --glibs --cflags  ) -L$(shell root-config --config | sed 's@\ @\n@g' | grep "\-\-libdir=" | cut -f 2 -d=) -lProof  src/runProof.cxx  src/Helpers.cxx  gen/TSampleInfoDict.cxx src/TSampleInfo.cxx -o ./bin/$(ARCH)/runProof


bin/$(ARCH)/makeDB: dirs src/makeDB.cxx gen/TSampleInfoDict.cxx $(SOURCES)
		$(CXX) -pipe  -I. -g -DSIMPLE_HELPERS_ONLY $(shell  root-config --ldflags --glibs --cflags  ) -L$(shell root-config --config | sed 's@\ @\n@g' | grep "\-\-libdir=" | cut -f 2 -d=) -lProof  src/makeDB.cxx  src/Helpers.cxx gen/TSampleInfoDict.cxx src/TSampleInfo.cxx  -o ./bin/$(ARCH)/makeDB



gen/DB.root: dirs bin/$(ARCH)/makeDB $(SOURCES)
	bin/$(ARCH)/makeDB  gen/DB.root $(MNT)/scratch/andriish/opal/ntuple_root/qcd/
	




bin/$(ARCH)/plots: dirs src/plots/plots.cxx src/Helpers.cxx src/Helpers.h gen/TAdvancedGraphDict.cxx src/TAdvancedGraph.cxx src/TAdvancedGraph.h
		$(CXX) -pipe  -I. -Isrc -I../ -g  $(shell  root-config --ldflags --glibs --cflags  ) -L$(shell root-config --config | sed 's@\ @\n@g' | grep "\-\-libdir=" | cut -f 2 -d=) -lProof  src/plots/plots.cxx src/Helpers.cxx  gen/TAdvancedGraphDict.cxx src/TAdvancedGraph.cxx -o ./bin/$(ARCH)/plots


lib/$(ARCH)/libopalrivet.so:  dirs  src/Helpers.cxx src/Helpers.h gen/TAdvancedGraphDict.cxx src/TAdvancedGraph.cxx src/TAdvancedGraph.h
	$(CXX) -g -shared -fPIC -pipe  -I. -Isrc -I../ -g  $(shell  root-config --ldflags --glibs --cflags  ) -L$(shell root-config --config | sed 's@\ @\n@g' | grep "\-\-libdir=" | cut -f 2 -d=) -lProof   src/Helpers.cxx  gen/TAdvancedGraphDict.cxx src/TAdvancedGraph.cxx -o lib/$(ARCH)/libopalrivet.so

.rootrc: lib/$(ARCH)/libopalrivet.so
	echo Unix.*.Root.DynamicPath:  .:./lib/$(ARCH):$(shell root-config --libdir) > .rootrc
	echo Rint.Logon: ./rootlogon.C >> .rootrc
	echo 'rootlogon(){ gROOT->ProcessLine(".L ./lib/'$(ARCH)'/libopalrivet.so");}' >./rootlogon.C

output/plots_%.root: .rootrc dirs   bin/$(ARCH)/plots output/opal_%.root output/$(GEN)_%.root
	#we need so somewhere
	bin/$(ARCH)/plots $* output/opal_$*.root output/$(GEN)_$*.root
	
	
	
	
	
