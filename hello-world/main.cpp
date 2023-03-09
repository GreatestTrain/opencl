#define _USE_MATH_DEFINES
#define CL_HPP_TARGET_OPENCL_VERSION 200

#include <CL/opencl.hpp>
#include <iostream>
#include <vector>
#define DATA_SIZE 30

std::vector<cl::Platform> platforms;
std::vector<cl::Device> devices;

cl::Platform& get_platforms() {
    cl::Platform::get(&platforms);
    return platforms[0];
}

std::vector<cl::Device>& get_devices() {
    platforms[0].getDevices(CL_DEVICE_TYPE_ALL, &devices);
    return devices;
}

int main() {

    // declaring vectors
    std::vector<float> data(DATA_SIZE);
    for (int i = 0; i < DATA_SIZE; i++)
    {
        data.push_back(float(i * CL_M_PI));
    }
    std::vector<float> output(int(data.size()));
    std::cout << "Vector size: " << data.size() << "|" << output.size() << std::endl;

    get_platforms();
    get_devices();

    // get context
    cl::Context context(devices);
    cl::CommandQueue queue(context, devices[0]);

    cl::Buffer inputBuff(context, CL_MEM_READ_ONLY, sizeof(float) * data.size());
    cl::Buffer outputBuff(context, CL_MEM_WRITE_ONLY, sizeof(float) * data.size());

    queue.enqueueWriteBuffer(inputBuff, CL_TRUE, 0, sizeof(float) * data.size(), data.data());

    const char* kernel_str =
        "kernel void calcSin(global const float* input, global float* output) {\n"
        "   int id = get_global_id(0);\n"
        "   output[id] = sin(input[id]);\n"
        "}\n";
    
    cl::Program program(context, kernel_str);
    // Building
    auto err = program.build(devices);
    cl::Kernel kernel(program, "calcSin");
    
    kernel.setArg(0, inputBuff);
    kernel.setArg(1, outputBuff);
    
    // Execute kernel
    cl::NDRange global_work_size(data.size());
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, global_work_size, cl::NullRange);

    // Read results
    queue.enqueueReadBuffer(outputBuff, CL_TRUE, 0, sizeof(float) * output.size(), output.data());
    queue.finish();

    for (int i = 0; i < data.size(); i++) {
        std::cout << data[i] << " -> " << output[i] << std::endl;
    }

    return 0;
}





