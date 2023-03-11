#define CL_HPP_ENABLE_EXCEPTIONS

#include <CL/opencl.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <exception>
#include <math.h>
#include <streambuf>
#include <math.h>

#include <file_tools.hpp>

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

    // write buffers
    unsigned int dimsA[2] = {3, 2};
    unsigned int dimsB[2] = {2, 4};
    unsigned int dimsC[2] = {dimsA[0], dimsB[1]};

    unsigned int sizeA = dimsA[0] * dimsA[1];
    unsigned int sizeB = dimsB[0] * dimsB[1];
    unsigned int sizeC = dimsA[0] * dimsB[1];

    std::vector<float> vecA(sizeA);
    std::vector<float> vecB(sizeB);
    std::vector<float> vecC(sizeC);

    get_matrix<float>(argv[2], vecA);
    get_matrix<float>(argv[3], vecB);

    std::cout << "Printin A matrix: " << std::endl << "=========" << std::endl;
    for (int i = 0; i != dimsA[0]; i++) {
      for (int j = 0; j != dimsA[1]; j++) {
        std::cout << vecA[j + i * dimsA[1]] << " ";
      }
      std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Printing B matrix: " << std::endl << "=========" << std::endl;
    for (int i = 0; i != dimsB[0]; i++) {
      for (int j = 0; j != dimsB[1]; j++) {
        std::cout << vecB[j + i * dimsB[1]] << " ";
      }
      std::cout << std::endl;
    }

    // Initialize buffers
    cl::Buffer bufferA(context, CL_MEM_READ_ONLY, sizeof(float) * sizeA);
    cl::Buffer bufferB(context, CL_MEM_READ_ONLY, sizeof(float) * sizeB);
    cl::Buffer bufferC(context, CL_MEM_WRITE_ONLY, sizeof(float) * sizeC);


    cl::Kernel kernel(program, "matmul");
    kernel.setArg(0, bufferA);
    kernel.setArg(1, bufferB);
    kernel.setArg(2, bufferC);
    kernel.setArg(3, dimsA[1]);

    cl::CommandQueue queue(context);
    cl::NDRange global(dimsC[0], dimsC[1]);

    queue.enqueueWriteBuffer(bufferA, CL_FALSE, 0, sizeof(float) * sizeA, vecA.data());
    queue.enqueueWriteBuffer(bufferB, CL_FALSE, 0, sizeof(float) * sizeB, vecB.data());

    queue.enqueueNDRangeKernel(kernel, cl::NullRange, global, cl::NullRange);
    queue.enqueueReadBuffer(bufferC, CL_FALSE, 0, sizeof(float) * sizeC, vecC.data());
    queue.finish();

    std::cout << std::endl;
    std::cout << "Printing C matrix: " << std::endl << "=========" << std::endl;
    for (int i = 0; i != dimsC[0]; i++) {
      for (int j = 0; j != dimsC[1]; j++) {
        std::cout << round(vecC[j + i * dimsC[1]] / 0.001) * 0.001 << "\t";
      }
      std::cout << std::endl;
    }

}

