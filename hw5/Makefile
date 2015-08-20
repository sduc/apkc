
HW=5

all: hw$(HW).pdf

%.pdf:%.dvi
	dvipdf $^
	mupdf $@

%.dvi:%.tex
	latex $^
	latex $^
	latex $^
