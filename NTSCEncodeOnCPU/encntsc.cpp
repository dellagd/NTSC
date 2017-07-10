#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

#include "encntsc.h"

#define ZLEVEL          0.3f
#define LINE_LENGTH     635
#define LINES_PER_FRAME 262
#define FRAME_LENGTH    (LINE_LENGTH * LINES_PER_FRAME)

using namespace cv;
    
int lines = 262; // 242 for lines, 9 for sync, 11 for blank
int N = FRAME_LENGTH;

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
        for (int col = 0; col < 526; col++){
            Vec3b p = frame.at<Vec3b>(row, col);
            float im_B = ((float)p.val[0]) / 255;
            float im_G = ((float)p.val[1]) / 255;
            float im_R = ((float)p.val[2]) / 255;
            
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
        resize(frame, resized, Size(526, 242));

        memcpy(luma, ref_lum, N*sizeof(float));
        memcpy(chroma_u, ref_cu, N*sizeof(float));
        memcpy(chroma_v, ref_cv, N*sizeof(float));
        fill_with_frame(luma, chroma_u, chroma_v, resized);

        imshow("window", resized);
        
        char key = cvWaitKey(10);
        if (key == 27) // ESC
            break;
        
        //printf("Microseconds: %d\n", getusec());

        ttill(t1, usec_per_frame);
    }
}

void free_frame(frame f){
    free(f.luma);
    free(f.chroma_u);
    free(f.chroma_v);
}

frame new_frame(){
    frame f;
    f.luma = (float*)calloc(FRAME_LENGTH, sizeof(float)); 
    f.chroma_u = (float*)calloc(FRAME_LENGTH, sizeof(float)); 
    f.chroma_v = (float*)calloc(FRAME_LENGTH, sizeof(float));

    f.length = FRAME_LENGTH;

    return f;
}

frame get_reference_frame(){
    frame f = new_frame();
    init_frame(f.luma, f.chroma_u, f.chroma_v, FRAME_LENGTH);

    return f;
}

bool get_frame(VideoCapture cap, frame out, frame ref){
    Mat rawframe;

    if (!cap.read(rawframe))
        return false;

    Mat resized;
    resize(rawframe, resized, Size(526, 242));
    imshow("window", resized);

    memcpy(out.luma, ref.luma, N*sizeof(float));
    memcpy(out.chroma_u, ref.chroma_u, N*sizeof(float));
    memcpy(out.chroma_v, ref.chroma_v, N*sizeof(float));
    
    fill_with_frame(out.luma, out.chroma_u, out.chroma_v, resized);

    return true;    
}

void init_frame(float* luma, float* chroma_u, float* chroma_v, int n){
    //Initialize Luma Array
    for (int i = 0; i < 242*LINE_LENGTH; i += LINE_LENGTH){
        for (int j = i; j < i+LINE_LENGTH; j++){
            if (j-i>=0 && j-i<47) luma[j] = 0.0f;
            else if ((j-i>=47 && j-i<47+47) || (j-i>=635-15 && j-i<635)) luma[j] = ZLEVEL;
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

void write_frame_to_file(frame f){
    FILE *of;
    of = fopen("frame.csv", "w");

    for(int i = 0; i < f.length; i++){
        fprintf(of, "%0.2f,\n", f.luma[i]);
    }

    fclose(of);
}

int main(int argc, char* argv[])
{ 
    VideoCapture cap(argv[1]);
    if (!cap.isOpened())
    {
        std::cout << "!!! Failed to open file: " << argv[1] << std::endl;
        return -1;
    }

    //begin_proc(cap); 
    
    frame f = new_frame();
    frame ref_frame = get_reference_frame();
    
    double usec_per_frame = 1000000.0/cap.get(CAP_PROP_FPS);
    long int t1;
    for(;;){
        t1 = getusec();
        
        if (!get_frame(cap, f, ref_frame))
            break;

        write_frame_to_file(f);
        
        char key = cvWaitKey(10);
        if (key == 27) // ESC
            break;
        
        ttill(t1, usec_per_frame);
    }

    return 0;
}

    
