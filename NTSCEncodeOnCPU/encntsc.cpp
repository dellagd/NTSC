#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

#include "encntsc.h"

#define ZLEVEL                        0.3f
#define LINE_LENGTH                   635
#define LINES_PER_FRAME_NONINTER      262
#define LINES_PER_FRAME_INTER         525
#define VIS_LINES_PER_FRAME_NONINTER  (LINES_PER_FRAME_NONINTER - 20)
#define VIS_LINES_PER_FRAME_INTER     (LINES_PER_FRAME_INTER - 39)
#define FRAME_LENGTH_NONINTER         (LINE_LENGTH * LINES_PER_FRAME_NONINTER)
#define FRAME_LENGTH_INTER            (LINE_LENGTH * LINES_PER_FRAME_INTER)

using namespace cv;
    
void fill_with_frame_noninter(float *luma, float *chroma_u, float *chroma_v, Mat frame){
    for (int row = 0; row < VIS_LINES_PER_FRAME_NONINTER; row++){
        for (int col = 0; col < 526; col++){
            Vec3b p = frame.at<Vec3b>(row, col);
            float im_B = ((float)p.val[0]) / 255.0f;
            float im_G = ((float)p.val[1]) / 255.0f;
            float im_R = ((float)p.val[2]) / 255.0f;
            
            float im_Y = im_R * .299 + im_G * .587 + im_B * .114;
            float im_U = .492 * (im_B - im_Y);
            float im_V = .877 * (im_R - im_Y);

            int arrIndex = 635 * row + 94 + col;
            luma[arrIndex] = (im_Y * 0.7) + 0.3;
            chroma_u[arrIndex] = im_U;
            chroma_v[arrIndex] = im_V;
        }
    }
}

void fill_with_frame_inter(float *luma, float *chroma_u, float *chroma_v, Mat frame){
    for (int row = 0; row < VIS_LINES_PER_FRAME_INTER; row++){
        for (int col = 0; col < 526; col++){
            Vec3b p = frame.at<Vec3b>(row, col);
            float im_B = ((float)p.val[0]) / 255.0f;
            float im_G = ((float)p.val[1]) / 255.0f;
            float im_R = ((float)p.val[2]) / 255.0f;
            
            float im_Y = im_R * .299 + im_G * .587 + im_B * .114;
            float im_U = .492 * (im_B - im_Y);
            float im_V = .877 * (im_R - im_Y);

            int arr_index = 0;
            if (row%2==0)
              arr_index = LINE_LENGTH * (row/2) + 94 + col;
            else
              arr_index = LINE_LENGTH * (((row-1)/2)+263) + 94 + col;
            
            luma[arr_index] = (im_Y * 0.7) + 0.3;
            chroma_u[arr_index] = im_U;
            chroma_v[arr_index] = im_V;
        }
    }
}

