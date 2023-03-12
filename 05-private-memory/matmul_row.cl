kernel void matmul(
    global const float* A,
    global const float* B,
    global float *res,
    const int w,
    const int v
)
{
    size_t i = get_global_id(0);
    size_t j, k;

    float sum;

    for (j = 0; j < v; j++)
    {
        sum = 0.0f;
        for (k = 0; k < w; k++) sum += A[i * w + k] * B[k * v + j];
        res[i * v + j] = sum;
    }
}
