#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/griffin/Documents/gr-ntsc/python
export PATH=/home/griffin/Documents/gr-ntsc/build/python:$PATH
export LD_LIBRARY_PATH=/home/griffin/Documents/gr-ntsc/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=/home/griffin/Documents/gr-ntsc/build/swig:$PYTHONPATH
/usr/bin/python2 /home/griffin/Documents/gr-ntsc/python/qa_encoder.py 