void init_frame_inter(float* luma, float* chroma_u, float* chroma_v){
    //Initialize Luma Array
    for (int i = 0; i < 244*LINE_LENGTH; i += LINE_LENGTH){
        //Last overwritten by V-Sync half
        for (int j = i; j < i+LINE_LENGTH; j++){
            if (j-i>=0 && j-i<47) luma[j] = 0.0f;
            else if ((j-i>=47 && j-i<47+47) || (j-i>=LINE_LENGTH-15 && j-i<LINE_LENGTH)) luma[j] = ZLEVEL;
            else luma[j] = 0.42f; //Random, will be overwritten
        }
    }

    for (int i = 263*LINE_LENGTH; i < 506*LINE_LENGTH; i += LINE_LENGTH){
        for (int j = i; j < i+LINE_LENGTH; j++){
            if (j-i>=0 && j-i<47) luma[j] = 0.0f;
            else if ((j-i>=47 && j-i<47+47) || (j-i>=LINE_LENGTH-15 && j-i<LINE_LENGTH)) luma[j] = ZLEVEL;
            else luma[j] = 0.42f; //Random, will be overwritten
        }
    }

    // Initialize Vertical Sync (After First Field)
    for (int i = 243*LINE_LENGTH; i < 244*LINE_LENGTH; i += LINE_LENGTH){
        for (int j = i; j < i+LINE_LENGTH; j++){
            if ((j-i>=25+292 && j-i<25+292+25)) luma[j] = 0.0f;
            else if (j-i>=25+292+25 || (j-i>=47+47 && j-i<25+292)) luma[j] = ZLEVEL;
        }
    }
        
    for (int i = 244*LINE_LENGTH; i < 246*LINE_LENGTH; i += LINE_LENGTH){
        for (int j = i; j < i+LINE_LENGTH; j++){
            if ((j-i>=0 && j-i<25) || (j-i>=25+292 && j-i<25+292+25)) luma[j] = 0.0f;
            else luma[j] = ZLEVEL;
        }
    }

    for (int i = 246*LINE_LENGTH; i < 247*LINE_LENGTH; i += LINE_LENGTH){
        for (int j = i; j < i+LINE_LENGTH; j++){
            if ((j-i>=0 && j-i<25) || (j-i>=25+292 && j-i<LINE_LENGTH-45)) luma[j] = 0.0f;
            else luma[j] = ZLEVEL;
        }
    }
        
    for (int i = 247*LINE_LENGTH; i < 249*LINE_LENGTH; i += LINE_LENGTH){
        for (int j = i; j < i+LINE_LENGTH; j++){
            if ((j-i>=0 && j-i<272) || (j-i>=272+45 && j-i<272+45+273)) luma[j] = 0.0f;
            else luma[j] = ZLEVEL;
        }
    }
    
    for (int i = 249*LINE_LENGTH; i < 250*LINE_LENGTH; i += LINE_LENGTH){
        for (int j = i; j < i+LINE_LENGTH; j++){
            if ((j-i>=0 && j-i<272) || (j-i>=272+45 && j-i<25+292+25)) luma[j] = 0.0f;
            else luma[j] = ZLEVEL;
        }
    }

    for (int i = 250*LINE_LENGTH; i < 252*LINE_LENGTH; i += LINE_LENGTH){
        for (int j = i; j < i+LINE_LENGTH; j++){
            if ((j-i>=0 && j-i<25) || (j-i>=25+292 && j-i<25+292+25)) luma[j] = 0.0f;
            else luma[j] = ZLEVEL;
        }
    }

    for (int i = 252*LINE_LENGTH; i < 253*LINE_LENGTH; i += LINE_LENGTH){
        for (int j = i; j < i+LINE_LENGTH; j++){
            if ((j-i>=0 && j-i<25)) luma[j] = 0.0f;
            else luma[j] = ZLEVEL;
        }
    }

    for (int i = 253*LINE_LENGTH; i < 263*LINE_LENGTH; i += LINE_LENGTH){
        for (int j = i; j < i+LINE_LENGTH; j++){
            if (j-i>=0 && j-i<47) luma[j] = 0.0f;
            else luma[j] = ZLEVEL;
        }
    }

    //Initialize Vertical Sync (After Second Field)
    for (int i = 506*LINE_LENGTH; i < 509*LINE_LENGTH; i += LINE_LENGTH){
        for (int j = i; j < i+LINE_LENGTH; j++){
            if ((j-i>=0 && j-i<25) || (j-i>=25+292 && j-i<25+292+25)) luma[j] = 0.0f;
            else luma[j] = ZLEVEL;
        }
    }

    for (int i = 509*LINE_LENGTH; i < 512*LINE_LENGTH; i += LINE_LENGTH){
        for (int j = i; j < i+LINE_LENGTH; j++){
            if ((j-i>=0 && j-i<272) || (j-i>=272+45 && j-i<272+45+273)) luma[j] = 0.0f;
            else luma[j] = ZLEVEL;

        }
    }

    for (int i = 512*LINE_LENGTH; i < 515*LINE_LENGTH; i += LINE_LENGTH){
        for (int j = i; j < i+LINE_LENGTH; j++){
            if ((j-i>=0 && j-i<25) || (j-i>=25+292 && j-i<25+292+25)) luma[j] = 0.0f;
            else luma[j] = ZLEVEL;
        }
    }

    for (int i = 515*LINE_LENGTH; i < 525*LINE_LENGTH; i += LINE_LENGTH){
        for (int j = i; j < i+LINE_LENGTH; j++){
            if (j-i>=0 && j-i<47) luma[j] = 0.0f;
            else luma[j] = ZLEVEL;
        }
    }

    //Initialize Chroma Arrays
    for (int i = 0; i < 244*LINE_LENGTH; i += LINE_LENGTH){
        for (int j = i; j < i+LINE_LENGTH; j++){
            if (j-i>=53 && j-i<53+25) chroma_u[j] = -0.3f;
            else chroma_u[j] = 0.0f;

            chroma_v[j] = 0.0f;
        }
    }

    for (int i = 263*LINE_LENGTH; i < 506*LINE_LENGTH; i += LINE_LENGTH){
        for (int j = i; j < i+LINE_LENGTH; j++){
            if (j-i>=53 && j-i<53+25) chroma_u[j] = -0.3f;
            else chroma_u[j] = 0.0f;

            chroma_v[j] = 0.0f;
        }
    }

    for (int i = 244*LINE_LENGTH; i < 263*LINE_LENGTH; i++){
        chroma_u[i] = 0.0f;
        chroma_v[i] = 0.0f;
    }
    
    for (int i = 506*LINE_LENGTH; i < 525*LINE_LENGTH; i++){
        chroma_u[i] = 0.0f;
        chroma_v[i] = 0.0f;
    }
}

