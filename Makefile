NAME=JADE_OPAL_2000_S4300807a

NAME_ONE=RivetJADE_OPAL_2000_S4300807a
NAME_TWO=JADE_OPAL_2000_S4300807a

VERS=2.1.1
all: 	
		make -C run


beauty:
		astyle -n --keep-one-line-blocks --style=gnu   src/*
		
		
		
TOPDIR=./Rivet-$(VERS)
srcrpm2:
	rm -rf $(TOPDIR)
		rm -rf patch-Rivet-0.txt
	mkdir -p  $(TOPDIR)/src
	mkdir -p  $(TOPDIR)/bin
	mkdir -p  $(TOPDIR)/data
	mkdir -p  $(TOPDIR)/data/refdata
	mkdir -p  $(TOPDIR)/data/plotinfo
	mkdir -p  $(TOPDIR)/data/anainfo
	mkdir -p  $(TOPDIR)/src/Analyses
	cp bin/*     $(TOPDIR)/bin
	cp ref/Rivet$(NAME).yoda $(TOPDIR)/data/refdata/$(NAME).yoda
	sed -i 's@Rivet$(NAME)@$(NAME)@g' $(TOPDIR)/data/refdata/$(NAME).yoda

	cp ref/Rivet$(NAME).plot $(TOPDIR)/data/plotinfo/$(NAME).plot
	sed -i 's@Rivet$(NAME)@$(NAME)@g' $(TOPDIR)/data/plotinfo/$(NAME).plot

	cp ref/Rivet$(NAME).info $(TOPDIR)/data/anainfo/$(NAME).info
	sed -i 's@Rivet$(NAME)@$(NAME)@g' $(TOPDIR)/data/anainfo/$(NAME).info

	cp src/Rivet$(NAME).cc   $(TOPDIR)/src/Analyses/$(NAME).cc
	sed -i 's@Rivet$(NAME)@$(NAME)@g' $(TOPDIR)/src/Analyses/$(NAME).cc


##	cp ref/$(NAME_ONE).yoda $(TOPDIR)/data/refdata/$(NAME_TWO).yoda
##	sed -i 's@$(NAME_ONE)@$(NAME_TWO)@g' $(TOPDIR)/data/refdata/$(NAME_TWO).yoda

##	cp ref/$(NAME_ONE).plot $(TOPDIR)/data/plotinfo/$(NAME_TWO).plot
##	sed -i 's@$(NAME_ONE)@$(NAME_TWO)@g' $(TOPDIR)/data/plotinfo/$(NAME_TWO).plot

##	cp ref/$(NAME_ONE).info $(TOPDIR)/data/anainfo/$(NAME_TWO).info
##	sed -i 's@$(NAME_ONE)@$(NAME_TWO)@g' $(TOPDIR)/data/anainfo/$(NAME_TWO).info

##	cp src/$(NAME_ONE).cc   $(TOPDIR)/src/Analyses/$(NAME_TWO).cc
##	sed -i 's@$(NAME_ONE)@$(NAME_TWO)@g' $(TOPDIR)/src/Analyses/$(NAME_TWO).cc


	
	tar  czfv Rivet$(NAME).tar.gz -C ./$(TOPDIR)   .

	diff -Naur  -x   *RivetPaths.* -x *rivet.pxd*  DEVRPMS/Rivet-$(VERS)_orig  DEVRPMS/Rivet-$(VERS) > patch-Rivet-0.txt
	diff -Naur                                    DEVRPMS/Rivet-$(VERS)_orig/src/Tools/RivetPaths.cc  DEVRPMS/Rivet-$(VERS)/src/Tools/RivetPaths.cc > patch-Rivet-1.txt
	diff -Naur                                    DEVRPMS/Rivet-$(VERS)_orig/src/Tools/RivetPaths.cc  DEVRPMS/Rivet-$(VERS)/src/Tools/RivetPaths.cc >> patch-Rivet-1.txt
	diff -Naur                                    DEVRPMS/Rivet-$(VERS)_orig/include/Rivet/Tools/RivetPaths.hh  DEVRPMS/Rivet-$(VERS)/include/Rivet/Tools/RivetPaths.hh >> patch-Rivet-1.txt
	diff -Naur                                    DEVRPMS/Rivet-$(VERS)_orig//pyext/rivet/rivet.pxd  DEVRPMS/Rivet-$(VERS)/pyext/rivet/rivet.pxd >> patch-Rivet-1.txt
	sed -i 's@DEVRPMS/Rivet-$(VERS)_orig@.@g' patch-Rivet-*.txt
	sed -i 's@DEVRPMS/Rivet-$(VERS)@.@g' patch-Rivet-*.txt
	
	
srcrpm:
	rm -rf DEVRPMS/Rivet-$(VERS)
	rm -rf DEVRPMS/Rivet-$(VERS)_orig	
	tar -zxf  DEVRPMS/Rivet-$(VERS).tar.gz 
	cp -R	Rivet-$(VERS) DEVRPMS/Rivet-$(VERS)_orig
	mv 	Rivet-$(VERS) DEVRPMS/
	rm -rf patch-Rivet-*.txt
	cp -R update/* DEVRPMS/Rivet-$(VERS)/
	
#	tar  czfv Rivet$(NAME).tar.gz -C ./$(TOPDIR)   .

	diff -Naur  -x   *RivetPaths.* -x *rivet.pxd* DEVRPMS/Rivet-$(VERS)_orig  DEVRPMS/Rivet-$(VERS) > DEVRPMS/patch-Rivet-0.txt
	diff -Naur                                    DEVRPMS/Rivet-$(VERS)_orig/src/Tools/RivetPaths.cc  DEVRPMS/Rivet-$(VERS)/src/Tools/RivetPaths.cc > DEVRPMS/patch-Rivet-1.txt
	diff -Naur                                    DEVRPMS/Rivet-$(VERS)_orig/src/Tools/RivetPaths.cc  DEVRPMS/Rivet-$(VERS)/src/Tools/RivetPaths.cc >> DEVRPMS/patch-Rivet-1.txt
	diff -Naur                                    DEVRPMS/Rivet-$(VERS)_orig/include/Rivet/Tools/RivetPaths.hh  DEVRPMS/Rivet-$(VERS)/include/Rivet/Tools/RivetPaths.hh >> DEVRPMS/patch-Rivet-1.txt
	diff -Naur                                    DEVRPMS/Rivet-$(VERS)_orig//pyext/rivet/rivet.pxd  DEVRPMS/Rivet-$(VERS)/pyext/rivet/rivet.pxd >> DEVRPMS/patch-Rivet-1.txt
	sed -i 's@DEVRPMS/Rivet-$(VERS)_orig@.@g' DEVRPMS/patch-Rivet-*.txt
	sed -i 's@DEVRPMS/Rivet-$(VERS)@.@g' DEVRPMS/patch-Rivet-*.txt
		

binrpm:
		cp DEVRPMS/patch-Rivet-*.txt   /home/andriish/rpmbuild/SOURCES/
		cp DEVRPMS/Rivet-$(VERS).tar.gz  /home/andriish/rpmbuild/SOURCES/
		rpmbuild -bs DEVRPMS/Rivet.spec
		rpmbuild --rebuild /home/andriish/rpmbuild/SRPMS/Rivet-$(VERS)-1.src.rpm

	
	
	
	
#	+++ ./src/Tools/RivetPaths.cc  ./include/Rivet/Tools/RivetPaths.hh +++ ./pyext/rivet/rivet.pxd



#+++ ./bin/Makefile.in	2014-04-02 19:45:34.615468381 +0200
#+++ ./bin/rivet	1970-01-01 01:00:00.000000000 +0100
#+++ ./bin/rivet.in	2014-04-04 17:59:58.000000000 +0200
#+++ ./configure.ac	2014-04-02 20:34:06.844247667 +0200
#++ ./data/anainfo/Makefile.am	2014-04-02 22:48:52.898343587 +0200
#+##++ ./data/anainfo/Makefile.in	2014-04-02 22:48:43.708421248 +0200
#+++ ./data/plotinfo/Makefile.am	2014-04-02 20:52:14.761801385 +0200
#+++ ./data/plotinfo/Makefile.in	2014-04-02 20:51:43.714067136 +0200
#+++ ./data/refdata/Makefile.am	2014-04-02 20:50:56.291472758 +0200
#+++ ./data/refdata/Makefile.in	2014-04-02 20:50:30.883689935 +0200
#+++ ./doc/analyses.bib	2014-04-02 22:47:42.699936483 +0200
#+++ ./doc/analyses.tex	2014-04-02 22:29:04.080270104 +0200
#+++ ./include/Rivet/Projections/FastJets.hh	2014-03-28 14:53:40.000000000 +0100
#+++ ./src/Analyses/Makefile.am	2014-04-02 23:51:35.317448116 +0200
#+++ ./src/Analyses/Makefile.in	2014-04-02 20:53:47.993002494 +0200
#+++ ./src/Projections/FastJets.cc	2014-03-28 14:54:46.000000000 +0100
#+##++ ./src/Tools/RivetPaths.cc	2014-04-04 18:50:30.740139194 +0200
#+++ ./src/Tools/RivetPaths.cc	2014-04-04 18:50:30.740139194 +0200
#+++ ./include/Rivet/Tools/RivetPaths.hh	2014-04-04 18:48:47.322042473 +0200
#+++ ./pyext/rivet/rivet.pxd	2014-04-04 18:45:59.364520475 +0200



binrpm2:
		cp patch-Rivet-0.txt   /home/andriish/rpmbuild/SOURCES/
		cp Rivet$(NAME).tar.gz /home/andriish/rpmbuild/SOURCES/
		cp Rivet-$(VERS).tar.gz  /home/andriish/rpmbuild/SOURCES/
		rpmbuild -bs Rivet.spec
		rpmbuild --rebuild /home/andriish/rpmbuild/SRPMS/Rivet-$(VERS)-1.src.rpm



