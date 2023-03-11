#define CL_HPP_ENABLE_EXCEPTIONS

#include <CL/opencl.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <exception>
#include <math.h>
#include <streambuf>

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

    int size = 10;

    // write buffers
    unsigned int dimsA[2] = {3, 2};
    unsigned int dimsB[2] = {2, 4};

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



}

