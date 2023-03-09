#include <cstdio>
#include <cstdlib>
#define CL_HPP_ENABLE_EXCEPTIONS

#include <CL/opencl.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <exception>
#include <math.h>

std::string get_file_contents(char* filepath) {
    std::string buffer;
    std::ifstream file;
    file.open(filepath);
    if ( file.is_open() && file.good() ) {
      file >> buffer;
    }
    return buffer;
}

int main(int argc, char *argv[])
{
    // Initialize platforms
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);

    // Initialize devices
    std::vector<cl::Device> devices;
    platforms.front().getDevices(CL_DEVICE_TYPE_ALL,&devices);

    // Initialize context
    cl::Context context(devices);

    // Read kernel_str
    char* filepath = (char*)"vadd.cl";
    std::string kernel_str = get_file_contents(filepath);

    // Initialize and build program
    cl::Program program(context, devices, kernel_str);
    program.build(devices);

    int size = 10;

    // TODO -> Initalize buffers
    // Initialize buffers
    cl::Buffer bufferA(context, CL_MEM_READ_ONLY, sizeof(float) * size);
    cl::Buffer bufferB(context, CL_MEM_READ_ONLY, sizeof(float) * size);
    cl::Buffer bufferC(context, CL_MEM_WRITE_ONLY, sizeof(float) * size);

    // write buffers
    //

    std::vector<float> vecA(size);
    std::vector<float> vecB(size);
    std::vector<float> vecC(size);

    for (float& element : vecA) {
      element = (float)(0.01 + rand() / RAND_MAX);
    }
    for (float& element : vecB) {
      element = (float)(0.01 + rand() / RAND_MAX);
    }


    cl::Kernel kernel(program, "vadd");
    kernel.setArg(0, bufferA);
    kernel.setArg(1, bufferB);
    kernel.setArg(2, bufferC);
    kernel.setArg(3, size);

    // TODO Initialize queue
    cl::CommandQueue queue(context);
    // TODO Execute queue
    cl::NDRange range = size;
    queue.enqueueWriteBuffer(bufferA, CL_FALSE, 0, sizeof(float) * size, vecA.data());
    queue.enqueueWriteBuffer(bufferB, CL_FALSE, 0, sizeof(float) * size, vecB.data());
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, range, cl::NullRange);
    queue.enqueueReadBuffer(bufferC, CL_FALSE, 0, sizeof(float) * size, vecC.data());

    queue.finish();

    for (float& element : vecC) {
      std::cout << element << std::endl;
    }

}

