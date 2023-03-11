kernel void matmul(
    global const float* A,
    global const float* B,
    unsigned int w,
    global float* res,
)
{
    int i = get_global_id(0);
    int j = get_global_id(1);

    float sum = 0;

    int it = 0;
    for (it = 0; it != w; it++)
    {
        sum += A[i + j * it] * B[i * it + j];
    }

    res[i * it + j] = sum;
}
