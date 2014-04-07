NAME=JADE_OPAL_2000_S4300807a
all: plots

src/Rivet$(NAME).cc: ../update/src/Analyses/JADE_OPAL_2000_S4300807a.cc
		cp ../update/src/Analyses/JADE_OPAL_2000_S4300807a.cc ./src/Rivet$(NAME).cc


lib/Rivet$(NAME).so:  src/Rivet$(NAME).cc Run.dat 
## -DUSE_DURHAM -DUSE_ANTIKT -DUSE_CONE -DUSE_JADE  -DUSE_ANTIKT_R_SCAN  -DUSE_CA
###		-DUSE_DURHAM -DUSE_JADE -DUSE_CONE -DUSE_PX -DUSE_CONE 
		rivet-buildplugin --with-root  lib/Rivet$(NAME).so src/Rivet$(NAME).cc -pedantic -Wall -DUSE_DURHAM -DUSE_JADE 



Rivet.yoda: lib/Rivet$(NAME).so ref/$(NAME).yoda
		rm -f fifo.hepmc.hepmc2g
		mkfifo fifo.hepmc.hepmc2g
		Sherpa EVENT_OUTPUT=HepMC_GenEvent[fifo.hepmc]   & 		
		./run-rivet.sh $(NAME)
		rm Sherpa_References.tex fifo.hepmc.hepmc2g
		
ref/$(NAME).yoda ref/$(NAME).plot ref/$(NAME).info: ../update/data/refdata/JADE_OPAL_2000_S4300807a.yoda ../update/data/plotinfo/JADE_OPAL_2000_S4300807a.plot ../update/data/anainfo/JADE_OPAL_2000_S4300807a.info
		mkdir -p ref
		cp ../update/data/refdata/JADE_OPAL_2000_S4300807a.yoda  ref/$(NAME).yoda
		cp ../update/data/plotinfo/JADE_OPAL_2000_S4300807a.plot  ref/$(NAME).plot
		cp ../update/data/anainfo/JADE_OPAL_2000_S4300807a.info  ref/$(NAME).info
		
plots: Rivet.yoda ref/$(NAME).yoda ref/$(NAME).plot ref/$(NAME).info
		rm -rf out/Rivet$(NAME)/*-*.dat
		mkdir -p out src lib ref 
		./run-mkhtml.sh $(NAME)
