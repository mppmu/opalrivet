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



all: dirs mc_91	 data_91 

#all: dirs mc_189	 data_189  




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
	
data_%:  bin/$(ARCH)/runProof 
	bin/$(ARCH)/runProof  LOCAL_OPAL_$*

pics: bin/$(ARCH)/plots
	bin/$(ARCH)/plots 91
	bin/$(ARCH)/plots 130
	bin/$(ARCH)/plots 161		
	bin/$(ARCH)/plots 172
	bin/$(ARCH)/plots 183	
	bin/$(ARCH)/plots 189	


	
mc_%: 	bin/$(ARCH)/opalrivet$(GEN)
		mkdir -p run
		
		cp share/Runpythia8.dat run		
		sed -i 's@.*Beams:eCM.*@Beams:eCM = '$(shell echo  $* | bc -qi | tail -n 1)'@g' run/Runpythia8.dat

		cp share/Runpythia8_nohad.dat run		
		sed -i 's@.*Beams:eCM.*@Beams:eCM = '$(shell echo  $*+$* | bc -qi | tail -n 1)'@g' run/Runpythia8_nohad.dat

		cp share/Runpythia8_evtgen.dat run		
		sed -i 's@.*Beams:eCM.*@Beams:eCM = '$(shell echo  $*+$* | bc -qi | tail -n 1)'@g' run/Runpythia8_evtgen.dat



		cp share/Runsherpa.dat run
		sed -i 's@.*BEAM_ENERGY_1.*@BEAM_ENERGY_1 = '$*';@g' run/Runsherpa.dat
		sed -i 's@.*BEAM_ENERGY_2.*@BEAM_ENERGY_2 = '$*';@g' run/Runsherpa.dat

		cp share/Runherwig++.dat run
		sed -i 's@.*set LEPGenerator:EventHandler:LuminosityFunction:Energy.*@set LEPGenerator:EventHandler:LuminosityFunction:Energy '$(shell echo  $*+$* | bc -qi | tail -n 1)'@g' run/Runherwig++.dat
		
		
		cp share/Runevtgen.dat run
		
		
		cp share/Makefile.run run/Makefile
		make -C run GEN=$(GEN)
		mv run/*.root ./output


beauty:
		astyle -n --keep-one-line-blocks --style=gnu    ./*cc

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

bin/$(ARCH)/prof: dirs src/pprroffessorr.cxx
		$(CXX) $(shell root-config --cflags --glibs )  -lMinuit src/pprroffessorr.cxx -o bin/$(ARCH)/prof

bin/$(ARCH)/draw: dirs  src/draw.cxx
		$(CXX) $(shell root-config --cflags --glibs )  -lMinuit draw.cxx -o bin/$(ARCH)/draw

bin/$(ARCH)/runProof: src/runProof.cxx
		mkdir -p ../bin/$(ARCH)
		$(CXX)  -g -DSIMPLE_HELPERS_ONLY $(shell  root-config --ldflags --glibs --cflags  ) -L$(shell root-config --config | sed 's@\ @\n@g' | grep "\-\-libdir=" | cut -f 2 -d=) -lProof  src/runProof.cxx  -o ./bin/$(ARCH)/runProof

bin/$(ARCH)/plots: src/plots.cxx
		mkdir -p ../bin/$(ARCH)
		$(CXX) -g -I. -DSIMPLE_HELPERS_ONLY $(shell  root-config --ldflags --libs --cflags  ) -L$(shell root-config --config | sed 's@\ @\n@g' | grep "\-\-libdir=" | cut -f 2 -d=) -lProof -I./Code src/plots.cxx  src/TAdvancedGraph.cxx src/Helpers.cxx  -o ./bin/$(ARCH)/plots


