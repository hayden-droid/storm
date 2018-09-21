STORM = x86_64-elf-storm
CC = cc

.PHONY: all clean

all:
	$(STORM) libc-break.storm # compile
	$(CC) libc-break.storm.o -o libc-break -static # link

clean:
	rm -f libc-break.storm.o libc-break
