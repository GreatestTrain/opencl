kernel void matmul(
    global const float* A,
    global const float* B,
    global float* res,
    const int w
)
{
    size_t i = get_global_id(0);
    size_t j = get_global_id(1);

    size_t size_i = get_global_size(0);
    size_t size_j = get_global_size(1);

    float sum = 0.0f;
    size_t it;

    for (it = 0; it < w; it++)
    {
        // sum += A[i * w + it];
        sum += A[i * w + it] * B[it * size_j + j];
    }

    res[i * size_j + j] = sum;
    // res[-1] = size_i;

}
