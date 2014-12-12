# Makefile for the ROOT test programs.
# This Makefile shows nicely how to compile and link applications
# using the ROOT libraries on all supported platforms.
#
# Copyright (c) 2000 Rene Brun and Fons Rademakers
#
# Author: Fons Rademakers, 29/2/2000

#-----------------------------------------------------------------------------
TARGET = shape
TARGETPAW = shapePAW


ROOT-CONFIG   =     root-config
CLHEP-CONFIG  =     clhep-config
FASTJET-CONFIG = fastjet-config
CERNLIB = cernlib

ObjSuf        = o
DllSuf        = so
OutPutOpt     = -o # keep whitespace after "-o"
SrcSuf        = cxx
SrcSuf2        = cpp
SrcSuf3        = f


FC                  =  $(shell  $(ROOT-CONFIG) --f77)
CXX                 =  $(shell  $(ROOT-CONFIG) --cxx)
LD                  =  $(shell  $(ROOT-CONFIG) --ld)
LDFLAGS             =  -g -O0 -shared   $(shell  $(ROOT-CONFIG) --ldflags)
SOFLAGS             =  -g -shared 

LDFLAGS+=-lgfortran -lgcc_s -fPIC $(shell $(FASTJET-CONFIG) --libs  --plugins)  $(shell $(ROOT-CONFIG) --libs) -lProofPlayer -lProof -lHbook 
CXXFLAGS+=-I. -Wextra   -Wall -I./include -fPIC -shared  -Wextra  -Wall  $(shell $(FASTJET-CONFIG) --cxxflags ) $(shell $(ROOT-CONFIG) --cflags)
CPPFLAGS+=$(shell $(FASTJET-CONFIG) --cxxflags )
FFLAGS+=-fPIC

EVENTO        =  obj/$(TARGET)Dict.$(ObjSuf)\
		obj/ftnclose.$(ObjSuf)\
		obj/GlobalsUtil.$(ObjSuf)\
		obj/OPALObservable.$(ObjSuf)\
		obj/JADEQCDNtupProj.$(ObjSuf)\
		obj/Filein.$(ObjSuf)\
		obj/Ntuple.$(ObjSuf)\
		obj/Observable.$(ObjSuf)\
		obj/OPALLEP1QCDNtupProj.$(ObjSuf)\
		obj/JADEObservable.$(ObjSuf)\
		obj/OPALQCDNtupProj.$(ObjSuf)\
		obj/NewNtupleReader.$(ObjSuf)\
		obj/NtupleReader.$(ObjSuf)\
		obj/NtupProj.$(ObjSuf)\
		obj/hbook.$(ObjSuf)\
		obj/special.$(ObjSuf)\
		obj/TFastJet.$(ObjSuf)\

		
		
EVENTOPAW =	obj/$(TARGETPAW)Dict.$(ObjSuf)\
		obj/S4sub.$(ObjSuf)\
		obj/MomHist.$(ObjSuf)\
		obj/Hismanip.$(ObjSuf)\
		obj/Histogram.$(ObjSuf)

				
				 
				  
                 
EVENTSO       = lib/lib$(TARGET).$(DllSuf)
EVENTLIB      = $(EVENTSO)
OBJS          = $(EVENTO) 


EVENTSOPAW       = lib/lib$(TARGETPAW).$(DllSuf)
EVENTLIBPAW      = $(EVENTSOPAW)
OBJSPAW          = $(EVENTOPAW)




ROOTMAP       =  lib/lib$(TARGET).rootmap
ROOTMAPPAW       =  lib/lib$(TARGETPAW).rootmap


.SUFFIXES: .$(SrcSuf) .$(SrcSuf2) .$(SrcSuf3) .$(ObjSuf) .$(DllSuf)


all:   dirs         $(EVENTLIB)  $(EVENTLIBPAW) $(ROOTMAP) $(ROOTMAPPAW)


dirs:
	mkdir -p lib obj gen bin
	


