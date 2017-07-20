#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

#include "encntsc.h"

long int getusec(){
    struct timeval starttime;
    gettimeofday(&starttime, NULL);
    return (starttime.tv_sec*1000000+starttime.tv_usec);
}

void ttill(long int start, int wait){
    int offset = 0;
#ifdef DEBUG 
    printf("Waiting %.2f ms\n", ((double)(start+wait-getusec()))/1000);
#endif
    for(;;){
        //printf("Hit!\n");
        long int curr = getusec() + offset;
        if (curr+5000000 < start){
            //Rollover occured
            offset = -60000000;
        }
        if (start+wait+offset < curr) break;
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
    NTSCEncoder enc = new_ntscencoder(argv[1]);
#ifdef DEBUG
    printf("Loaded video from file %s running at %.2f FPS\n", argv[1], enc.fps);
#endif

    frame f = new_frame();
    frame ref_frame = get_reference_frame();
    
    double usec_per_frame = 1000000.0/enc.fps;
    long int t1;
    for(;;){
        t1 = getusec();
        
        if (!get_frame(enc, f, ref_frame))
            break;

#ifdef WRITE_CSV
        write_frame_to_file(f);
#endif

#ifdef SHOW_IMAGE 
        char key = cvWaitKey(1);
        if (key == 27) // ESC
            break;
#endif
        
        ttill(t1, usec_per_frame);
    }

    return 0;
}

