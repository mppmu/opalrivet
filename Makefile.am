# Process this file with automake to produce Makefile.in (in this,
# and all subdirectories).
# Makefile for the top-level directory of GNU hello.
#
# Copyright 1997, 1998, 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2013,
# 2014 Free Software Foundation, Inc.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.






## Place generated object files (.o) into the same directory as their source
## files, in order to avoid collisions when non-recursive make is used.
AUTOMAKE_OPTIONS = subdir-objects check-news gnu

AM_CFLAGS =  
# -Wno-long-long -Wall -Wextra   -Werror -pedantic -Wno-error=long-long 
AM_CXXFLAGS = 
#-Wno-long-long -Wall -Wextra   -Werror -pedantic -Wno-error=long-long 

## Additional flags to pass to aclocal when it is invoked automatically at
## make time. The ${ACLOCAL_FLAGS} variable is picked up from the environment
## to provide a way for the user to supply additional arguments.
#ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I .
#ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}   -I .
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4
AM_CPPFLAGS = -Ilib -I$(top_srcdir)/lib -Isrc -I$(top_srcdir)/src

#export X509_USER_PROXY=$(pwd)/k5-ca-proxy.pem
#GEN=sherpa
#GEN=herwig++
#GEN=pythia8

#GEN=evtgen
#GEN?=pythia8
#GEN=pythia8_evtgen
#CUTS?=central
NAME=JADE_OPAL_2000_S4300807a
ARCH          =   $(shell uname -m)
#CXX?='g++ -Wextra -Wall -pedantic -Wno-long-long -Wno-variadic-macros'
include Makefile.syst

warn: 
	echo 'ARE YOU SURE?'


all:	 		    output/$(GEN)_91_$(CUTS).root \
					output/opal_9196_$(CUTS).root \
					output/opal_9197_$(CUTS).root \
					output/opal_9198_$(CUTS).root \
					output/opal_9199_$(CUTS).root \
					output/opal_9100_$(CUTS).root \
					output/opal_130_$(CUTS).root output/$(GEN)_130.root \
					output/opal_136_$(CUTS).root output/$(GEN)_136.root \
					output/opal_161_$(CUTS).root output/$(GEN)_161.root \
					output/opal_172_$(CUTS).root output/$(GEN)_172.root \
					output/opal_183_$(CUTS).root output/$(GEN)_183.root \
					output/opal_189_$(CUTS).root output/$(GEN)_189.root \
					output/opal_192_$(CUTS).root output/$(GEN)_192.root \
					output/opal_196_$(CUTS).root output/$(GEN)_196.root \
					output/opal_202_$(CUTS).root output/$(GEN)_202.root \
					output/opal_205_$(CUTS).root output/$(GEN)_205.root \
					output/opal_207_$(CUTS).root output/$(GEN)_207.root


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
					output/opal_9196_$(CUTS).root \
					output/opal_9197_$(CUTS).root \
					output/opal_9198_$(CUTS).root \
					output/opal_9199_$(CUTS).root \
					output/opal_9100_$(CUTS).root \
					output/opal_130_$(CUTS).root \
					output/opal_136_$(CUTS).root \
					output/opal_161_$(CUTS).root \
					output/opal_172_$(CUTS).root \
					output/opal_183_$(CUTS).root \
					output/opal_189_$(CUTS).root \
					output/opal_192_$(CUTS).root \
					output/opal_196_$(CUTS).root \
					output/opal_202_$(CUTS).root \
					output/opal_205_$(CUTS).root \
					output/opal_207_$(CUTS).root



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
	mkdir -p logs
	mkdir -p subs_output

gen/%LinkDef.h: dirs
	@rm -f gen/$*LinkDef.h
	@echo  "#ifdef __MAKECINT__"   >> gen/$*LinkDef.h
	@echo  "#pragma link C++ class "$*"+;"   >> gen/$*LinkDef.h
	@echo  "#endif"      >> gen/$*LinkDef.h

