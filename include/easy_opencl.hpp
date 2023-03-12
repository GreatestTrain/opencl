#pragma once

#include <CL/cl.h>
#include <utility>
#define CL_HPP_ENABLE_EXCEPTIONS

#include <CL/opencl.hpp>
#include <exception>
#include <iostream>
#include <vector>

class INVALID_PLATFORM_ID : std::exception
{

    const int code = 100;
    const char* message = "Invalid Platform ID";

public:
    INVALID_PLATFORM_ID() = default;

    const int err_code() { return code; }
    const char* what() { return message; }
};

class INVALID_DEVICE_ID : std::exception
{

    const int code = 101;
    const char* message = "Invalid Device ID";

public:
    INVALID_DEVICE_ID() = default;

    const int err_code() { return code; }
    const char* what() { return message; }
};

namespace easy {

    inline void get_platform_info(cl::Platform& platform, bool verbose)
    {
        cl_int err;
        std::cout << platform.getInfo(CL_PLATFORM_NAME, &err) << std::endl;
        std::cout << platform.getInfo(CL_PLATFORM_VENDOR, &err) << std::endl;
        std::cout << platform.getInfo(CL_PLATFORM_VERSION, &err) << std::endl;
        if (verbose) {
            std::cout << platform.getInfo(CL_PLATFORM_PROFILE, &err) << std::endl;
            std::cout << platform.getInfo(CL_PLATFORM_EXTENSIONS, &err) << std::endl;
        }
    }

    inline cl::Device& select_device(std::vector<cl::Platform>& platforms, size_t n_platform, std::vector<cl::Device>& devices, size_t n_device)
    {
        cl_int err;
        cl::Platform::get(&platforms);

        if (platforms.size() == 0 || platforms.size() < n_platform) throw INVALID_PLATFORM_ID();

        cl::Platform& selected_platform = platforms[n_platform];

        selected_platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

        if (devices.size() == 0 || devices.size() < n_device) throw INVALID_DEVICE_ID();

        cl::Device& selected_device = devices[n_device];
        return selected_device;
    }

}
