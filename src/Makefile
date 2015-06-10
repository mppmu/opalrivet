# Makefile for the ROOT test programs.
# This Makefile shows nicely how to compile and link applications
# using the ROOT libraries on all supported platforms.
#
# Copyright (c) 2000 Rene Brun and Fons Rademakers
#
# Author: Fons Rademakers, 29/2/2000

#-----------------------------------------------------------------------------
#TARGET = 



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
FASTJET_LIBDIR=$(shell $(FASTJET-CONFIG) --libs |  tr ' ' '\n' | grep '\-L' | sed 's@-L@@g')


LDFLAGS+=-lgfortran  -g -lgcc_s  $(shell $(FASTJET-CONFIG) --libs  --plugins)  $(shell $(ROOT-CONFIG) --libs) -lProofPlayer -lProof
CXXFLAGS+=-I. -g -Wextra  -std=c++0x  -Wall -I.  -Wextra -fPIC  -Wall $(shell $(FASTJET-CONFIG) --cxxflags )  $(shell $(ROOT-CONFIG) --cflags)  -Wno-unused-variable
EVENTO        = $(TARGET).$(ObjSuf) $(TARGET)Dict.$(ObjSuf)\
				TFastJet.$(ObjSuf)  \
				TAdvancedGraph.$(ObjSuf) TAdvancedGraphDict.$(ObjSuf)\
				Cuts.$(ObjSuf) Helpers.$(ObjSuf)\
								TUserProofData.$(ObjSuf) TUserProofDataDict.$(ObjSuf)
#				TAutomaticSelector.$(ObjSuf) TAutomaticSelectorDict.$(ObjSuf)\


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
	    $(FASTJET_LIBDIR)/libfastjettools.so $(FASTJET_LIBDIR)/libfastjet.so $(FASTJET_LIBDIR)/libfastjetplugins.so $(FASTJET_LIBDIR)/libsiscone.so $(FASTJET_LIBDIR)/libsiscone_spherical.so\
	      libTreePlayer.so libPhysics.so  -c $^	
	@echo "Done"



$(EVENTSO):     $(EVENTO)
		$(LD) $(SOFLAGS) $(LDFLAGS) $^ $(OutPutOpt) $@ $(EXPLLINKLIBS)  -Wl,--no-as-needed

clean:   
		@rm -f $(PROGRAMS) $(EVENTSO) $(EVENTLIB) *Dict.* *.def *.exp \
		   *.so *.lib *.dll *.d *.log .def so_locations

nice: 
	astyle -n --keep-one-line-blocks --style=gnu  ./*cxx ./*h ./*C

.PHONY: TFastJetLinkDef.h TAutomaticSelectorLinkDef.h TAdvancedGraphLinkDef.h $(TARGET)LinkDef.h

$(TARGET)LinkDef.h:
	@rm -f $(TARGET)LinkDef.h
	@echo  "#ifdef __MAKECINT__"   >> $(TARGET)LinkDef.h
	@echo  "#pragma link C++ class "$(TARGET)"+;"   >> $(TARGET)LinkDef.h
	@echo  "#endif                ">> $(TARGET)LinkDef.h


TAutomaticSelectorLinkDef.h:
	@rm -f TAutomaticSelectorLinkDef.h
	@echo  "#ifdef __MAKECINT__"   >> TAutomaticSelectorLinkDef.h
	@echo  "#pragma link C++ class TAutomaticSelector+;"   >> TAutomaticSelectorLinkDef.h
	@echo  "#endif                ">> TAutomaticSelectorLinkDef.h


TUserProofDataLinkDef.h:
	@rm -f TUserProofDataLinkDef.h
	@echo  "#ifdef __MAKECINT__"   >> TUserProofDataLinkDef.h
	@echo  "#pragma link C++ class TUserProofData+;"   >> TUserProofDataLinkDef.h
	@echo  "#endif                ">> TUserProofDataLinkDef.h



TAdvancedGraphLinkDef.h:
	@rm -f TAdvancedGraphLinkDef.h
	@echo  "#ifdef __MAKECINT__"   >> TAdvancedGraphLinkDef.h
	@echo  "#pragma link C++ class TAdvancedGraph+;"   >> TAdvancedGraphLinkDef.h
	@echo  "#endif                ">> TAdvancedGraphLinkDef.h


TFastJetLinkDef.h:
	@rm -f TFastJetLinkDef.h
	@echo  "#ifdef __MAKECINT__"   >> TFastJetLinkDef.h
	@echo  "#pragma link C++ class TFastJet+;"   >> TFastJetLinkDef.h
	@echo  "#endif                ">> TFastJetLinkDef.h



.$(SrcSuf)Dict.$(SrcSuf): .$(SrcSuf).h .$(SrcSuf)LinkDef.h
	@echo "Generating dictionary $@..."
	@rootcint -f $@ -c  $^

TUserProofDataDict.$(SrcSuf): TUserProofData.h TUserProofDataLinkDef.h
	@echo "Generating dictionary $@..."
	@rootcint -f $@ -c  $^


TFastJetDict.$(SrcSuf): TFastJet.h TFastJetLinkDef.h
	@echo "Generating dictionary $@..."
	@rootcint -f $@ -c  $^

TAdvancedGraphDict.$(SrcSuf2): TAdvancedGraph.h TAdvancedGraphLinkDef.h
	@echo "Generating dictionary $@..."
	@rootcint -f $@ -c  $^

TAutomaticSelectorDict.$(SrcSuf2): TAutomaticSelector.h TAutomaticSelectorLinkDef.h
	@echo "Generating dictionary $@..."
	@rootcint -f $@ -c  $^






$(TARGET).$(ObjSuf): $(TARGET).h 

$(TARGET)Dict.$(SrcSuf): $(TARGET).h   $(TARGET)LinkDef.h
	@echo "Generating dictionary $@..."
	@rootcint -f $@ -c  $^

#TFastJet.h  TAdvancedGraph.h  TAutomaticSelector.h

.$(SrcSuf).$(ObjSuf):
	$(CXX) $(CXXFLAGS) -c $<

.$(SrcSuf2).$(ObjSuf):
	$(CXX) $(CXXFLAGS)   -c $<

TAutomaticSelector.$(ObjSuf): TAutomaticSelector.C TAutomaticSelector.h
	$(CXX) $(CXXFLAGS) -DTAutomaticSelector_cxx  -c $< TAutomaticSelector.C


.$(SrcSuf3).$(ObjSuf):
	$(FC)   $(FFLAGS) -c $<

