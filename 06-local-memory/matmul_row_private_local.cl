kernel void matmul(
    global  const   float*  A,
    global  const   float*  B,
    global          float*  res,
    local           float*  localA,
    const   unsigned    int sj
)
{
    unsigned int j, k;
    unsigned int i = get_group_id(0); //
    unsigned int sk = get_local_size(0);
    unsigned int lk = get_local_id(0);

    float sum;

    if (lk < sk)
        localA[lk] = A[i * sk + lk];
    barrier(CLK_LOCAL_MEM_FENCE);


    for (j = 0; j < sj; j++)
        {
            sum = 0.0f;
            for (k = 0; k < sk; k++)
                sum += localA[k] * B[k * sj + j];
            res[i * sj + j] = sum;
            barrier(CLK_LOCAL_MEM_FENCE);
        }
}
