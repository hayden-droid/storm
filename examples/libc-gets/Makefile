STORM = x86_64-elf-storm
CC = cc

.PHONY: all clean

all:
	$(STORM) libc-gets.storm # compile
	$(CC) libc-gets.storm.o -o libc-gets -static # link

clean:
	rm -f libc-gets.storm.o libc-gets
