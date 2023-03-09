#include <CL/opencl.hpp>

#include <vector>
#include <iostream>

int main(int argc, char* argv[]) {

    // Initialize platforms and devices
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);

    std::vector<cl::Device> devices;
    platforms[0].getDevices(&devices);


}
