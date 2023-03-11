#define _USE_MATH_DEFINES
# define CL_HPP_TARGET_OPENCL_VERSION 200
#include <CL/opencl.hpp>
#include <cmath>
#include <iostream>
#include <vector>

int main()
{
    const int VECTOR_SIZE = 100;
    std::vector<float> input(VECTOR_SIZE);
    std::vector<float> output(VECTOR_SIZE);

    // Initialize input vector with random values between 0 and 2*Pi
    for (int i = 0; i < VECTOR_SIZE; i++) {
        input[i] = static_cast<float>(rand()) / RAND_MAX * 2 * M_PI;
    }

    // Get available OpenCL platforms
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);

    // Get available OpenCL devices
    std::vector<cl::Device> devices;
    platforms[0].getDevices(CL_DEVICE_TYPE_GPU, &devices);

    // Create OpenCL context and command queue
    cl::Context context(devices);
    cl::CommandQueue queue(context, devices[0]);

    // Create OpenCL buffers for input and output vectors
    cl::Buffer input_buffer(context, CL_MEM_READ_ONLY, sizeof(float) * VECTOR_SIZE);
    cl::Buffer output_buffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * VECTOR_SIZE);

    // Copy input vector to input buffer
    queue.enqueueWriteBuffer(input_buffer, CL_TRUE, 0, sizeof(float) * VECTOR_SIZE, input.data());

    // Create OpenCL program from source code
    const char* source_code = "__kernel void sin_kernel(__global const float* input, __global float* output)\n"
        "{\n"
        "    int i = get_global_id(0);\n"
        "    output[i] = sin(input[i]);\n"
        "}";

    // cl::Program::Sources sources(, std::make_pair(source_code, strlen(source_code)));
    // cl::Program::Sources sources(kernel_str);
    cl::Program program(context, source_code);

    // Compile OpenCL program for device
    program.build(devices);

    // Create OpenCL kernel from program
    cl::Kernel kernel(program, "sin_kernel");

    // Set kernel arguments
    kernel.setArg(0, input_buffer);
    kernel.setArg(1, output_buffer);

    // Enqueue kernel for execution
    cl::NDRange global_work_size(VECTOR_SIZE);
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, global_work_size, cl::NullRange);

    // Copy output vector from output buffer
    queue.enqueueReadBuffer(output_buffer, CL_TRUE, 0, sizeof(float) * VECTOR_SIZE, output.data());

    
    // Print resultskernel.setArg(0, memBuf);
    for (int i = 0; i < VECTOR_SIZE; i++) {
        std::cout << "sin(" << input[i] << ") = " << output[i] << std::endl;
    }

    return 0;
}
