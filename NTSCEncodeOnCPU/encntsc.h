#ifndef INCLUDED_ENCNTSC_H
#define INCLUDED_ENCNTSC_H

#include <pthread.h>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class ThreadedCaptureReader {
  private:
    pthread_t looper;
    pthread_mutex_t m;
    cv::Mat readFrame;
    cv::Mat writeFrame;
    bool just_read_frame;  

    void make();
    void getFrame();
  public:
    cv::VideoCapture vidcap;   
    bool opened;
    bool uses_cam;
    ThreadedCaptureReader (const char *);
    ThreadedCaptureReader (int);
    ~ThreadedCaptureReader ();
    void *readloop();
    bool start();
    cv::Mat readMat();

};

struct frame {
    float *luma;
    float *chroma_u;
    float *chroma_v;
    bool is_inter;
    int length;
};

struct NTSCEncoder {
    //cv::VideoCapture cap;
    ThreadedCaptureReader *tcr;
    float fps;
    bool success;
};

void free_frame(frame f);
frame new_frame(bool is_interlaced);
frame get_reference_frame(bool is_interlaced);
NTSCEncoder new_ntscencoder_file(char *filename);
NTSCEncoder new_ntscencoder_cam(size_t camera_num);
bool get_frame(NTSCEncoder enc, frame f, frame ref_frame);

#endif
