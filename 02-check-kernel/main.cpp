#include <CL/cl.h>
#include <cstdlib>
#include <string>
#define __CL_ENABLE_EXCEPTIONS

#include <CL/opencl.hpp>

#include <vector>
#include <iostream>
#include <math.h>

char* kernel_str =
    "__global kernel void sumVectors(__global const float* vecA, __global const float* vecB"
    "   id = get_global_id(0);\n"
    "   res[id] = vecA[id] + vecB[id];\n"
    "}\n";


std::vector<cl::Platform> platforms;
std::vector<cl::Device> devices;


int main(int argc, char* argv[]) {


    int count = int(std::stoi(argv[0]));
    std::vector<float> vecA;
    std::vector<float> vecB(vecA.size());

    for (int i = 0; i != count; i++) {
        vecA.push_back((float)(rand() % 100));
        vecB.push_back((float)(rand() % 100));
    }

    std::vector<float> output(vecA.size());

    // Initialize platform and devices
    cl::Platform::get(&platforms);
    platforms[0].getDevices(CL_DEVICE_TYPE_ALL, &devices);

    cl::Device& device = devices.front();

    // Initialize context
    cl::Context context(devices);

    // Initialize Program - Build it
    cl::Program program(context, kernel_str);
    program.build(devices);

    // Initialize buffers
    cl::Buffer vecA_buffer(context, CL_MEM_READ_ONLY, sizeof(float) * vecA.size());
    cl::Buffer vecB_buffer(context, CL_MEM_READ_ONLY, sizeof(float) * vecB.size());
    cl::Buffer output_buffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * output.size());

    // Initialize kernel
    cl::Kernel kernel(program, "sumVectors");
    kernel.setArg(0, vecA_buffer);
    kernel.setArg(1, vecB_buffer);
    kernel.setArg(2, output_buffer);

    // Initialize queue
    cl::CommandQueue queue(context, devices[0]);

    // Initialize range
    cl::NDRange range((size_t)vecA.size());

    queue.enqueueWriteBuffer(vecA_buffer, CL_FALSE, 0, sizeof(float) * vecA.size(), vecA.data());
    queue.enqueueWriteBuffer(vecB_buffer, CL_FALSE, 0, sizeof(float) * vecB.size(), vecB.data());
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, range, cl::NullRange);
    queue.enqueueReadBuffer(output_buffer, CL_FALSE, 0, sizeof(float) * output.size(),
output.data());

    for (float& element : output) {
        std::cout << element << std::endl;
    }

}