gen/%Dict.cxx: dirs src/%.h gen/%LinkDef.h
	echo "Generating dictionary $@..."
	rootcint -f $@ -c  src/$*.h gen/$*LinkDef.h



	
SOURCES=src/Helpers.cxx         src/Helpers.h \
		            src/Cuts.h \
		src/TSampleInfo.cxx     src/TSampleInfo.h \
		src/OPALJet.cxx        src/OPALJet.h  \
		src/TAdvancedGraph.cxx  src/TAdvancedGraph.h \
		src/TUserProofData.cxx 	src/TUserProofData.h
	



output/opal_%.root:   dirs $(SOURCES)    bin/$(ARCH)/create_proof       src/opalanalysis.C gen/DB.root
		bin/$(ARCH)/create_proof  LOCAL_OPAL_$* share/input.rc

	
output/$(GEN)_%.root: dirs $(SOURCES)	 bin/$(ARCH)/opal$(GEN) run/Run$(GEN).dat_%  run/Makefile external/Rivet/src/Analyses/JADE_OPAL_2000_S4300807a.cc
		make -C run GEN=$(GEN) ENERGY=$*
		mv run/*.root ./output

	
run/Runpythia8.dat_%: 	bin/$(ARCH)/opal$(GEN)
		mkdir -p run		
		cp share/Runpythia8.dat run/Runpythia8.dat_$*		
		sed -i 's@.*Beams:eCM.*@Beams:eCM = '$(shell echo  1.0*$* | bc -qi | tail -n 1)'@g' run/Runpythia8.dat_$*

run/Runpythia8_nohad.dat_%: share/Runpythia8_nohad.dat
		cp share/Runpythia8_nohad.dat run/Runpythia8_nohad.dat		
		sed -i 's@.*Beams:eCM.*@Beams:eCM = '$(shell echo  1.0*$* | bc -qi | tail -n 1)'@g' run/Runpythia8_nohad.dat_$*

run/Runpythia8_evtgen.dat_%: share/Runpythia8_evtgen.dat
		cp share/Runpythia8_evtgen.dat run/Runpythia8_evtgen.dat_$*		
		sed -i 's@.*Beams:eCM.*@Beams:eCM = '$(shell echo  1.0*$* | bc -qi | tail -n 1)'@g' run/Runpythia8_evtgen.dat_$*


run/Runsherpa.dat_%: share/Runsherpa.dat
		cp share/Runsherpa.dat run/Runsherpa.dat_$*
		sed -i 's@.*BEAM_ENERGY_1.*@BEAM_ENERGY_1 = '$(shell echo  0.5*$* | bc -qi | tail -n 1)';@g' run/Runsherpa.dat_$*
		sed -i 's@.*BEAM_ENERGY_2.*@BEAM_ENERGY_2 = '$(shell echo  0.5*$* | bc -qi | tail -n 1)';@g' run/Runsherpa.dat_$*

run/Runherwig++.dat_%: share/Runherwig++.dat
		cp share/Runherwig++.dat run/Runherwig++.dat_$*
		sed -i 's@.*set LEPGenerator:EventHandler:LuminosityFunction:Energy.*@set LEPGenerator:EventHandler:LuminosityFunction:Energy '$(shell echo  1.0*$* | bc -qi | tail -n 1)'@g' run/Runherwig++.dat_$*
		
run/Runevtgen.dat_%: share/Runevtgen.dat		
		cp share/Runevtgen.dat run/Runevtgen.dat_$*
		
run/Makefile: share/Makefile.run		
		cp share/Makefile.run run/Makefile


beauty:
		astyle -n --keep-one-line-blocks --style=gnu    ./*/*.h   ./*/*.cxx ./*/*.C ./*/*.hh

bin/$(ARCH)/opal$(GEN):
	rm -f bin/$(ARCH)/opal$(GEN)
	touch bin/$(ARCH)/opal$(GEN)


obj/$(ARCH)/opalpythia8.o:  dirs src/MC/opalpythia8.cxx
	$(CXX) -fdiagnostics-color=never   -pipe  -c src/MC/opalpythia8.cxx -o obj/$(ARCH)/opalpythia8.o 
	
	
	
	
bin/$(ARCH)/opalpythia8:  dirs obj/$(ARCH)/opalpythia8.o
	$(CXX) -fdiagnostics-color=never   -pipe   -lpythia8 -lpythia8tohepmc -lHepMC obj/$(ARCH)/opalpythia8.o -o ./bin/$(ARCH)/opalpythia8  -L/lib64

bin/$(ARCH)/opalpythia8_nohad:  dirs obj/$(ARCH)/opalpythia8.o
	$(CXX) -fdiagnostics-color=never   -pipe   -lpythia8 -lpythia8tohepmc -lHepMC obj/$(ARCH)/opalpythia8.o -o ./bin/$(ARCH)/opalpythia8_nohad  -L/lib64



obj/$(ARCH)/opalpythia8_evtgen.o:  dirs src/MC/opalpythia8_evtgen.cxx
	$(CXX) -fdiagnostics-color=never   -pipe  -c src/MC/opalpythia8_evtgen.cxx -o obj/$(ARCH)/opalpythia8_evtgen.o -L/lib64 
	

bin/$(ARCH)/opalpythia8_evtgen:  dirs obj/$(ARCH)/opalpythia8_evtgen.o
	$(CXX) -fdiagnostics-color=never   -pipe  -lpythia8 -lHepMC  -lEvtGenExternal  obj/$(ARCH)/opalpythia8_evtgen.o -o ./bin/$(ARCH)/opalpythia8_evtgen -L/lib64



obj/$(ARCH)/opalevtgen.o:  dirs src/opalevtgen.cxx
	$(CXX) -fdiagnostics-color=never   -pipe  $(shell root-config --cflags) -c src/opalevtgen.cxx -o obj/$(ARCH)/opalevtgen.o
		
bin/$(ARCH)/opalevtgen:  dirs obj/$(ARCH)/opalevtgen.o
	$(CXX) -fdiagnostics-color=never   -pipe   -lEvtGenExternal $(shell  root-config --libs)  obj/$(ARCH)/opalevtgen.o -o ./bin/$(ARCH)/opalevtgen   -L/lib64


bin/$(ARCH)/create_proof: dirs src/create_proof.cxx  src/Helpers.cxx src/Helpers.h gen/TSampleInfoDict.cxx src/TSampleInfo.cxx
		$(CXX) -fdiagnostics-color=never   -pipe  -I. -g -DSIMPLE_HELPERS_ONLY $(shell  root-config --ldflags --glibs --cflags  ) -L$(shell root-config --config | sed 's@\ @\n@g' | grep "\-\-libdir=" | cut -f 2 -d=) -lProof  src/create_proof.cxx  src/Helpers.cxx  gen/TSampleInfoDict.cxx src/TSampleInfo.cxx -o ./bin/$(ARCH)/create_proof


bin/$(ARCH)/create_DB: dirs src/create_DB.cxx gen/TSampleInfoDict.cxx $(SOURCES)
		$(CXX) -fdiagnostics-color=never   -pipe  -I. -g -DSIMPLE_HELPERS_ONLY $(shell  root-config --ldflags --glibs --cflags  ) -L$(shell root-config --config | sed 's@\ @\n@g' | grep "\-\-libdir=" | cut -f 2 -d=) -lProof  src/create_DB.cxx  src/Helpers.cxx gen/TSampleInfoDict.cxx src/TSampleInfo.cxx  -o ./bin/$(ARCH)/create_DB



gen/DB.root: dirs bin/$(ARCH)/create_DB
	bin/$(ARCH)/create_DB  gen/DB.root $(MNT)/scratch/andriish/opal/ntuple_root/qcd/
	




bin/$(ARCH)/create_plots: dirs src//create_plots.cxx src/Helpers.cxx src/Helpers.h gen/TAdvancedGraphDict.cxx src/TAdvancedGraph.cxx src/TAdvancedGraph.h
		$(CXX) -fdiagnostics-color=never   -pipe  -I. -Isrc -I../ -g  $(shell  root-config --ldflags --glibs --cflags  ) -L$(shell root-config --config | sed 's@\ @\n@g' | grep "\-\-libdir=" | cut -f 2 -d=) -lProof  src//create_plots.cxx src/Helpers.cxx  gen/TAdvancedGraphDict.cxx src/TAdvancedGraph.cxx -o ./bin/$(ARCH)/create_plots



bin/$(ARCH)/create_specialplots: dirs src//create_specialplots.cxx src/Helpers.cxx src/Helpers.h gen/TAdvancedGraphDict.cxx src/TAdvancedGraph.cxx src/TAdvancedGraph.h
		$(CXX) -fdiagnostics-color=never   -pipe  -I. -Isrc -I../ -g  $(shell  root-config --ldflags --glibs --cflags  ) -L$(shell root-config --config | sed 's@\ @\n@g' | grep "\-\-libdir=" | cut -f 2 -d=) -lProof  src//create_specialplots.cxx src/Helpers.cxx  gen/TAdvancedGraphDict.cxx src/TAdvancedGraph.cxx -o ./bin/$(ARCH)/create_specialplots



bin/$(ARCH)/create_tables: dirs src//create_tables.cxx src/Helpers.cxx src/Helpers.h gen/TAdvancedGraphDict.cxx src/TAdvancedGraph.cxx src/TAdvancedGraph.h
		$(CXX) -fdiagnostics-color=never   -pipe  -I. -Isrc -I../ -g  $(shell  root-config --ldflags --glibs --cflags  ) -L$(shell root-config --config | sed 's@\ @\n@g' | grep "\-\-libdir=" | cut -f 2 -d=) -lProof  src//create_tables.cxx src/Helpers.cxx  gen/TAdvancedGraphDict.cxx src/TAdvancedGraph.cxx -o ./bin/$(ARCH)/create_tables




bin/$(ARCH)/create_manip: dirs src//create_manip.cxx src/Helpers.cxx src/Helpers.h gen/TAdvancedGraphDict.cxx src/TAdvancedGraph.cxx src/TAdvancedGraph.h
		$(CXX) -fdiagnostics-color=never   -pipe  -I. -Isrc -I../ -g  $(shell  root-config --ldflags --glibs --cflags  ) -L$(shell root-config --config | sed 's@\ @\n@g' | grep "\-\-libdir=" | cut -f 2 -d=) -lProof  src//create_manip.cxx src/Helpers.cxx  gen/TAdvancedGraphDict.cxx src/TAdvancedGraph.cxx -o ./bin/$(ARCH)/create_manip



bin/$(ARCH)/create_old: dirs src//create_old.cxx src/Helpers.cxx src/Helpers.h gen/TAdvancedGraphDict.cxx src/TAdvancedGraph.cxx src/TAdvancedGraph.h
		$(CXX) -fdiagnostics-color=never   -pipe  -I. -fdiagnostics-color=never  -Isrc -I../ -g  $(shell  root-config --ldflags --glibs --cflags  ) -L$(shell root-config --config | sed 's@\ @\n@g' | grep "\-\-libdir=" | cut -f 2 -d=) -lProof  src//create_old.cxx src/Helpers.cxx  gen/TAdvancedGraphDict.cxx src/TAdvancedGraph.cxx -o ./bin/$(ARCH)/create_old




lib/$(ARCH)/libopal.so:  dirs  src/Helpers.cxx src/Helpers.h gen/TAdvancedGraphDict.cxx src/TAdvancedGraph.cxx src/TAdvancedGraph.h  gen/TAdvancedGraphLinkDef.h
	$(CXX) -fdiagnostics-color=never -Wextra -Wall -pedantic -Wno-long-long -Wno-variadic-macros -g -shared -fPIC -pipe  -I. -Isrc -I../ -g  $(shell  root-config --ldflags --glibs --cflags  ) -L$(shell root-config --config | sed 's@\ @\n@g' | grep "\-\-libdir=" | cut -f 2 -d=) -lProof   src/Helpers.cxx  gen/TAdvancedGraphDict.cxx src/TAdvancedGraph.cxx -o lib/$(ARCH)/libopal.so
	rlibmap -f -o lib/$(ARCH)/libopal.rootmap -l lib/$(ARCH)/libopal.so  -c gen/TAdvancedGraphLinkDef.h
	
.rootrc: lib/$(ARCH)/libopal.so
	echo Unix.*.Root.DynamicPath:  .:./lib/$(ARCH):$(shell root-config --libdir) > .rootrc
	echo Rint.Logon: ./rootlogon.C >> .rootrc
	echo 'rootlogon(){ gROOT->ProcessLine(".L ./lib/'$(ARCH)'/libopal.so");}' >./rootlogon.C



output/plots_%.root: .rootrc dirs   bin/$(ARCH)/create_plots output/opal_%.root output/$(GEN)_%.root output/shapemanip_%.root output/old_%.root
	bin/$(ARCH)/create_plots $* output/opal_$*.root output/$(GEN)_$*.root output/shapemanip_$*.root output/old_$*.root


output/tables_%.tex: .rootrc dirs   bin/$(ARCH)/create_tables 
	bin/$(ARCH)/create_tables  output/plots_$*.root  output/tables_$*.tex
	
doc/opalanalysis.pdf:  doc/opalanalysis.tex
		$(MAKE) $(shell cat doc/opalanalysis.tex | grep output/tables | sed 's@\input{../@@g' | grep -v '%' | sed 's@}@@g' )
		pdflatex doc/opalanalysis.tex
		mv opalanalysis.pdf  doc/opalanalysis.pdf

#pdf-local: doc/opalanalysis.pdf


bin/$(ARCH)/hepplotconvert: dirs   external/hepplotconvert/WriterROOT.h external/hepplotconvert/ROOTConvert.cc external/hepplotconvert/ROOTConvert.h external/hepplotconvert/ReaderROOT.cc external/hepplotconvert/ReaderROOT.h external/hepplotconvert/hepplotconvert.cxx external/hepplotconvert/WriterROOT.cc
		$(CXX) -fdiagnostics-color=never   -pipe  -fdiagnostics-color=never  -I. -g -fdiagnostics-color=never  $(shell  yoda-config --ldflags --libs --cflags  )  $(shell  root-config --ldflags --glibs --cflags  ) -L$(shell root-config --config | sed 's@\ @\n@g' | grep "\-\-libdir=" | cut -f 2 -d=) -lProof  external/hepplotconvert/WriterROOT.h external/hepplotconvert/ROOTConvert.cc external/hepplotconvert/ROOTConvert.h external/hepplotconvert/ReaderROOT.cc external/hepplotconvert/ReaderROOT.h external/hepplotconvert/hepplotconvert.cxx external/hepplotconvert/WriterROOT.cc -o ./bin/$(ARCH)/hepplotconvert

	
output/JADE_OPAL_2000_S4300807.root: bin/$(ARCH)/hepplotconvert external/Rivet/data/refdata/JADE_OPAL_2000_S4300807a.yoda
	bin/$(ARCH)/hepplotconvert yoda2root external/Rivet/data/refdata/JADE_OPAL_2000_S4300807a.yoda output/JADE_OPAL_2000_S4300807.root


output/OPAL_2000_S4306783.root: bin/$(ARCH)/hepplotconvert external/Rivet/data/refdata/OPAL_2000_S4306783.yoda
	bin/$(ARCH)/hepplotconvert yoda2root external/Rivet/data/refdata/OPAL_2000_S4306783.yoda output/OPAL_2000_S4306783.root

output/OPAL_2004_S6132243.root: bin/$(ARCH)/hepplotconvert external/Rivet/data/refdata/OPAL_2004_S6132243.yoda
	bin/$(ARCH)/hepplotconvert yoda2root external/Rivet/data/refdata/OPAL_2004_S6132243.yoda output/OPAL_2004_S6132243.root

output/old_%.root: dirs bin/$(ARCH)/create_old output/JADE_OPAL_2000_S4300807.root output/OPAL_2004_S6132243.root output/OPAL_2000_S4306783.root
	bin/$(ARCH)/create_old   output/old_$*.root nevermind output/JADE_OPAL_2000_S4300807.root output/OPAL_2004_S6132243.root output/OPAL_2000_S4306783.root


output/shapemanip_%.root: dirs bin/$(ARCH)/create_manip    .rootrc
	mkdir -p subs_output
	rm -f output/shape_$*.root
	$(MAKE) output/shape_$*.root
#ifeq  ($%, '91')
#		external/cppshape/examples/shape/bin/shape2 A output/shape_$* external/cppshape/examples/shape/QCDadmin/QCDadmin_200_$*.txt
#else
#		external/cppshape/examples/shape/bin/shape2 P output/shape_$* external/cppshape/examples/shape/QCDadmin/QCDadmin_200_$*.txt
#endif
#	h2root  output/shape_$*_manip.rzhist
#	h2root  output/shape_$*.rzhist
	bin/$(ARCH)/create_manip   tmp/shapemanip_$*_durham.root durham output/shape_$*_manip.root output/shape_$*.root
	bin/$(ARCH)/create_manip   tmp/shapemanip_$*_antikt.root antikt output/shape_$*_manip.root output/shape_$*.root
	hadd -f output/shapemanip_$*.root tmp/shapemanip_$*_antikt.root tmp/shapemanip_$*_durham.root

output/shape_%.root:
				make -C external/cppshape clean
				make -C external/cppshape/examples/shape clean
				make -C external/cppshape
				make -C external/cppshape/examples/shape
			    rm -rf output_200_$*.rzhist
			    external/cppshape/examples/shape/bin/shape2 P /scratch/andriish/opal/ntuple/qcd/  external/cppshape/examples/shape/QCDadmin/QCDadmin_200_$*.txt
				mv  output_200_$*.rzhist output/shape_$*.rzhist
				h2root output/shape_$*.rzhist


output/shape_91.root:
				make -C external/cppshape clean
				make -C external/cppshape/examples/shape clean
				make -C external/cppshape
				make -C external/cppshape/examples/shape
			    rm -rf output_200_91.rzhist
			    external/cppshape/examples/shape/bin/shape2 A /scratch/andriish/opal/ntuple/qcd/  external/cppshape/examples/shape/QCDadmin/QCDadmin_200_91.txt
				mv  output_200_91.rzhist output/shape_91.rzhist
				h2root output/shape_91.rzhist




bin/$(ARCH)/create_systematics: dirs src//create_systematics.cxx src/Helpers.cxx src/Helpers.h gen/TAdvancedGraphDict.cxx src/TAdvancedGraph.cxx src/TAdvancedGraph.h
		$(CXX) -fdiagnostics-color=never   -pipe  -I. -Isrc -I../ -g  $(shell  root-config --ldflags --glibs --cflags  ) -L$(shell root-config --config | sed 's@\ @\n@g' | grep "\-\-libdir=" | cut -f 2 -d=) -lProof  src//create_systematics.cxx src/Helpers.cxx  gen/TAdvancedGraphDict.cxx src/TAdvancedGraph.cxx -o ./bin/$(ARCH)/create_systematics



uclean:
	rm -rf output/*
	rm -rf subs_output/*	
	rm -rf gen/*
	rm -rf tmp/*
	
	

MOSTLYCLEANFILES = $(DX_CLEANFILES)
include m4/aminclude.am

EXTRA_DIST = Doxyfile

uninstall-local:
		rm $(DESTDIR)$(datadir)/$(PACKAGE)/html/
		-rmdir $(DESTDIR)$(datadir)/$(PACKAGE)/html 
install: install-am install-rootmap install-examples


	
