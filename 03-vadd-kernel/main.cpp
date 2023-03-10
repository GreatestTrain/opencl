#include <cstdio>
#include <cstdlib>
#include <sstream>
#define CL_HPP_ENABLE_EXCEPTIONS

#include <CL/opencl.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <exception>
#include <math.h>
#include <streambuf>

std::string get_file_contents(char *filepath) {
    std::ifstream t(filepath);
    std::stringstream strStream;

    strStream << t.rdbuf();
    return strStream.str();

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
    std::string kernel_str = get_file_contents(argv[1]);

    // Initialize and build program
    cl::Program program(context, kernel_str.c_str());
    // cl::Program::Sources sources();
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
      element = (float)(0.01 + rand() / 100.0f);
    }
    for (float& element : vecB) {
      element = (float)(0.03 + rand() / 100.0f);
    }


    cl::Kernel kernel(program, "vadd");
    int new_size = 3;
    kernel.setArg(0, bufferA);
    kernel.setArg(1, bufferB);
    kernel.setArg(2, bufferC);
    kernel.setArg(3, new_size);

    // TODO Initialize queue
    cl::CommandQueue queue(context);
    // TODO Execute queue
    cl::NDRange range = size;
    queue.enqueueWriteBuffer(bufferA, CL_FALSE, 0, sizeof(float) * size, vecA.data());
    queue.enqueueWriteBuffer(bufferB, CL_FALSE, 0, sizeof(float) * size, vecB.data());
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, range, cl::NullRange);
    queue.enqueueReadBuffer(bufferC, CL_FALSE, 0, sizeof(float) * size, vecC.data());

    queue.finish();

    for (int i = 0; i != size; i++) {
      std::cout << vecA[i] << " + " << vecB[i] << " = " << vecC[i] << std::endl;
    }
}

