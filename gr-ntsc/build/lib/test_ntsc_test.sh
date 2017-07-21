#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/griffin/NTSC/gr-ntsc/lib
export PATH=/home/griffin/NTSC/gr-ntsc/build/lib:$PATH
export LD_LIBRARY_PATH=/home/griffin/NTSC/gr-ntsc/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$PYTHONPATH
test-ntsc 
