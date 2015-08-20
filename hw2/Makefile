LIBS=-lgmp
CC=gcc
FLAGS=-O2

OBJ=chgbase badadd add checkadd

all: $(OBJ)

%: %.c
	$(CC) -o $@ $^ $(LIBS) $(FLAGS) 

.PHONY: clean

clean:
	rm -f $(OBJ) *~
