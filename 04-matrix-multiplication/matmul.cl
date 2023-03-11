kernel void matmul(
    const int w,
    global const float* A,
    global const float* B,
    global float* res,
)
{
    int i = get_global_id(0);
    int j = get_global_id(1);

    int size_i = get_global_size(0);
    int size_j = get_global_size(1);

    float sum = 0;

    int it = 0;
    if (i < size_i && j < size_j) {
        for (it = 0; it != w; it++)
        {
            sum += A[i + j * it] * B[i * it + j];
        }
        res[i * w + j] = sum;
    }

}
