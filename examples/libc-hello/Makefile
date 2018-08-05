STORM = x86_64-elf-storm
CC = cc

.PHONY: all clean

all:
	$(STORM) libc-hello.storm # compile
	$(CC) libc-hello.storm.o -o libc-hello -static # link

clean:
	rm -f libc-hello.storm.o libc-hello
