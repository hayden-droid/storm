#!/bin/sh

set -ex

make distclean && ./configure --target=x86_64 && make && sudo make install install-highlighting && ( cd ../thunder/ && make clean && make && make run )
