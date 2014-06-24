#do not remove intermediate
.SECONDARY:



#export ROOTSYS:=/opt/products/root64/5.28.00
#export PATH:=$$(ROOTSYS)/bin:$$(PATH)
#export LD_LIBRARY_PATH:=$$(ROOTSYS)/bin:$$(LD_LIBRARY_PATH)

ROOT-CONFIG   =     root-config
CLHEP-CONFIG  =     clhep-config
ARCH          =   $(shell uname -m)

SPECIALCFLAGS=-pthread -Wall  -pedantic -O4 
SPECIALFFLAGS=-ffixed-line-length-none -ffast-math   -pedantic -pthread 
 
EDMFLAGS=-O3 -Df2cFortran  -DUSE_DOUBLE  -DEXPLICIT_FORTRAN_PROTOTYPES -DNOBUILDINMINMAX
EDMINCPATH=-I./Minuit -I./Minuit/packlib/minuit -I./Minuit/packlib/packlib -I./Minuit/packlib/kernlib/kerngen -I./Minuit/packlib
EDMLINKLIBS=-lgfortran -lgcc_s  -L./lib/$(ARCH) -lminuit


 
FC                  =  $(shell  $(ROOT-CONFIG) --f77)
CXX                 =  $(shell  $(ROOT-CONFIG) --cxx)
CC                   = $(shell  $(ROOT-CONFIG) --cc)
LD                  =  $(shell  $(ROOT-CONFIG) --ld)
LDFLAGS             =  -g -O0    $(shell  $(ROOT-CONFIG) --ldflags)
SOFLAGS             =  -g -shared 

LDFLAGS+=-lgfortran -lgcc_s $(shell $(CLHEP-CONFIG) --libs )  $(shell $(ROOT-CONFIG) --libs) -lProofPlayer -lProof 
CXXFLAGS+=-DUSE_DOUBLE -I. -I./Code  -I./Minuit -Wextra    -Wall -I.  -Wextra  -Wall  $(shell $(CLHEP-CONFIG) --include ) $(shell $(ROOT-CONFIG) --cflags)
CPPFLAGS+=$(shell $(CLHEP-CONFIG) --include )





bin/$(ARCH)/runProof: Scripts/runProof.cxx
		mkdir -p bin/$(ARCH)
		$(CXX) $(LDFLAGS) $(CXXFLAGS)  Scripts/runProof.cxx  -o bin/$(ARCH)/runProof



beauty:
	astyle -n --keep-one-line-blocks --style=gnu  Code/*.C Code/*.h 
	astyle -n --keep-one-line-blocks --style=gnu  Scripts/*.cxx Scripts/*.h

setuptest:
	$(shell which $(ROOT-CONFIG))
	$(shell which $(CLHEP-CONFIG))
	$(shell echo $(ARCH))



.FORCE:  bin/$(ARCH)/runProof  
