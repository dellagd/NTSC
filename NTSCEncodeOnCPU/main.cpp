#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>

#define ZLEVEL          0.3f
#define LINE_LENGTH     635

using namespace cv;
    
int lines = 262; // 242 for lines, 9 for sync, 11 for blank
int N = lines*LINE_LENGTH;

void init_frame(float* luma, float* chroma_u, float* chroma_vi, int n);

long int getusec(){
    struct timeval starttime;
    gettimeofday(&starttime, NULL);
    return (starttime.tv_sec*1000000+starttime.tv_usec);
}

void ttill(long int start, int wait){
    int offset = 0;
    for(;;){
        long int curr = getusec() + offset;
        if (curr+5000000 < start){
            //Rollover occured
            offset = -60000000;
        }
        if (start+wait+offset < curr) break;
    }
}

void fill_with_frame(float *luma, float *chroma_u, float *chroma_v, Mat frame){
    for (int row = 0; row < 242; row++){
        for (int col = 0; col < 514; col++){
            Vec3b p = frame.at<Vec3b>(row, col);
            uchar im_B = p.val[0];
            uchar im_G = p.val[1];
            uchar im_R = p.val[2];
            
            float im_Y = im_R * .299 + im_G * .587 + im_B * .114;
            float im_U = .492 * (im_B - im_Y);
            float im_V = .877 * (im_R - im_Y);

            int arrIndex = 635 * row + 106 + col;
            luma[arrIndex] = (im_Y * 0.7) + 0.3;
            chroma_u[arrIndex] = im_U;
            chroma_v[arrIndex] = im_V;
        }
    }
}

void begin_proc(VideoCapture cap){
    Mat frame;
    float* ref_lum = new float[N];
    float* ref_cu = new float[N];
    float* ref_cv = new float[N];
    float* luma = new float[N];
    float* chroma_u = new float[N];
    float* chroma_v = new float[N];

    // load X, Y, store result
    init_frame(ref_lum, ref_cu, ref_cv, N);
    
    printf("FPS of video: %f\n", cap.get(CAP_PROP_FPS));
    double usec_per_frame = 1000000.0/cap.get(CAP_PROP_FPS);
    printf("Frame period in ms: %f\n", usec_per_frame);

    long int t1;
    for(;;)
    {
        t1 = getusec();        

        if (!cap.read(frame))             
            break;

        Mat resized;
        resize(frame, resized, Size(514, 242));

        memcmp(ref_lum, luma, N*sizeof(float));
        memcmp(ref_cu, chroma_u, N*sizeof(float));
        memcmp(ref_cv, chroma_v, N*sizeof(float));
        fill_with_frame(luma, chroma_u, chroma_v, resized);

        imshow("window", resized);
        
        char key = cvWaitKey(10);
        if (key == 27) // ESC
            break;
        
        //printf("Microseconds: %d\n", getusec());

        ttill(t1, usec_per_frame);
    }
}

int main(int argc, char* argv[])
{ 
    VideoCapture cap(argv[1]);
    if (!cap.isOpened())
    {
        std::cout << "!!! Failed to open file: " << argv[1] << std::endl;
        return -1;
    }


    begin_proc(cap);    

    return 0;
}

void init_frame(float* luma, float* chroma_u, float* chroma_v, int n){
    //Initialize Luma Array
    for (int i = 0; i < 242*LINE_LENGTH; i += LINE_LENGTH){
        for (int j = i; j < i+LINE_LENGTH; j++){
            if (j-i>=0 && j-i<47) luma[j] = 0.0f;
            else if ((j-i>=47 && j-i<47+59) || (j-i>=635-15 && j-i<635)) luma[j] = ZLEVEL;
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
            if (j-i>=64 && j-i<64+25) chroma_u[j] = -0.3f;
            else chroma_u[j] = 0.0f;

            chroma_v[j] = 0.0f;
        }
    }

    for (int i = 242*LINE_LENGTH; i < 262*LINE_LENGTH; i++){
        chroma_u[i] = 0.0f;
        chroma_v[i] = 0.0f;
    }
}

    
