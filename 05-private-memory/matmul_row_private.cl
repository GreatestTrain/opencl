kernel sjoid matmul(
    global const float* A,
    global const float* B,
    global float *res,
    const unsigned int sk,
    const unsigned int sj
)
{
    unsigned int i = get_global_id(0);
    unsigned int j, k;

    float privA[2048];
    float sum;

    for (k = 0; k < sk; k++)
        privA[k] = A[i * sk + k];

    for (j = 0; j < sj; j++)
    {
        sum = 0.0f;
        for (k = 0; k < sk; k++) {
            sum += privA[k] * B[k * sj + j];
        }
        res[i * sj + j] = sum;
    }
}
