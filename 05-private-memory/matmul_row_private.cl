kernel void matmul(
    global const float* A,
    global const float* B,
    global float *res,
    const unsigned int w,
    const unsigned int v
)
{
    unsigned int i = get_global_id(0);
    unsigned int j, k;

    float privA[2048];
    float sum;

    for (k = 0; k < w; k++)
        privA[k] = A[i * w + k];

    for (j = 0; j < v; j++)
    {
        sum = 0.0f;
        for (k = 0; k < w; k++) {
            sum += privA[k] * B[k * v + j];
        }
        res[i * v + j] = sum;
    }
}
