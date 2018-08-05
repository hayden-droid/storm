# storm

A simple retargetable programming language.
storm is currently ported to the i386 and x86_64 architectures, but it is really
simple to port it to other architectures; it can be accomplished by only modifying
2 files! (machine.h, Makefile.in)

# Build instructions

storm's build instructions are relatively standard.
If you cloned this repo, just ```cd storm``` to the storm directory and run
```./configure --help```.
Once you understand how ```./configure``` works and what options you need, proceed
to ```make install``` (as root if needed).

# That is all folks!
