STORM = i386-elf-storm
LD    = ld

STORM_FILES := $(shell find . -type f -name '*.storm')
ASM_FILES   := $(shell find . -type f -name '*.asm')
OBJ         := $(STORM_FILES:.storm=.storm.o) $(ASM_FILES:.asm=.o)

LDFLAGS = -melf_i386 -nostdlib -T./linker.ld

.PHONY: clean

kernel.bin: $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) -o $@

%.storm.o: %.storm
	$(STORM) $<

%.o: %.asm
	nasm $< -f elf32 -o $@

clean:
	rm -f $(OBJ) kernel.bin
