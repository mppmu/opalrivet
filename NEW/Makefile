#do not remove intermediate
.SECONDARY:


ROOT-CONFIG   =     root-config
ARCH          =   $(shell uname -m)

 
FC                  =  $(shell  $(ROOT-CONFIG) --f77)
CXX                 =  $(shell  $(ROOT-CONFIG) --cxx)
CC                   = $(shell  $(ROOT-CONFIG) --cc)
LD                  =  $(shell  $(ROOT-CONFIG) --ld)
LDFLAGS             =  -g -O0    $(shell  $(ROOT-CONFIG) --ldflags)
SOFLAGS             =  -g -shared 




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
