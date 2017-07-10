#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

struct frame {
    float *luma;
    float *chroma_u;
    float *chroma_v;
    int length;
};

frame new_frame();
frame get_reference_frame();
bool get_frame(cv::VideoCapture cap, frame f, frame ref_frame);
