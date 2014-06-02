# Makefile for the ROOT test programs.
# This Makefile shows nicely how to compile and link applications
# using the ROOT libraries on all supported platforms.
#
# Copyright (c) 2000 Rene Brun and Fons Rademakers
#
# Author: Fons Rademakers, 29/2/2000

#-----------------------------------------------------------------------------
TARGET = readtree



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
LDFLAGS             =  -g -O0   
SOFLAGS             =  -g 

LDFLAGS+=  $(shell $(ROOT-CONFIG) --libs) -lProofPlayer -lProof -lHbook
LDFLAGS+=-L../../lib -lshape  $(shell $(CERNLIB) packlib )
CXXFLAGS+=-I. -Wextra  -I../../include -Wall -I./include  -Wextra  -Wall  $(shell $(FASTJET-CONFIG) --cxxflags ) $(shell $(ROOT-CONFIG) --cflags)
CPPFLAGS+=$(shell $(FASTJET-CONFIG) --cxxflags )


all: dirs bin/$(TARGET)

dirs:
	mkdir -p lib obj gen bin
	
clean:   
		@rm -f $(PROGRAMS) $(EVENTSO) $(EVENTLIB) *Dict.* *.def *.exp \
		   *.so *.lib *.dll *.d *.log .def so_locations  gen/*  lib/* obj/*

nice: 
	astyle -n --keep-one-line-blocks --style=gnu  ./src/*cxx ./include/*h 

doc:
	doxygen 
	



bin/$(TARGET): 
		$(CXX) $(CXXFLAGS) $(LDFLAGS) src/$(TARGET).cc -o bin/$(TARGET)

