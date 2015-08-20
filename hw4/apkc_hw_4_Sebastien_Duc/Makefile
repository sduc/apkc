CC=gcc
FLAGS=-O2
EXE=mod_inv chinese_reminder
OBJ=$(patsubst %,%.o,$(EXE))
OBJ+=mod_op.o
DEPS=inv_op.h

all:$(EXE)

mod_inv: mod_inv.o mod_op.o
	$(CC) $(FLAGS) -o $@ $^

chinese_reminder: chinese_reminder.o mod_op.o
	$(CC) $(FLAGS) -o $@ $^

%.o:%.c $(DEPS)
	$(CC) $(FLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -f $(OBJ) $(EXE) *~
