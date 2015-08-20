
HW=6

all: hw$(HW).pdf er_sieve

%.pdf:%.dvi
	dvipdf $^
	mupdf $@

%.dvi:%.tex
	latex $^
	latex $^
	latex $^

er_sieve: er_sieve.c
	gcc -Ofast -o $@ $^ -std=c99 -mtune=native -fmodulo-sched
