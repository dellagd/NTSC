#include <stdio.h>

#include <cuda.h>
#include <cuda_runtime.h>
#include <driver_functions.h>

#include "CycleTimer.h"

extern float toBW(int bytes, float sec);
extern int image_N;

float * dev_ref_luma;
float * dev_ref_chroma_u;
float * dev_ref_chroma_v;

__global__ void
ntsc_encode_frame(int N, float* luma, float* chroma_u, float* chroma_v, unsigned char* source) {
    // compute overall index from position of thread in current block,
    // and given the block we are in
    int refIndex = blockIdx.x * blockDim.x + threadIdx.x;
    int line = blockIdx.x;
    int col = threadIdx.x;

    int imageOffset = (line * 514 + col) * 4;
    float im_R = source[imageOffset] / 256.0;
    float im_G = source[imageOffset+1] / 256.0;
    float im_B = source[imageOffset+2] / 256.0;
    float im_A = source[imageOffset+3] / 256.0;

    float im_Y = im_R * .299 + im_G * .587 + im_B * .114;
    float im_U = .492 * (im_B - im_Y);
    float im_V = .877 * (im_R - im_Y);
    //if (index > 1000 & index < 1100) printf("Index: %d\n, Block: %d, Dim: %d, Thread: %d",
    //        index, blockIdx.x, blockDim.x, threadIdx.x);

    int arrIndex = 635 * line + 106 + col;
    luma[arrIndex] = (im_Y * 0.7) + 0.3;
    chroma_u[arrIndex] = im_U;
    chroma_v[arrIndex] = im_V;
}

void
ntscCuda(int N, float* luma, float* chroma_u, float* chroma_v, unsigned char* source){

    int totalBytes = sizeof(float) * N;
    int totalBytesUChar = sizeof(unsigned char) * image_N;

    // compute number of blocks and threads per block
    //const int threadsPerBlock = 512;
    //const int blocks = (N + threadsPerBlock - 1) / threadsPerBlock;
    const int blocks = ((N / 635) - 20); //242 TV Lines
    const int threadsPerBlock = 514; //514 'pixels' per line

    float* device_luma;
    float* device_chroma_u;
    float* device_chroma_v;
    unsigned char* device_source;

    // start timing
    double startTime = CycleTimer::currentSeconds();

    //
    // TODO allocate device memory buffers on the GPU using cudaMalloc
    //
    cudaMalloc(&device_luma, totalBytes);
    cudaMalloc(&device_chroma_u, totalBytes);
    cudaMalloc(&device_chroma_v, totalBytes);
    cudaMalloc(&device_source, totalBytesUChar);

    //
    // TODO copy input arrays to the GPU using cudaMemcpy
    //
    cudaMemcpy(device_luma, dev_ref_luma, totalBytes, cudaMemcpyDeviceToDevice);
    cudaMemcpy(device_chroma_u, dev_ref_chroma_u, totalBytes, cudaMemcpyDeviceToDevice);
    cudaMemcpy(device_chroma_v, dev_ref_chroma_v, totalBytes, cudaMemcpyDeviceToDevice);
    cudaMemcpy(device_source, source, totalBytesUChar, cudaMemcpyHostToDevice);

    // run kernel
    ntsc_encode_frame<<<blocks, threadsPerBlock>>>(N, device_luma, device_chroma_u, device_chroma_v, device_source);
    cudaThreadSynchronize();

    //
    // TODO copy result from GPU using cudaMemcpy
    //
    cudaMemcpy(luma, device_luma, totalBytes, cudaMemcpyDeviceToHost);
    cudaMemcpy(chroma_u, device_chroma_u, totalBytes, cudaMemcpyDeviceToHost);
    cudaMemcpy(chroma_v, device_chroma_v, totalBytes, cudaMemcpyDeviceToHost);
    //cudaMemcpy(source, source, totalBytes, cudaMemcpyDeviceToHost);

    // end timing after result has been copied back into host memory
    double endTime = CycleTimer::currentSeconds();

    cudaError_t errCode = cudaPeekAtLastError();
    if (errCode != cudaSuccess) {
        fprintf(stderr, "WARNING: A CUDA error occured: code=%d, %s\n", errCode, cudaGetErrorString(errCode));
    }

    double overallDuration = endTime - startTime;
    printf("Overall: %.3f ms\t\t[%.3f GB/s]\n", 1000.f * overallDuration, toBW(totalBytes, overallDuration));

    // TODO free memory buffers on the GPU
    cudaFree(device_luma);
    cudaFree(device_chroma_u);
    cudaFree(device_chroma_v);
    cudaFree(device_source);
}

void
load_reference_arrays(float * luma, float * chroma_u, float * chroma_v, int n){
    int totalBytes = n * sizeof(float);

    cudaMalloc(&dev_ref_luma, totalBytes);
    cudaMalloc(&dev_ref_chroma_u, totalBytes);
    cudaMalloc(&dev_ref_chroma_v, totalBytes);

    cudaMemcpy(dev_ref_luma, luma, totalBytes, cudaMemcpyHostToDevice);
    cudaMemcpy(dev_ref_chroma_u, chroma_u, totalBytes, cudaMemcpyHostToDevice);
    cudaMemcpy(dev_ref_chroma_v, chroma_v, totalBytes, cudaMemcpyHostToDevice);
}

void
clear_reference_arrays(){
    cudaFree(dev_ref_luma);
    cudaFree(dev_ref_chroma_u);
    cudaFree(dev_ref_chroma_v);
}

void
printCudaInfo() {

    // for fun, just print out some stats on the machine

    int deviceCount = 0;
    cudaError_t err = cudaGetDeviceCount(&deviceCount);

    printf("---------------------------------------------------------\n");
    printf("Found %d CUDA devices\n", deviceCount);

    for (int i=0; i<deviceCount; i++) {
        cudaDeviceProp deviceProps;
        cudaGetDeviceProperties(&deviceProps, i);
        printf("Device %d: %s\n", i, deviceProps.name);
        printf("   SMs:        %d\n", deviceProps.multiProcessorCount);
        printf("   Global mem: %.0f MB\n",
               static_cast<float>(deviceProps.totalGlobalMem) / (1024 * 1024));
        printf("   CUDA Cap:   %d.%d\n", deviceProps.major, deviceProps.minor);
    }
    printf("---------------------------------------------------------\n");
}
