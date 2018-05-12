STORM = ../../src/storm
LD = i386-elf-ld

STORM_FILES = $(shell find src -type f -name '*.storm')
ASM_FILES = $(shell find asm -type f -name '*.asm') $(shell find startup -type f -name '*.asm')
OBJ = $(STORM_FILES:.storm=.o) $(ASM_FILES:.asm=.o)

LDFLAGS = -nostdlib \
    -T ./linker.ld

.PHONY: storm clean

kernel.bin: storm $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) -o $@

%.o: %.storm
	$(STORM) $< $(@:.o=.s)
	nasm $(@:.o=.s) -f elf32 -o $@

%.o: %.asm
	nasm $< -f elf32 -o $@

storm:
	cd ../../src && make clean && make

clean:
	rm -f $(OBJ) $(STORM_FILES:.storm=.s) kernel.bin
