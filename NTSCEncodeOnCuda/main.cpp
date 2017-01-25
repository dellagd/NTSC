#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string>
#include <cstring>
#include <iostream>

#include "lodepng.h"


#define ZLEVEL          0.3f
#define LINE_LENGTH     635

void ntscCuda(int N, float* luma, float* chroma_u, float* chroma_v, unsigned char* source);
void load_reference_arrays(float * luma, float * chroma_u, float * chroma_v, int n);
void clear_reference_arrays();

void init_frame(float* luma, float* chroma_u, float* chroma_vi, int n);
void init_img_source(unsigned char* src, int n);
void write_csv(float* arr0, float* arr1, float* arr2, int n);
void decodePNGFromFile(char * src, const char* filename);
void printCudaInfo();

int image_N = 4 * 242 * 514;


// return GB/s
float toBW(int bytes, float sec) {
  return static_cast<float>(bytes) / (1024. * 1024. * 1024.) / sec;
}


void usage(const char* progname) {
    printf("Usage: %s [options]\n", progname);
    printf("Program Options:\n");
    printf("  -n  --arraysize <INT>  Number of elements in arrays\n");
    printf("  -?  --help             This message\n");
}

int main(int argc, char** argv)
{

    int lines = 262; // 242 for lines, 9 for sync, 11 for blank
    int N = lines*LINE_LENGTH;

    // parse commandline options ////////////////////////////////////////////
    int opt;
    static struct option long_options[] = {
        {"arraysize",  1, 0, 'n'},
        {"help",       0, 0, '?'},
        {0 ,0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "?n:", long_options, NULL)) != EOF) {

        switch (opt) {
        case 'n':
            N = atoi(optarg);
            break;
        case '?':
        default:
            usage(argv[0]);
            return 1;
        }
    }


    // end parsing of commandline options //////////////////////////////////////

    unsigned char * ref_testSource = new unsigned char[image_N];
    float* ref_luma = new float[N];
    float* ref_chroma_u = new float[N];
    float* ref_chroma_v = new float[N];

    float* luma = new float[N];
    float* chroma_u = new float[N];
    float* chroma_v = new float[N];


    // load image
    init_img_source(ref_testSource, N);

    // load X, Y, store result
    init_frame(ref_luma, ref_chroma_u, ref_chroma_v, N);

    load_reference_arrays(ref_luma, ref_chroma_u, ref_chroma_v, N);

    printCudaInfo();

    for (int i=0; i<10000; i++) {
        ntscCuda(N, luma, chroma_u, chroma_v, ref_testSource);
    }

    write_csv(luma, chroma_u, chroma_v, N);

    printf("DONE\n");

    //for (int i=635*200; i<635*201; i++){
    //    printf("i: %d, luma: %.3f, u: %.3f, v: %.3f\n", i, luma[i], chroma_u[i], chroma_v[i]);
    //}

    clear_reference_arrays();

    delete [] ref_luma;
    delete [] ref_chroma_u;
    delete [] ref_chroma_v;
    delete [] ref_testSource;
    delete [] luma;
    delete [] chroma_u;
    delete [] chroma_v;

    return 0;
}

void decodePNGFromFile(unsigned char * dst, const char* filename){
    std::vector<unsigned char> image;
    unsigned width, height;

    unsigned err = lodepng::decode(image, width, height, filename);

    std::copy(image.begin(), image.end(), dst);
}

void write_csv(float* arr0, float* arr1, float* arr2, int n){
    FILE *fp;
    fp = fopen("test.csv", "w+");
    fprintf(fp, "Index, Luma, Chroma U, Chroma V\n");

    for (int i = 0; i < n; i++){
        fprintf(fp, "%d, %.3f, %.3f, %.3f\n", i, arr0[i], arr1[i], arr2[i]);
    }

    fclose(fp);
}

void init_img_source(unsigned char* source, int n){
    decodePNGFromFile(source, "maxresdefault.png");
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

