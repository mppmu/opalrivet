#export X509_USER_PROXY=$(pwd)/k5-ca-proxy.pem
#GEN=sherpa
#GEN=herwi$(CXX)
#GEN=pythia8
#GEN=evtgen
GEN?=pythia8
NAME=JADE_OPAL_2000_S4300807a
ARCH          =   $(shell uname -m)
CXX?=g++






YODA_VERS=1.0.6
YODA_VERS=1.3.0
YODA_VERS=1.3.1
RIVET_VERS=2.2.0
PHOTOS_VERS=3.54
TAUOLA_VERS=1.1.4
SHERPA_VERS=2.1.0
FASTJET_VERS=3.0.2
HEPMC_VERS=2.06.09
PYTHIA8_VERS=8180
THEPEG_VERS=1.9.0
HERWIG++_VERS=2.7.0

include Makefile.software

.PHONY: dirs

all: dirs mc_189	 data_189  

inputhisto:  
	mkdir -p Code/HEPDATA/irn4300807/bin/$(ARCH)
	mkdir -p Code/HEPDATA/irn4300807/src
	rm -f Code/HEPDATA/irn4300807/src/main.cxx
	echo '#include "ZROOT.h"' >  Code/HEPDATA/irn4300807/src/main.cxx
	echo 'int main(){ TFile* f_irn4300807=new TFile("Code/irn4300807.root","recreate");' >>  Code/HEPDATA/irn4300807/src/main.cxx
	number=1 ; while [[ $$number -le 90 ]] ; do \
        wget  "http://hepdata.cedar.ac.uk/view/irn4300807/d"$$number"/root" -O "Code/HEPDATA/irn4300807/"$$number".C" ; \
		sed -i -e  '1ivoid\ irn4300807_'$$number'()\n' "Code/HEPDATA/irn4300807/"$$number".C"; \
        sed -i -e  '1i#include "ZROOT.h"\n' "Code/HEPDATA/irn4300807/"$$number".C"; \
        sed -n -i -e  '/TGraph/{s|^|TGraphAsymmErrors |};p'  "Code/HEPDATA/irn4300807/"$$number".C"; \
		sed  -i -e  's/Draw(\"AP\");/Write();/g'   "Code/HEPDATA/irn4300807/"$$number".C"; \
        sed -i -e  '1ivoid\ irn4300807_'$$number'();\n' Code/HEPDATA/irn4300807/src/main.cxx; \
        echo 'irn4300807_'$$number'();' >>Code/HEPDATA/irn4300807/src/main.cxx;\
        ((number = number + 1)) ; \
    done
	echo 'f_irn4300807->Close(); return 0;}' >>  Code/HEPDATA/irn4300807/src/main.cxx	
	$(CXX)  -g -DSIMPLE_HELPERS_ONLY $(shell  root-config --ldflags --libs --cflags) -lProof -I./Code Code/HEPDATA/irn4300807/*C Code/HEPDATA/irn4300807/src/main.cxx  -o Code/HEPDATA/irn4300807/bin/$(ARCH)/main
	
#	wget  http://hepdata.cedar.ac.uk/view/irn4300807/d19/root -O Code/HEPDATA/irn4300807/19.C


toyoda:  bin/$(ARCH)/yodaconvert
		for a in $(shell find TC/2012-4-27antiktQ | grep rzhist  | grep -v '.svn' ); do \
		h2root $$a $(echo $$a| sed 's@rzhist@root@g');\
		./bin/$(ARCH)/yodaconvert  root2yoda   $$( echo $$a| sed 's@rzhist@root@g') $$( echo $$a| sed 's@rzhist@yoda@g');\
		done

dirs:
	mkdir -p ~/rpmbuild/{BUILD,RPMS,SOURCES,SPECS,SRPMS}
	mkdir -p ./bin/$(ARCH)
	mkdir -p ./obj/$(ARCH)
	mkdir -p output
	mkdir -p obj
	mkdir -p tmp
	
data_%:  bin/$(ARCH)/runProof 
	bin/$(ARCH)/runProof  DCAP_OPAL_$*

pics: bin/$(ARCH)/plots
	bin/$(ARCH)/plots 91
	bin/$(ARCH)/plots 130
	bin/$(ARCH)/plots 161		
	bin/$(ARCH)/plots 172
	bin/$(ARCH)/plots 183	
	bin/$(ARCH)/plots 189	


	
mc_%: 	
#./bin/$(ARCH)/cut_and_transform
		mkdir -p run
		
		cp share/Runpythia8.dat run		
		sed -i 's@.*Beams:eCM.*@Beams:eCM = '$(shell echo  $*+$* | bc -qi | tail -n 1)'@g' run/Runpythia8.dat

		cp share/Runpythia8_nohad.dat run		
		sed -i 's@.*Beams:eCM.*@Beams:eCM = '$(shell echo  $*+$* | bc -qi | tail -n 1)'@g' run/Runpythia8_nohad.dat


		cp share/Runsherpa.dat run
		sed -i 's@.*BEAM_ENERGY_1.*@BEAM_ENERGY_1 = '$*';@g' run/Runsherpa.dat
		sed -i 's@.*BEAM_ENERGY_2.*@BEAM_ENERGY_2 = '$*';@g' run/Runsherpa.dat

		cp share/Runherwig++.dat run
		sed -i 's@.*set LEPGenerator:EventHandler:LuminosityFunction:Energy.*@set LEPGenerator:EventHandler:LuminosityFunction:Energy '$(shell echo  $*+$* | bc -qi | tail -n 1)'@g' run/Runherwig++.dat
		
		
		cp share/Runevtgen.dat run
		
		
		cp share/Makefile.run run/Makefile
		make -C run GEN=$(GEN)
		mv run/*.root ./output


beauty:
		astyle -n --keep-one-line-blocks --style=gnu    ./*cc


convert:  dirs  bin/$(ARCH)/cut_and_transform bin/$(ARCH)/yodaconvert
		rm -rf newdata.yoda
# to have yoda files run
#	
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.root/h1860022 /REF/JADE_OPAL_2000_S4300807a/d1009-x01-y01    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.root/h1860023 /REF/JADE_OPAL_2000_S4300807a/d1009-x01-y02    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.root/h1860024 /REF/JADE_OPAL_2000_S4300807a/d1009-x01-y03    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.root/h1860025 /REF/JADE_OPAL_2000_S4300807a/d1009-x01-y04    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.root/h1860026 /REF/JADE_OPAL_2000_S4300807a/d1009-x01-y05    >> newdata.yoda




	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.root/h1860022 /REF/JADE_OPAL_2000_S4300807a/d1009-x01-y01    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.root/h1860023 /REF/JADE_OPAL_2000_S4300807a/d1009-x01-y02    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.root/h1860024 /REF/JADE_OPAL_2000_S4300807a/d1009-x01-y03    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.root/h1860025 /REF/JADE_OPAL_2000_S4300807a/d1009-x01-y04    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_9196_manip.root/h1860026 /REF/JADE_OPAL_2000_S4300807a/d1009-x01-y05    >> newdata.yoda


	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_207_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_207_manip.root/h9860022 /REF/JADE_OPAL_2000_S4300807a/d1014-x01-y01   >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_207_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_207_manip.root/h9860023 /REF/JADE_OPAL_2000_S4300807a/d1014-x01-y02    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_207_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_207_manip.root/h9860024 /REF/JADE_OPAL_2000_S4300807a/d1014-x01-y03    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_207_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_207_manip.root/h9860025 /REF/JADE_OPAL_2000_S4300807a/d1014-x01-y04    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27antiktQ/R0.7/output_200_207_manip.yoda  /TC/2012-4-27antiktQ/R0.7/output_200_207_manip.root/h9860026 /REF/JADE_OPAL_2000_S4300807a/d1014-x01-y05    >> newdata.yoda


########

	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27inclKt/output_200_9196_manip.yoda  /TC/2012-4-27inclKt/output_200_9196_manip.root/h1860022 /REF/JADE_OPAL_2000_S4300807a/d2009-x01-y01    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27inclKt/output_200_9196_manip.yoda  /TC/2012-4-27inclKt/output_200_9196_manip.root/h1860023 /REF/JADE_OPAL_2000_S4300807a/d2009-x01-y02    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27inclKt/output_200_9196_manip.yoda  /TC/2012-4-27inclKt/output_200_9196_manip.root/h1860024 /REF/JADE_OPAL_2000_S4300807a/d2009-x01-y03    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27inclKt/output_200_9196_manip.yoda  /TC/2012-4-27inclKt/output_200_9196_manip.root/h1860025 /REF/JADE_OPAL_2000_S4300807a/d2009-x01-y04    >> newdata.yoda


	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27inclKt/output_200_207_manip.yoda  /TC/2012-4-27inclKt/output_200_207_manip.root/h9860022 /REF/JADE_OPAL_2000_S4300807a/d2014-x01-y01   >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27inclKt/output_200_207_manip.yoda  /TC/2012-4-27inclKt/output_200_207_manip.root/h9860023 /REF/JADE_OPAL_2000_S4300807a/d2014-x01-y02    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27inclKt/output_200_207_manip.yoda  /TC/2012-4-27inclKt/output_200_207_manip.root/h9860024 /REF/JADE_OPAL_2000_S4300807a/d2014-x01-y03    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27inclKt/output_200_207_manip.yoda  /TC/2012-4-27inclKt/output_200_207_manip.root/h9860025 /REF/JADE_OPAL_2000_S4300807a/d2014-x01-y04    >> newdata.yoda




########

	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27kt/output_200_9196_manip.yoda  /TC/2012-4-27kt/output_200_9196_manip.root/h1860022 /REF/JADE_OPAL_2000_S4300807a/d3009-x01-y01    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27kt/output_200_9196_manip.yoda  /TC/2012-4-27kt/output_200_9196_manip.root/h1860023 /REF/JADE_OPAL_2000_S4300807a/d3009-x01-y02    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27kt/output_200_9196_manip.yoda  /TC/2012-4-27kt/output_200_9196_manip.root/h1860024 /REF/JADE_OPAL_2000_S4300807a/d3009-x01-y03    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27kt/output_200_9196_manip.yoda  /TC/2012-4-27kt/output_200_9196_manip.root/h1860025 /REF/JADE_OPAL_2000_S4300807a/d3009-x01-y04    >> newdata.yoda


	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27kt/output_200_207_manip.yoda  /TC/2012-4-27kt/output_200_207_manip.root/h9860022 /REF/JADE_OPAL_2000_S4300807a/d3014-x01-y01   >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27kt/output_200_207_manip.yoda  /TC/2012-4-27kt/output_200_207_manip.root/h9860023 /REF/JADE_OPAL_2000_S4300807a/d3014-x01-y02    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27kt/output_200_207_manip.yoda  /TC/2012-4-27kt/output_200_207_manip.root/h9860024 /REF/JADE_OPAL_2000_S4300807a/d3014-x01-y03    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27kt/output_200_207_manip.yoda  /TC/2012-4-27kt/output_200_207_manip.root/h9860025 /REF/JADE_OPAL_2000_S4300807a/d3014-x01-y04    >> newdata.yoda



########

	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_9196_manip.root/h1860022 /REF/JADE_OPAL_2000_S4300807a/d4009-x01-y01    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_9196_manip.root/h1860023 /REF/JADE_OPAL_2000_S4300807a/d4009-x01-y02    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_9196_manip.root/h1860024 /REF/JADE_OPAL_2000_S4300807a/d4009-x01-y03    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_9196_manip.root/h1860025 /REF/JADE_OPAL_2000_S4300807a/d4009-x01-y04    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_9196_manip.root/h1860026 /REF/JADE_OPAL_2000_S4300807a/d4009-x01-y05    >> newdata.yoda



	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_207_manip.root/h9860022 /REF/JADE_OPAL_2000_S4300807a/d4014-x01-y01   >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_207_manip.root/h9860023 /REF/JADE_OPAL_2000_S4300807a/d4014-x01-y02    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_207_manip.root/h9860024 /REF/JADE_OPAL_2000_S4300807a/d4014-x01-y03    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_207_manip.root/h9860025 /REF/JADE_OPAL_2000_S4300807a/d4014-x01-y04    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.4.npass2/output_200_207_manip.root/h9860026 /REF/JADE_OPAL_2000_S4300807a/d4014-x01-y05    >> newdata.yoda




	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_9196_manip.root/h1860022 /REF/JADE_OPAL_2000_S4300807a/d4109-x01-y01    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_9196_manip.root/h1860023 /REF/JADE_OPAL_2000_S4300807a/d4109-x01-y02    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_9196_manip.root/h1860024 /REF/JADE_OPAL_2000_S4300807a/d4109-x01-y03    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_9196_manip.root/h1860025 /REF/JADE_OPAL_2000_S4300807a/d4109-x01-y04    >> newdata.yoda


	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_207_manip.root/h9860022 /REF/JADE_OPAL_2000_S4300807a/d4114-x01-y01   >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_207_manip.root/h9860023 /REF/JADE_OPAL_2000_S4300807a/d4114-x01-y02    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_207_manip.root/h9860024 /REF/JADE_OPAL_2000_S4300807a/d4114-x01-y03    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.5.npass2/output_200_207_manip.root/h9860025 /REF/JADE_OPAL_2000_S4300807a/d4114-x01-y04    >> newdata.yoda



	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_9196_manip.root/h1860022 /REF/JADE_OPAL_2000_S4300807a/d4209-x01-y01    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_9196_manip.root/h1860023 /REF/JADE_OPAL_2000_S4300807a/d4209-x01-y02    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_9196_manip.root/h1860024 /REF/JADE_OPAL_2000_S4300807a/d4209-x01-y03    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_9196_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_9196_manip.root/h1860025 /REF/JADE_OPAL_2000_S4300807a/d4209-x01-y04    >> newdata.yoda


	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_207_manip.root/h9860022 /REF/JADE_OPAL_2000_S4300807a/d4214-x01-y01   >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_207_manip.root/h9860023 /REF/JADE_OPAL_2000_S4300807a/d4214-x01-y02   >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_207_manip.root/h9860024 /REF/JADE_OPAL_2000_S4300807a/d4214-x01-y03    >> newdata.yoda
	./bin/$(ARCH)/cut_and_transform yes  TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_207_manip.yoda  /TC/2012-4-27SISCone/ee_siscone_etabins0.7.npass2/output_200_207_manip.root/h9860025 /REF/JADE_OPAL_2000_S4300807a/d4214-x01-y04  >> newdata.yoda

	cat DEVRPMS/Rivet/data/refdata/JADE_OPAL_2000_S4300807a.yoda.in > DEVRPMS/Rivet/data/refdata/JADE_OPAL_2000_S4300807a.yoda
	cat newdata.yoda >> DEVRPMS/Rivet/data/refdata/JADE_OPAL_2000_S4300807a.yoda
	bin/$(ARCH)/yodaconvert yoda2root DEVRPMS/Rivet/data/refdata/JADE_OPAL_2000_S4300807a.yoda output/JADE_OPAL_2000_S4300807a.root







bin/$(ARCH)/yodaconvert: src/yodaconvert.cxx
		$(CXX) -std=c++0x src/yodaconvert.cxx -DENABLE_ROOT  $(shell yoda-config --cppflags --libs)  $(shell root-config --cflags --libs --ldflags)  -o ./bin/$(ARCH)/yodaconvert


bin/$(ARCH)/cut_and_transform: dirs  src/cut_and_transform.cxx
				$(CXX) -std=c++0x src/cut_and_transform.cxx  $(shell root-config  --cflags --libs --ldflags) $(shell yoda-config  --libs --cppflags)  -o ./bin/$(ARCH)/cut_and_transform




obj/opalrivetpythia8.o:  dirs src/opalrivetpythia8.cxx
	gcc -c src/opalrivetpythia8.cxx -o obj/opalrivetpythia8.o 
	
	
	
bin/$(ARCH)/opalrivetpythia8:  dirs obj/opalrivetpythia8.o
	gcc -lpythia8tohepmc  obj/opalrivetpythia8.o -o ./bin/$(ARCH)/opalrivetpythia8  

bin/$(ARCH)/opalrivetpythia8_nohad:  dirs obj/opalrivetpythia8.o
	gcc -lpythia8tohepmc  obj/opalrivetpythia8.o -o ./bin/$(ARCH)/opalrivetpythia8_nohad  

obj/$(ARCH)/opalrivetevtgen.o:  dirs src/opalrivetevtgen.cxx
	gcc $(shell root-config --cflags) -c src/opalrivetevtgen.cxx -o obj/$(ARCH)/opalrivetevtgen.o
		
bin/$(ARCH)/opalrivetevtgen:  dirs obj/$(ARCH)/opalrivetevtgen.o
	g++  -lEvtGenExternal $(shell  root-config --libs)  obj/$(ARCH)/opalrivetevtgen.o -o ./bin/$(ARCH)/opalrivetevtgen  

bin/$(ARCH)/prof: dirs src/pprroffessorr.cxx
		$(CXX) $(shell root-config --cflags --glibs )  -lMinuit src/pprroffessorr.cxx -o bin/$(ARCH)/prof

bin/$(ARCH)/draw: dirs  src/draw.cxx
		$(CXX) $(shell root-config --cflags --glibs )  -lMinuit draw.cxx -o bin/$(ARCH)/draw

bin/$(ARCH)/runProof: src/runProof.cxx
		mkdir -p ../bin/$(ARCH)
		$(CXX)  -g -DSIMPLE_HELPERS_ONLY $(shell  root-config --ldflags --glibs --cflags  ) -L$(shell root-config --config | sed 's@\ @\n@g' | grep "\-\-libdir=" | cut -f 2 -d=) -lProof  src/runProof.cxx  -o ./bin/$(ARCH)/runProof

bin/$(ARCH)/plots: src/plots.cxx
		mkdir -p ../bin/$(ARCH)
		$(CXX) -g -DSIMPLE_HELPERS_ONLY $(shell  root-config --ldflags --libs --cflags  ) -L$(shell root-config --config | sed 's@\ @\n@g' | grep "\-\-libdir=" | cut -f 2 -d=) -lProof -I./Code src/plots.cxx  -o ./bin/$(ARCH)/plots


