/* -*- c++ -*- */
/* 
 * Copyright 2017 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "encoder_impl.h"

namespace gr {
  namespace ntsc {

    encoder::sptr
    encoder::make(const char * videofile, int decim, bool use_webcam)
    {
      return gnuradio::get_initial_sptr
        (new encoder_impl(videofile, decim, use_webcam));
    }

    /*
     * The private constructor
     */
    encoder_impl::encoder_impl(const char * videofile, int decim, bool use_webcam)
      : gr::sync_block("encoder",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(3, 3, sizeof(float))),
      p_filepath(videofile), p_decim(decim), p_use_webcam(use_webcam)
    {
      if(!p_use_webcam)
        p_enc = new_ntscencoder_file(const_cast<char*>(p_filepath));
      else
        p_enc = new_ntscencoder_cam(0);


      bool interlaced;
      if (p_enc.fps > 29 && p_enc.fps < 31) {
        interlaced = true;
      } else if (p_enc.fps > 59 && p_enc.fps < 61) {
        interlaced = false;
      } else {
        printf("WARNING: Source has %.2f FPS video, which will "
               "not be transmitted at the correct speed. Use video "
               "of ~30 or ~60 FPS for this block to properly encode it."
               "\n", p_enc.fps);
      }

      p_ref_frame = get_reference_frame(interlaced);
      p_vid_frame = new_frame(interlaced);
      p_repeat = 0;
      
      p_frame_length = p_ref_frame.length/p_decim;
      set_output_multiple(p_frame_length);
    }

    /*
     * Our virtual destructor.
     */
    encoder_impl::~encoder_impl()
    {
      free_frame(p_ref_frame);
      free_frame(p_vid_frame);
    }

    int
    encoder_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      float **out = (float**) &output_items[0]; 
      
      //Send frame twice because not interlacing
      //if (p_repeat == 0 || p_enc.fps > 35) { 
        get_frame(p_enc, p_vid_frame, p_ref_frame);
      //  p_repeat = 1;
      //} else {
      //  p_repeat--;
      //}
      
      //printf("noutput_items = %d\n", noutput_items);
      if (p_decim == 1) {
        memcpy(out[0], p_vid_frame.luma, sizeof(float[noutput_items])); 
        memcpy(out[1], p_vid_frame.chroma_u, sizeof(float[noutput_items])); 
        memcpy(out[2], p_vid_frame.chroma_v, sizeof(float[noutput_items])); 
      } else {
        for (int i = 0; i < noutput_items; i++) {
          out[0][i] = p_vid_frame.luma[i*p_decim];
          out[1][i] = p_vid_frame.chroma_u[i*p_decim];
          out[2][i] = p_vid_frame.chroma_v[i*p_decim];
        }
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace ntsc */
} /* namespace gr */

