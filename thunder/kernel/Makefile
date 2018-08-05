STORM = i386-elf-storm
LD = i386-elf-ld

STORM_FILES = $(shell find src -type f -name '*.storm')
ASM_FILES = $(shell find asm -type f -name '*.asm') $(shell find startup -type f -name '*.asm')
OBJ = $(STORM_FILES:.storm=.storm.o) $(ASM_FILES:.asm=.o)

LDFLAGS = -nostdlib \
    -T ./linker.ld

.PHONY: clean

kernel.bin: $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) -o $@

%.storm.o: %.storm
	$(STORM) $<

%.o: %.asm
	nasm $< -f elf32 -o $@

clean:
	rm -f $(OBJ) kernel.bin
