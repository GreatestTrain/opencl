#define __CL_ENABLE_EXCEPTIONS

#include <CL/opencl.hpp>

#include <vector>
#include <iostream>
// #include <err_code.h>

std::vector<cl::Platform> platforms;
std::vector<cl::Device> devices;


int main(int argc, char* argv[]) {

    try {
        // Initialize platforms and devices
        cl::Platform::get(&platforms);
        std::cout << "Nº of platforms: " << platforms.size() << std::endl;

        // analyze each platform
        for (cl::Platform &plat : platforms) {
            std::string str;
            std::cout << "================================" << std::endl;
            plat.getInfo(CL_PLATFORM_NAME, &str);
            std::cout << "Platform name: " << str << std::endl;
            plat.getInfo(CL_PLATFORM_VENDOR, &str);
            std::cout << "Platform vendor: " << str << std::endl;
            plat.getInfo(CL_PLATFORM_VERSION, &str);
            std::cout << "Platform version: " << str << std::endl;

            // analyze each device
            plat.getDevices(CL_DEVICE_TYPE_ALL, &devices);
            if (devices.size() == 0) {
                std::cout << "No devices." << std::endl;
                continue;
            }

            for (cl::Device &device : devices) {
                std::cout << "------------------------------" << std::endl;
                device.getInfo(CL_DEVICE_NAME, &str);
                std::cout << "Device name: " << str << std::endl;
                size_t size;
                device.getInfo(CL_DEVICE_LOCAL_MEM_SIZE, &size);
                std::cout << "Local mem: " << size / 1024 << " KB" << std::endl;
                device.getInfo(CL_DEVICE_GLOBAL_MEM_SIZE, &size);
                std::cout << "Global mem: " << size /1024 << " KB" << std::endl;
            }
            std::cout << "------------------------------" << std::endl;
        }
        std::cout << "================================" << std::endl;
        // get context

        // cl::Context context()
    }
    catch (cl::Error& error) {
        std::cerr << "OpenCL error:" << error.what() << std::endl;
        std::cerr << "Error Code: " << error.err() << std::endl;
    }

}
