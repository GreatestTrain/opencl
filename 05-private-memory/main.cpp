#define CL_TARGET_OPEN_CL_VERSION 200

#include <CL/opencl.hpp>
#include <vector>
#include <easy_opencl.hpp>
#include <file_tools.hpp>
#include <math.h>

std::vector<cl::Platform> platforms;
std::vector<cl::Device> devices;

int main(int argc, char* argv[])
{
    cl::Device& device = easy::select_device(platforms, 0, devices, 0);

    cl_int err;
    cl::Context context(device, NULL, NULL, &err);
    std::string kernel_str = get_file_contents(argv[1]);
    cl::Program program(context, kernel_str);
    program.build(device);

    cl::CommandQueue queue(context, device);

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

    cl::Buffer bufferA(context, CL_MEM_READ_ONLY, sizeof(float) * sizeA);
    cl::Buffer bufferB(context, CL_MEM_READ_ONLY, sizeof(float) * sizeB);
    cl::Buffer bufferC(context, CL_MEM_WRITE_ONLY, sizeof(float) * sizeC);

    cl::Kernel kernel(program, "matmul");
    kernel.setArg(0, bufferA);
    kernel.setArg(1, bufferB);
    kernel.setArg(2, bufferC);
    kernel.setArg(3, dimsA[1]);

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

    return 0;
}
