#include <CL/opencl.hpp>
#include <iostream>

cl_device_id device;
cl_context context;
cl_command_queue queue;

cl_program program;
cl_kernel kernel;

cl_mem buffer;

void initialize() {
    // Setup OpenCL - as many C libraries, OpenCL needs initialization
    // cl_device_id device;
    clGetDeviceIDs(NULL, CL_DEVICE_TYPE_CPU, 1, &device, NULL);
    context = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);
    queue = clCreateCommandQueue(context, device, (cl_command_queue_properties)0, NULL);
}

// kernel -> calculates the Sin
char* source = {
    "kernel void calcSin(global float *data) {\n"
    "   int id = get_global_id(0);\n"
    "   data[id] = sin(data[id]);\n"
    "}\n"
};

void createProgram() {
    // Compile Kernel - (char* source)
    program = clCreateProgramWithSource(context, 1, (const char**)&source, NULL, NULL);
    clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
    kernel = clCreateKernel(program, "calcSin", NULL);

}

void createBuffer() {
    // create memory buffer - allocate memory on global memory of device (gpu)
    buffer = clCreateBuffer(context, CL_MEM_READ_WRITE, DATA_SIZE, NULL, NULL);
     // copy data to input (buffer)
    clEnqueueWriteBuffer(queue, buffer, CL_FALSE, 0, DATA_SIZE, data, 0, NULL, NULL);

}

int main() {
    initialize();
    createProgram();

    
    cl_mem buffer = clCreateBuffer(context, CL_MEM_READ_WRITE, DATA_SIZE, NULL, NULL);

   
    clEnqueueWriteBuffer(queue, buffer, CL_FALSE, 0, DATA_SIZE, data, 0, NULL, NULL);

    // Execute kernel
    clSetKernelArg(kernel, 0, sizeof(buffer), &buffer);
    size_t global_dimensions[] = {LENGTH, 0, 0};
    clEnqueueNDRangeKernel(queue, kernel, 1, NULL, global_dimensions, NULL, 0, NULL, NULL);

    // Read the output
    clEnqueueReadBuffer(queue, kernel, CL_FALSE, 0, sizeof(cl_float)*LENGTH, data, 0, NULL, NULL);

    // wait for queue to finish

    //Finish queue
    clFinish(queue);
}





