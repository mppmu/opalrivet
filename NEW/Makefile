#do not remove intermediate
.SECONDARY:


ROOT-CONFIG   =     root-config
ARCH          =   $(shell uname -m)

 
FC                  =  $(shell  $(ROOT-CONFIG) --f77)
CXX                 =  $(shell  $(ROOT-CONFIG) --cxx)
CC                   = $(shell  $(ROOT-CONFIG) --cc)
LD                  =  $(shell  $(ROOT-CONFIG) --ld)
CXXFLAGS                   = $(shell  $(ROOT-CONFIG) --cflags)
LDFLAGS             =  -g -O0    $(shell  $(ROOT-CONFIG) --ldflags --libs) -lProof
SOFLAGS             =  -g -shared 

../output/OPAL_%: ../bin/$(ARCH)/runProof
	../bin/$(ARCH)/runProof  DCAP_OPAL_$*




#all_%: 	
#		mkdir -p run
#		cp Runpythia8.dat run		
#		sed -i 's@.*Beams:eCM.*@Beams:eCM = '$(shell echo  $*+$* | bc -qi | tail -n 1)'@g' run/Runpythia8.dat

#		cp Runsherpa.dat run
#		sed -i 's@.*BEAM_ENERGY_1.*@BEAM_ENERGY_1 = '$*';@g' run/Runsherpa.dat


../bin/$(ARCH)/runProof: Scripts/runProof.cxx
		mkdir -p ../bin/$(ARCH)
		$(CXX) $(LDFLAGS) $(CXXFLAGS)  Scripts/runProof.cxx  -o ../bin/$(ARCH)/runProof



beauty:
	astyle -n --keep-one-line-blocks --style=gnu  Code/*.C Code/*.h 
	astyle -n --keep-one-line-blocks --style=gnu  Scripts/*.cxx Scripts/*.h

setuptest:
	$(shell which $(ROOT-CONFIG))
	$(shell which $(CLHEP-CONFIG))
	$(shell echo $(ARCH))



.FORCE:  bin/$(ARCH)/runProof  
