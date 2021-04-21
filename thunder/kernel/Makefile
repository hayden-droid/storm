STORM = x86_64-elf-storm
LD    = ld

STORM_FILES := $(shell find . -type f -name '*.storm')
ASM_FILES   := $(shell find . -type f -name '*.asm')
OBJ         := $(STORM_FILES:.storm=.storm.o) $(ASM_FILES:.asm=.o)

LDFLAGS = -nostdlib -Tlinker.ld -pie -static -z max-page-size=0x1000

.PHONY: clean

kernel.elf: $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) -o $@

%.storm.o: %.storm
	$(STORM) $<

%.o: %.asm
	nasm $< -f elf64 -o $@

clean:
	rm -f $(OBJ) kernel.elf
