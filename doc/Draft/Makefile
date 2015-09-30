latexfile=opalJRT
newname=JRT
TEX=  latex -halt-on-error -shell-escape -enable-write18
PDFTEX= pdflatex -halt-on-error -shell-escape -enable-write18
BIB= bibtex
KPSEWHICH=kpsewhich

all: $(latexfile).pdf


figures_tikz: $(latexfile)-dia.tex
	$(TEX)  -interaction=batchmode -jobname    $(latexfile)"-dia-figure0" "\def\tikzexternalrealjob{"$(latexfile)"-dia}\input{"$(latexfile)"-dia}"
	dvips   $(latexfile)"-dia-figure0.dvi" -o $(latexfile)"-dia-figure0.eps"
	ps2eps -f   $(latexfile)"-dia-figure0.ps"
	$(PDFTEX)  -interaction=batchmode -jobname    $(latexfile)"-dia-figure0" "\def\tikzexternalrealjob{"$(latexfile)"-dia}\input{"$(latexfile)"-dia}"
	mv $(latexfile)"-dia-figure0.eps" Figures/$(newname)-figure0.eps
	mv $(latexfile)"-dia-figure0.pdf" Figures/$(newname)-figure0.pdf
	rm $(latexfile)"-dia-figure0".*
	
	$(TEX)  -interaction=batchmode -jobname    $(latexfile)"-dia-figure1" "\def\tikzexternalrealjob{"$(latexfile)"-dia}\input{"$(latexfile)"-dia}"
	dvips   $(latexfile)"-dia-figure1.dvi" -o $(latexfile)"-dia-figure1.eps"
	ps2eps -f   $(latexfile)"-dia-figure1.ps"
	$(PDFTEX)  -interaction=batchmode -jobname    $(latexfile)"-dia-figure1" "\def\tikzexternalrealjob{"$(latexfile)"-dia}\input{"$(latexfile)"-dia}"
	mv $(latexfile)"-dia-figure1.eps" Figures/$(newname)-figure1.eps
	mv $(latexfile)"-dia-figure1.pdf" Figures/$(newname)-figure1.pdf
	rm $(latexfile)"-dia-figure1".*

tar:  Makefile $(figures) $(constanttables) $(tables) $(latexfile).bst $(latexfile).bib $(latexfile)-txt.tex $(latexfile)-tab.tex $(latexfile)-fig.tex $(latexfile)-auth.tex  $(latexfile).tex zeus_paper.cls
	rm -rf TAR
	mkdir -p TAR
	cp Makefile $(figures) $(constanttables) $(tables) $(latexfile).bst $(latexfile).bib $(latexfile)-txt.tex $(latexfile)-tab.tex $(latexfile)-fig.tex $(latexfile)-auth.tex  $(latexfile).tex zeus_paper.cls TAR	
	sed -i 's@ConstantTables/@./@g'  TAR/*tex
	sed -i 's@ConstantTables/@./@g'  TAR/Makefile
	sed -i 's@Tables/@./@g'  TAR/*tex
	sed -i 's@Tables/@./@g' TAR/Makefile
	sed -i 's@Figures/@./@g' TAR/*tex
	sed -i 's@Figures/@./@g' TAR/Makefile	
	sed -i 's@'$(latexfile)'@'$(newname)'@g' TAR/*tex	
	sed -i 's@'$(latexfile)'@'$(newname)'@g' TAR/*bst
	sed -i 's@'$(latexfile)'@'$(newname)'@g' TAR/Makefile
	sed -i 's@\\usepackage{lineno}@@g'	 TAR/*tex	
	sed -i 's@\\linenumbers@@g'	 TAR/*tex	
	sed -i 's@\\documentclass.*@\\documentclass[zpreprint,zbstnp,final]{zeus_paper}@g' TAR/*tex	
	sed -i '/@artic/achecked={2},' TAR/*bib	
	sed -i '/@inproceed/achecked={2},' TAR/*bib	
	sed -i '/@phdthesis/achecked={2},' TAR/*bib	
	mv TAR/$(latexfile).bst TAR/$(newname).bst 
	mv TAR/$(latexfile).bib TAR/$(newname).bib 
	mv TAR/$(latexfile).tex TAR/$(newname).tex
	mv TAR/$(latexfile)-txt.tex TAR/$(newname)-txt.tex
	mv TAR/$(latexfile)-tab.tex TAR/$(newname)-tab.tex
	mv TAR/$(latexfile)-fig.tex $(latexfile)-auth.tex TAR/$(newname)-fig.tex
#####-->A trick to get bib file
	$(MAKE) -C TAR
	mv TAR/$(newname).bbl  TAR/$(newname).bbl.temp
	$(MAKE) -C TAR clean
	mv TAR/$(newname).bbl.temp  TAR/$(newname).bbl
#####<--A trick to get bib file
	tar -zcvf   $(newname).tar.gz -C TAR . 
	rm -rf TAR


figures=
tables=
constanttables=



$(latexfile).dvi :  $(figures) $(constanttables) $(tables) $(latexfile).bst $(latexfile).bib $(latexfile)-txt.tex $(latexfile)-tab.tex $(latexfile)-fig.tex $(latexfile)-auth.tex  $(latexfile).tex zeus_paper.cls
	$(TEX) $(latexfile)
	$(TEX) $(latexfile)
	$(BIB) $(latexfile)
	$(BIB) $(latexfile)
	$(TEX) $(latexfile)
	$(TEX) $(latexfile)

$(latexfile).pdf : $(latexfile).ps
	ps2pdf -dUseCIEColor -dPDFSETTINGS=/printer -sPAPERSIZE=a4  $(latexfile).ps $(latexfile).pdf

ps : $(latexfile).ps 

pdf : $(latexfile).pdf
$(latexfile).ps : $(latexfile).dvi
	dvips -Ppdf -t a4 $(latexfile)


$(latexfile).rws: $(latexfile)-dict.txt
	aspell --lang=en create master ./$(latexfile).rws < ./$(latexfile)-dict.txt

spell: $(latexfile).rws
		for a in $$(ls -1 $(latexfile)-*.tex); do\
		echo "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" ;\
		echo $a;\
		echo "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" ;\
		aspell  --add-extra-dicts=./$(latexfile).rws  -t --dont-tex-check-comments -d en_GB -c $$a ;\
		done

clean :
	rm -f $(latexfile)-papers.tex
	rm -f *.aux
	rm -f *.lof
	rm -f *.out
	rm -f *.lot
	rm -f *.bbl
	rm -f *.l4l
	rm -f *.log
	rm -f *.blg
	rm -f *.ilg
	rm -f *.aux
	rm -f *.dvi
	rm -f *.ps
	rm -f *.toc
	rm -f *.idx
	rm -f *.ind
	rm -f *.nav
	rm -f *.snm


	