void init_frame_noninter(float* luma, float* chroma_u, float* chroma_v){
    //Initialize Luma Array
    for (int i = 0; i < 242*LINE_LENGTH; i += LINE_LENGTH){
        for (int j = i; j < i+LINE_LENGTH; j++){
            if (j-i>=0 && j-i<47) luma[j] = 0.0f;
            else if ((j-i>=47 && j-i<47+47) || (j-i>=LINE_LENGTH-15 && j-i<LINE_LENGTH)) luma[j] = ZLEVEL;
            else luma[j] = 0.42f; //Random, will be overwritten
        }
    }

    for (int i = 242*LINE_LENGTH; i < 245*LINE_LENGTH; i += LINE_LENGTH){
        for (int j = i; j < i+LINE_LENGTH; j++){
            if ((j-i>=0 && j-i<25) || (j-i>=25+292 && j-i<25+292+25)) luma[j] = 0.0f;
            else luma[j] = ZLEVEL;
        }
    }

    for (int i = 245*LINE_LENGTH; i < 248*LINE_LENGTH; i += LINE_LENGTH){
        for (int j = i; j < i+LINE_LENGTH; j++){
            if ((j-i>=0 && j-i<272) || (j-i>=272+45 && j-i<272+45+273)) luma[j] = 0.0f;
            else luma[j] = ZLEVEL;

        }
    }

    for (int i = 248*LINE_LENGTH; i < 251*LINE_LENGTH; i += LINE_LENGTH){
        for (int j = i; j < i+LINE_LENGTH; j++){
            if ((j-i>=0 && j-i<25) || (j-i>=25+292 && j-i<25+292+25)) luma[j] = 0.0f;
            else luma[j] = ZLEVEL;
        }
    }

    for (int i = 251*LINE_LENGTH; i < 262*LINE_LENGTH; i += LINE_LENGTH){
        for (int j = i; j < i+LINE_LENGTH; j++){
            if (j-i>=0 && j-i<47) luma[j] = 0.0f;
            else luma[j] = ZLEVEL;
        }
    }

    //Initialize Chroma Arrays
    for (int i = 0; i < 242*LINE_LENGTH; i += LINE_LENGTH){
        for (int j = i; j < i+LINE_LENGTH; j++){
            if (j-i>=53 && j-i<53+25) chroma_u[j] = -0.3f;
            else chroma_u[j] = 0.0f;

            chroma_v[j] = 0.0f;
        }
    }

    for (int i = 242*LINE_LENGTH; i < 262*LINE_LENGTH; i++){
        chroma_u[i] = 0.0f;
        chroma_v[i] = 0.0f;
    }
}

void free_frame(frame f){
    free(f.luma);
    free(f.chroma_u);
    free(f.chroma_v);
}

frame new_frame(bool is_interlaced){
    frame f;

    int l;
    if (is_interlaced) l = FRAME_LENGTH_INTER;
    else l = FRAME_LENGTH_NONINTER;

    f.luma = (float*)calloc(l, sizeof(float)); 
    f.chroma_u = (float*)calloc(l, sizeof(float)); 
    f.chroma_v = (float*)calloc(l, sizeof(float));

    f.is_inter = is_interlaced;
    f.length = l;

    return f;
}

