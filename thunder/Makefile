.PHONY: kernel_target clean

notarget: thunder.iso

clean:
	$(MAKE) clean -C kernel

kernel_target:
	$(MAKE) -C kernel

thunder.iso: kernel_target
	mkdir -p isodir/boot/grub
	cp kernel/kernel.bin isodir/boot/kernel.bin
	cp boot/grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o thunder.iso isodir
	rm -rf isodir
