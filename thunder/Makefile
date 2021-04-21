.PHONY: all
all: thunder.hdd

thunder.hdd: kernel dir2fat32-esp limine
	mkdir -p pack
	cp kernel/kernel.elf limine.cfg limine/limine.sys pack/
	mkdir -p pack/EFI/BOOT
	cp limine/BOOTX64.EFI pack/EFI/BOOT/
	./dir2fat32-esp -f thunder.hdd 64 pack
	limine/limine-install thunder.hdd

.PHONY: kernel
kernel:
	$(MAKE) -C kernel

.PHONY: clean
clean:
	$(MAKE) clean -C kernel

.PHONY: distclean
distclean: clean
	rm -rf dir2fat32-esp limine

dir2fat32-esp:
	wget https://github.com/mintsuki-org/dir2fat32-esp/raw/master/dir2fat32-esp
	chmod +x dir2fat32-esp

limine:
	git clone https://github.com/limine-bootloader/limine.git --branch=v2.0-branch-binary --depth=1
	make -C limine

.PHONY: run
run:
	qemu-system-x86_64 -net none -hda thunder.hdd
