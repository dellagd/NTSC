#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

struct frame {
    float *luma;
    float *chroma_u;
    float *chroma_v;
    int length;
};

struct NTSCEncoder {
    cv::VideoCapture cap;
    float fps;
    bool success;
};

frame new_frame();
frame get_reference_frame();
NTSCEncoder new_ntscencoder(char *filename);
bool get_frame(NTSCEncoder enc, frame f, frame ref_frame);
