CC=gcc
FLAGS=-O2

OBJ=modInverse chinese

all: $(OBJ)

%: %.c
	$(CC) -o $@ $^ $(FLAGS) 

.PHONY: clean

clean:
	rm -f $(OBJ) *~
