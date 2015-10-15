


all: 
	g++ -g -std=c++11 WriterRootTree.cc hepmcconvert.cxx -L./hepmc3-alpha5/outputs/lib -lHepMCrootIO -lHepMC   -I./hepmc3-alpha5/include  -I./hepmc3-alpha5/rootIO/include $(shell root-config --cflags --glibs) -o hepmcconvert
#	g++ -g -std=c++11   -I./hepmc3-alpha5/include $(shell root-config --cflags --glibs)  -c WriterRootTree.cc



%LinkDef.h: 
	rm -f $*LinkDef.h
	echo  "#ifdef __MAKECINT__"   >> $*LinkDef.h
	echo  "#pragma link C++ class "$*"+;"   >> $*LinkDef.h
	echo  "#endif"      >> $*LinkDef.h

%Dict.cxx:  %.h %LinkDef.h
	echo "Generating dictionary $@..."
	rootcint -f $@ -c  $*.h $*LinkDef.h