frame get_reference_frame(bool is_interlaced){
    frame f = new_frame(is_interlaced);
    if (f.is_inter) init_frame_inter(f.luma, f.chroma_u, f.chroma_v);
    else init_frame_noninter(f.luma, f.chroma_u, f.chroma_v);

    return f;
}

bool get_frame(NTSCEncoder enc, frame out, frame ref){
    if (out.is_inter != ref.is_inter){
      printf("ERROR: Input frames are not of same interlacing style "
             "(e.g. one noninterlaced, one interlaced). Cannot Proceed "
             "correctly!\n");
      return true;
    }
  
    Mat rawframe = enc.tcr->readMat();
    
    Mat resized;
    if (ref.is_inter) resize(rawframe, resized, Size(526, VIS_LINES_PER_FRAME_INTER));
    else resize(rawframe, resized, Size(526, VIS_LINES_PER_FRAME_NONINTER));

    putText(resized, "KB3ZKL TV", 
        cvPoint((int)(resized.cols*0.55), (int)(resized.rows*0.9)), 
        FONT_HERSHEY_SIMPLEX, 1.1, cvScalar(250, 250, 250), 3, CV_AA);

#ifdef SHOW_IMAGE
    imshow("window", resized);
#endif

    memcpy(out.luma, ref.luma, ref.length*sizeof(float));
    memcpy(out.chroma_u, ref.chroma_u, ref.length*sizeof(float));
    memcpy(out.chroma_v, ref.chroma_v, ref.length*sizeof(float));
    
    if (ref.is_inter) fill_with_frame_inter(out.luma, out.chroma_u, out.chroma_v, resized);
    else fill_with_frame_noninter(out.luma, out.chroma_u, out.chroma_v, resized);

    return true;    
}

NTSCEncoder new_ntscencoder_file(char *filename){
    NTSCEncoder ret;
    
    ret.tcr = new ThreadedCaptureReader(filename);
    ret.success = ret.tcr->opened;
    ret.fps = ret.tcr->vidcap.get(CAP_PROP_FPS);
    
    return ret;
}

NTSCEncoder new_ntscencoder_cam(size_t camera_num){
    NTSCEncoder ret;
    
    ret.tcr = new ThreadedCaptureReader((int)camera_num);
    ret.success = ret.tcr->opened;
    ret.fps = ret.tcr->vidcap.get(CAP_PROP_FPS);
    
    return ret;
}


static void * readloopEntry(void * self){
  return static_cast<ThreadedCaptureReader*>(self)->readloop();
}

ThreadedCaptureReader::ThreadedCaptureReader(const char *filepath){
  uses_cam = false;
  opened = vidcap.open(filepath); 

  make();
}

ThreadedCaptureReader::ThreadedCaptureReader(int cam_num){
  uses_cam = true;
  opened = vidcap.open(cam_num); 
  
  make();
}

ThreadedCaptureReader::~ThreadedCaptureReader(){
  readFrame.release();
  writeFrame.release();
}
   
void ThreadedCaptureReader::make(){
  pthread_mutex_init( &m, NULL);
  just_read_frame = false;

  if (!opened){
    printf("!!! Failed to open capture\n");
    return;  
  }

  getFrame();

  start();
  printf("Started capture thread!\n");
}

bool ThreadedCaptureReader::start(){
  pthread_create( &looper, NULL, &readloopEntry, this);
}

void ThreadedCaptureReader::getFrame(){
  if (!vidcap.read(writeFrame))
    return;
  
  pthread_mutex_lock(&m);
  writeFrame.copyTo(readFrame);
  pthread_mutex_unlock(&m);
}

void *ThreadedCaptureReader::readloop(){
  int x = 0;
  for(;;){
    if (uses_cam) {
      getFrame();
    } else if (just_read_frame){
      getFrame();
      just_read_frame = false;
    } else {
      usleep(1000);
    }
  }
}

Mat ThreadedCaptureReader::readMat(){
  Mat ret;
  
  pthread_mutex_lock(&m);
  readFrame.copyTo(ret);
  pthread_mutex_unlock(&m);

  just_read_frame = true;
  return ret;
}
