CC = gcc
CFLAGS = -O2 -DTARGET_i386

.PHONY: clean

storm: main.o literals.o tokeniser.o lexer.o codegen.o
	$(CC) main.o literals.o tokeniser.o lexer.o codegen.o -o storm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o
