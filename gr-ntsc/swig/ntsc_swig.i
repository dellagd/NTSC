/* -*- c++ -*- */

#define NTSC_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "ntsc_swig_doc.i"

%{
#include "ntsc/encoder.h"
%}


%include "ntsc/encoder.h"
GR_SWIG_BLOCK_MAGIC2(ntsc, encoder);
