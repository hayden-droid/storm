#!/bin/sh

set -ex

make distclean && ./configure --target=i386 && make && sudo make install && ( cd ../thunder/ && make clean && make && make run )
