# Makefile for the ROOT test programs.
# This Makefile shows nicely how to compile and link applications
# using the ROOT libraries on all supported platforms.
#
# Copyright (c) 2000 Rene Brun and Fons Rademakers
#
# Author: Fons Rademakers, 29/2/2000

#-----------------------------------------------------------------------------
#TARGET = 



ROOT-CONFIG    =     root-config
FASTJET-CONFIG =     fastjet-config

ObjSuf        = o
DllSuf        = so
OutPutOpt     = -o # keep whitespace after "-o"
SrcSuf        = cxx
SrcSuf2        = C
SrcSuf3        = fpp


FC                  =  $(shell  $(ROOT-CONFIG) --f77)
#CXX                 = g++-4.4
CXX                 =  $(shell  $(ROOT-CONFIG) --cxx)
#LD                  =  g++-4.4
LD                  = $(shell  $(ROOT-CONFIG) --ld)
LDFLAGS             =  -g -O0 -shared   $(shell  $(ROOT-CONFIG) --ldflags)
SOFLAGS             =  -g -shared 
FASTJET_LIBDIR=$(shell $(FASTJET-CONFIG) --libs |  tr ' ' '\n' | grep '\-L' | sed 's@-L@@g')


LDFLAGS+= -pipe -g  -lgfortran  -lgcc_s  $(shell $(FASTJET-CONFIG) --libs  --plugins)  $(shell $(ROOT-CONFIG) --libs) -lProofPlayer -lProof
CXXFLAGS+= -pipe -g -std=c++0x -Wall -Wextra  -Wno-unused-variable -Wno-unused-parameter -Wno-delete-non-virtual-dtor -I.  -fPIC  $(shell $(FASTJET-CONFIG) --cxxflags )  $(shell $(ROOT-CONFIG) --cflags) 
EVENTO        = $(TARGET).$(ObjSuf) $(TARGET)Dict.$(ObjSuf)\
				Cuts.$(ObjSuf) Helpers.$(ObjSuf) \
				TFastJet.$(ObjSuf)  \
				TAdvancedGraph.$(ObjSuf) TAdvancedGraphDict.$(ObjSuf) \
				TUserProofData.$(ObjSuf) TUserProofDataDict.$(ObjSuf) \
				TSampleInfo.$(ObjSuf)    TSampleInfoDict.$(ObjSuf)

ROOTMAP       =  lib$(TARGET).rootmap
                 
EVENTSO       = lib$(TARGET).$(DllSuf)
EVENTLIB      = $(EVENTSO)
OBJS          = $(EVENTO) 


.SUFFIXES: .$(SrcSuf) .$(SrcSuf2) .$(SrcSuf3) .$(ObjSuf) .$(DllSuf)

all:            $(EVENTLIB)  $(ROOTMAP)   

$(ROOTMAP): $(TARGET)LinkDef.h
	@printf "Building $(ROOTMAP) ... "
	rlibmap -f -o $@ -l lib$(TARGET).$(DllSuf) -d  \
	libMinuit.so libMLP.so libMatrix.so libTree.so  libTreePlayer.so libXMLIO.so \
	libTree.so libPhysics.so libThread.so libMatrix.so  libGpad.so libGraf3d.so \
	libGraf.so libHist.so libNet.so  libRIO.so libMathCore.so libCore libPyROOT.so \
	libGX11.so libGui.so libGX11TTF libProof.so  libProofPlayer.so libSessionViewer.so \
	$(FASTJET_LIBDIR)/libsiscone.so $(FASTJET_LIBDIR)/libfastjetplugins.so \
	$(FASTJET_LIBDIR)/libsiscone_spherical.so \
	$(FASTJET_LIBDIR)/libfastjettools.so $(FASTJET_LIBDIR)/libfastjet.so   -c $^	
	@echo "Done"

$(EVENTSO):     $(EVENTO)
		$(LD) $(SOFLAGS) $(LDFLAGS) $^ $(OutPutOpt) $@ $(EXPLLINKLIBS)  -Wl,--no-as-needed

clean:   
		rm -f $(PROGRAMS) $(EVENTSO) $(EVENTLIB) *Dict.* *.def *.exp \
		   *.so *.lib *.dll *.d *.log .def so_locations


%LinkDef.h: 
	rm -f $*LinkDef.h
	echo  "#ifdef __MAKECINT__"   >> $*LinkDef.h
	echo  "#pragma link C++ class "$*"+;"   >> $*LinkDef.h
	echo  "#endif"      >> $*LinkDef.h

%Dict.cxx:  %.h %LinkDef.h
	echo "Generating dictionary $@..."
	rootcint -f $@ -c  $*.h $*LinkDef.h



.$(SrcSuf)Dict.$(SrcSuf): .$(SrcSuf).h .$(SrcSuf)LinkDef.h
	echo "Generating dictionary $@..."
	rootcint -f $@ -c  $^

$(TARGET).$(ObjSuf): $(TARGET).h 

.$(SrcSuf).$(ObjSuf):
	$(CXX) $(CXXFLAGS) -c $<

.$(SrcSuf2).$(ObjSuf):
	$(CXX) $(CXXFLAGS)   -c $<

.$(SrcSuf3).$(ObjSuf):
	$(FC)   $(FFLAGS) -c $<

