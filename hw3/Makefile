
HW=3

all: hw$(HW).pdf

%.pdf:%.dvi
	dvipdf $^

%.dvi:%.tex
	latex $^
	latex $^
	latex $^