$(ROOTMAP): 
	@printf "Building $(ROOTMAP) ... "
	rlibmap -f -o $@ -l lib$(TARGET).$(DllSuf) -d  $(shell $(CLHEP-CONFIG) --libs )/lib64/libCLHEP.so $(shell $(CLHEP-CONFIG) --libs )/lib/libCLHEP.so\
	 libPhysics.so libMinuit.so libMLP.so libMatrix.so libTree.so  libTreePlayer.so libXMLIO.so \
	 libTree.so libPhysics.so libThread.so libMatrix.so libTree.so  libGpad.so libGraf3d.so\
	  libGraf.so libHist.so libNet.so  libRIO.so libMathCore.so libCore libPyROOT.so\
	    libGX11.so libGui.so libGX11TTF libProof.so  libProofPlayer.so libSessionViewer.so\
	      libTreePlayer.so libPhysics.so  -c $^	
	@echo "Done"


$(ROOTMAPPAW): 
	@printf "Building $(ROOTMAPPAW) ... "
	rlibmap -f -o $@ -l lib$(TARGETPAW).$(DllSuf) -d  $(shell $(CLHEP-CONFIG) --libs )/lib64/libCLHEP.so $(shell $(CLHEP-CONFIG) --libs )/lib/libCLHEP.so\
	 libPhysics.so libMinuit.so libMLP.so libMatrix.so libTree.so  libTreePlayer.so libXMLIO.so \
	 libTree.so libPhysics.so libThread.so libMatrix.so libTree.so  libGpad.so libGraf3d.so\
	  libGraf.so libHist.so libNet.so  libRIO.so libMathCore.so libCore libPyROOT.so\
	    libGX11.so libGui.so libGX11TTF libProof.so  libProofPlayer.so libSessionViewer.so\
	      libTreePlayer.so libPhysics.so  -c $^	
	@echo "Done"


$(EVENTSO):     $(EVENTO)
		$(LD) $(SOFLAGS) $(LDFLAGS) $^ $(OutPutOpt) $@ $(EXPLLINKLIBS)

$(EVENTSOPAW):     $(EVENTOPAW)
		$(LD) $(SOFLAGS) $(LDFLAGS)  -L./lib -l$(TARGET) $^ $(OutPutOpt) $@ $(EXPLLINKLIBS)



clean:   
		@rm -f $(PROGRAMS) $(EVENTSO) $(EVENTLIB) *Dict.* *.def *.exp \
		   *.so *.lib *.dll *.d *.log .def so_locations  gen/*  lib/* obj/*

nice: 
	astyle -n --keep-one-line-blocks --style=gnu  ./src/*cxx ./include/*h 

doc:
	doxygen 

obj/$(TARGET).$(ObjSuf):  \
		include/OPALObservable.h\
		include/OPALQCDNtupProj.h\
		include/JADEQCDNtupProj.h\
		include/TFastJet.h\
		include/NtupProj.h\
		include/GlobalsUtil.h\
		include/NtupleReader.h\
		include/NewNtupleReader.h\
		include/OPALLEP1QCDNtupProj.h\
		include/nhmem.h\
		include/Observable.h\
		include/Ntuple.h\
		include/hbook.h\
		include/JADEObservable.h\
		include/Filein.h



gen/$(TARGET)Dict.$(SrcSuf): \
		include/OPALObservable.h\
		include/OPALQCDNtupProj.h\
		include/JADEQCDNtupProj.h\
		include/TFastJet.h\
		include/NtupProj.h\
		include/Ntuple.h\
		include/NtupleReader.h\
		include/OPALLEP1QCDNtupProj.h\
		include/JADEObservable.h\
		include/Filein.h\
		include/GlobalsUtil.h\
		include/$(TARGET)LinkDef.h
	@echo "Generating dictionary $@..."
	@rootcint -f $@ -c  $^



gen/$(TARGETPAW)Dict.$(SrcSuf): \
		include/S4sub.h\
		include/MomHist.h\
		include/Hismanip.h\
		include/Histogram.h\
		include/$(TARGETPAW)LinkDef.h
	@echo "Generating dictionary $@..."
	@rootcint -f $@ -c  $^



obj/$(TARGET)Dict.$(ObjSuf): gen/$(TARGET)Dict.$(SrcSuf)
	$(CXX) $(CXXFLAGS) -c $<  -o $@


obj/$(TARGETPAW)Dict.$(ObjSuf): gen/$(TARGETPAW)Dict.$(SrcSuf)
	$(CXX) $(CXXFLAGS) -c $<  -o $@



obj/%.$(ObjSuf): src/%.$(SrcSuf)
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/%.$(ObjSuf): src/%.$(SrcSuf2)
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/%.$(ObjSuf): src/%.$(SrcSuf3)
	$(FC)   $(FFLAGS) -c $< -o $@

