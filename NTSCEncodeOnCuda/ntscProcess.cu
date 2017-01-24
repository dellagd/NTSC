#include <stdio.h>

#include <cuda.h>
#include <cuda_runtime.h>
#include <driver_functions.h>

#include "CycleTimer.h"

extern float toBW(int bytes, float sec);

__global__ void
ntsc_encode_frame(int N, float* luma, float* chroma_u, float* chroma_v, float* source) {

    // compute overall index from position of thread in current block,
    // and given the block we are in
    int refIndex = blockIdx.x * blockDim.x + threadIdx.x;
    int pixel = blockIdx.x;
    int line = threadIdx.x;
    //if (index > 1000 & index < 1100) printf("Index: %d\n, Block: %d, Dim: %d, Thread: %d",
    //        index, blockIdx.x, blockDim.x, threadIdx.x);

    int arrIndex = 635 * line + 106 + pixel;
    luma[arrIndex] = source[arrIndex];
    chroma_u[arrIndex] = (source[arrIndex] * 2 - 256) / 512.0f;
    chroma_v[arrIndex] = (source[arrIndex] * 1.5 - 256) / 512.0f;
}

void
ntscCuda(int N, float* luma, float* chroma_u, float* chroma_v, float* source) {

    int totalBytes = sizeof(float) * N;

    // compute number of blocks and threads per block
    //const int threadsPerBlock = 512;
    //const int blocks = (N + threadsPerBlock - 1) / threadsPerBlock;
    const int threadsPerBlock = ((N / 635) - 20); //242 TV Lines
    const int blocks = 514; //514 'pixels' per line

    float* device_luma;
    float* device_chroma_u;
    float* device_chroma_v;
    float* device_source;

    //
    // TODO allocate device memory buffers on the GPU using cudaMalloc
    //
    cudaMalloc(&device_luma, totalBytes);
    cudaMalloc(&device_chroma_u, totalBytes);
    cudaMalloc(&device_chroma_v, totalBytes);
    cudaMalloc(&device_source, totalBytes);

    // start timing after allocation of device memory
    double startTime = CycleTimer::currentSeconds();

    //
    // TODO copy input arrays to the GPU using cudaMemcpy
    //
    cudaMemcpy(device_luma, luma, totalBytes, cudaMemcpyHostToDevice);
    cudaMemcpy(device_chroma_u, chroma_u, totalBytes, cudaMemcpyHostToDevice);
    cudaMemcpy(device_chroma_v, chroma_v, totalBytes, cudaMemcpyHostToDevice);
    cudaMemcpy(device_source, source, totalBytes, cudaMemcpyHostToDevice);

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
