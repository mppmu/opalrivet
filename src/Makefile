# Makefile for the ROOT test programs.
# This Makefile shows nicely how to compile and link applications
# using the ROOT libraries on all supported platforms.
#
# Copyright (c) 2000 Rene Brun and Fons Rademakers
#
# Author: Fons Rademakers, 29/2/2000

#-----------------------------------------------------------------------------
TARGET = 



ROOT-CONFIG   =     root-config


FASTJET-CONFIG = fastjet-config

ObjSuf        = o
DllSuf        = so
OutPutOpt     = -o # keep whitespace after "-o"
SrcSuf        = cxx
SrcSuf2        = C
SrcSuf3        = fpp


FC                  =  $(shell  $(ROOT-CONFIG) --f77)
CXX                 =  $(shell  $(ROOT-CONFIG) --cxx)
LD                  =  $(shell  $(ROOT-CONFIG) --ld)
LDFLAGS             =  -g -O0 -shared   $(shell  $(ROOT-CONFIG) --ldflags)
SOFLAGS             =  -g -shared 

LDFLAGS+=-lgfortran  -g -lgcc_s  $(shell $(FASTJET-CONFIG) --libs  --plugins)  $(shell $(ROOT-CONFIG) --libs) -lProofPlayer -lProof
CXXFLAGS+=-I. -g -Wextra  -std=c++0x  -Wall -I.  -Wextra -fPIC  -Wall $(shell $(FASTJET-CONFIG) --cxxflags )  $(shell $(ROOT-CONFIG) --cflags)  -Wno-unused-variable
EVENTO        = $(TARGET).$(ObjSuf) $(TARGET)Dict.$(ObjSuf)\
				TFastJet.$(ObjSuf)

ROOTMAP       =  lib$(TARGET).rootmap
                 
EVENTSO       = lib$(TARGET).$(DllSuf)
EVENTLIB      = $(EVENTSO)
OBJS          = $(EVENTO) 


.SUFFIXES: .$(SrcSuf) .$(SrcSuf2) .$(SrcSuf3) .$(ObjSuf) .$(DllSuf)

all:            $(EVENTLIB)  $(ROOTMAP)   

$(ROOTMAP): $(TARGET)LinkDef.h
	@printf "Building $(ROOTMAP) ... "
	rlibmap -f -o $@ -l lib$(TARGET).$(DllSuf) -d  \
	 libPhysics.so libMinuit.so libMLP.so libMatrix.so libTree.so  libTreePlayer.so libXMLIO.so \
	 libTree.so libPhysics.so libThread.so libMatrix.so libTree.so  libGpad.so libGraf3d.so\
	  libGraf.so libHist.so libNet.so  libRIO.so libMathCore.so libCore libPyROOT.so\
	    libGX11.so libGui.so libGX11TTF libProof.so  libProofPlayer.so libSessionViewer.so\
	    libfastjettools.so libfastjet.so libfastjetplugins.so\
	      libTreePlayer.so libPhysics.so  -c $^	
	@echo "Done"


$(EVENTSO):     $(EVENTO)
		$(LD) $(SOFLAGS) $(LDFLAGS) $^ $(OutPutOpt) $@ $(EXPLLINKLIBS)  -Wl,--no-as-needed

clean:   
		@rm -f $(PROGRAMS) $(EVENTSO) $(EVENTLIB) *Dict.* *.def *.exp \
		   *.so *.lib *.dll *.d *.log .def so_locations

nice: 
	astyle -n --keep-one-line-blocks --style=gnu  ./*cxx ./*h ./*C


$(TARGET).$(ObjSuf): $(TARGET).h 

$(TARGET)Dict.$(SrcSuf): $(TARGET).h  TFastJet.h  $(TARGET)LinkDef.h
	@echo "Generating dictionary $@..."
	@rootcint -f $@ -c  $^

.$(SrcSuf).$(ObjSuf):
	$(CXX) $(CXXFLAGS) -c $<

.$(SrcSuf2).$(ObjSuf):
	$(CXX) $(CXXFLAGS) -c $<

.$(SrcSuf3).$(ObjSuf):
	$(FC)   $(FFLAGS) -c $<
