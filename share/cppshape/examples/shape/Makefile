# Makefile for the ROOT test programs.
# This Makefile shows nicely how to compile and link applications
# using the ROOT libraries on all supported platforms.
#
# Copyright (c) 2000 Rene Brun and Fons Rademakers
#
# Author: Fons Rademakers, 29/2/2000

#-----------------------------------------------------------------------------
TARGET = shape2



ROOT-CONFIG   =      /opt/i686/usr/bin/root-config
CLHEP-CONFIG  =      /opt/i686/usr/bin/clhep-config
FASTJET-CONFIG =  /opt/i686/usr/bin/fastjet-config
CERNLIB = /opt/i686/usr/bin/cernlib
ROOTCINT= /opt/i686/usr/bin/rootcint
 #export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/i686/usr/lib:/opt/i686/usr/lib/root:/opt/i686/usr/lib/cernlib/2006/lib/
ObjSuf        = o
DllSuf        = so
OutPutOpt     = -o # keep whitespace after "-o"
SrcSuf        = cxx
SrcSuf2        = cpp
SrcSuf3        = f


FC                  =  $(shell  $(ROOT-CONFIG) --f77 | sed 's@m64@m32@') -m32 #bug
CXX                 =  $(shell  $(ROOT-CONFIG) --cxx | sed 's@m64@m32@') -m32
LD                  =  $(shell  $(ROOT-CONFIG) --ld | sed 's@m64@m32@')  -m32
LDFLAGS             =  -g -O0    $(shell  $(ROOT-CONFIG) --ldflags | sed 's@m64@m32@') 
SOFLAGS             =  -g 

LDFLAGS+=  $(shell $(ROOT-CONFIG) --libs) 
LDFLAGS+=-lgfortran -lgcc_s  $(shell $(CERNLIB) packlib | sed 's@-Wl,-static@@g' )
CXXFLAGS+= -fdiagnostics-color=never -I. -Wextra  -I../../include -Wall -I./include  -Wextra  -Wall  $(shell $(FASTJET-CONFIG) --cxxflags | sed 's@m64@m32@') $(shell $(ROOT-CONFIG) --cflags | sed 's@m64@m32@')
CPPFLAGS+=$(shell $(FASTJET-CONFIG) --cxxflags )


all: dirs  bin/$(TARGET)

dirs:
	mkdir -p lib obj gen bin

clean:   
		@rm -f $(PROGRAMS) $(EVENTSO) $(EVENTLIB) *Dict.* *.def *.exp \
		   *.so *.lib *.dll *.d *.log .def so_locations  gen/*  lib/* obj/*

nice: 
	astyle -n --keep-one-line-blocks --style=gnu  ./src/*cxx ./include/*h 

doc:
	doxygen 
	
EVENTO  =  obj/$(TARGET)Dict.$(ObjSuf) obj/$(TARGET).$(ObjSuf)\
	obj/ntuple_200.$(ObjSuf)\
	obj/ntuple_200_lep1.$(ObjSuf)\
	obj/ntuple_107j.$(ObjSuf)\
	obj/ntuple_200j.$(ObjSuf)\
	obj/ntuple_108.$(ObjSuf)






gen/$(TARGET)Dict.$(SrcSuf): \
	include/ntuple_200.hh\
	include/ntuple_200_lep1.hh\
	include/ntuple_107j.hh\
	include/ntuple_200j.hh\
	include/ntuple_108.hh\
	include/$(TARGET)LinkDef.h
	@echo "Generating dictionary $@..."
	$(ROOTCINT)  -f $@  -c  -I../../include  $^    




bin/$(TARGET): $(EVENTO)
		$(LD) $(SOFLAGS) $(LDFLAGS) $^    ../../lib/libshape.a ../../lib/libshapePAW.a $(shell $(FASTJET-CONFIG) --libs --shared=no --plugins=yes)  $(OutPutOpt) $@ $(EXPLLINKLIBS)



obj/$(TARGET)Dict.$(ObjSuf): gen/$(TARGET)Dict.$(SrcSuf)
	$(CXX) $(CXXFLAGS) -c $<  -o $@

obj/%.$(ObjSuf): src/%.$(SrcSuf)
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/%.$(ObjSuf): src/%.$(SrcSuf2)
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/%.$(ObjSuf): src/%.$(SrcSuf3)
	$(FC)   $(FFLAGS) -c $<  -o $@

