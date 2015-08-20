
HW=12

all: hw$(HW).pdf 

%.pdf:%.dvi
	dvipdf $^
	mupdf $@

%.dvi:%.tex
	latex $^
	latex $^
	latex $^


clean:
	rm -f *.log *.toc *.dvi *.aux *.out 
