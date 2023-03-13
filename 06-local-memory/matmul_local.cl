kernel void matmul(
    global  const   float* A,
    global  const   float* B,
    global          float* res,
    local           float* localA,
    local           float* localB,
    const   unsigned  int  sk
)
{
    size_t i = get_global_id(0);
    size_t j = get_global_id(1);

    size_t li = get_local_id(0);
    size_t lj = get_local_id(1);

    size_t gi = get_group_id(0);
    size_t gj = get_group_id(1);

    size_t si = get_global_size(0);
    size_t sj = get_global_size(1);

    size_t lsi = get_local_size(0);
    size_t lsj = get_local_size(1);

          size_t Abase = gi * sj * lsi ;
    const size_t Ainc  = lsj ;
          size_t Bbase = gj * lsi ;
    const size_t Binc  = sj * lsi ;

    float sum = 0.0f;
    size_t it;

    size_t k;

    // write
    for (it = 0; it < sk; it++) {

    }
    barrier(CLK_LOCAL_MEM_FENCE)

    // compute
    for (it = 0; it < sk; it++)
    {
        sum += localA[it] * localB[it];
    }

    res[i * size_j + j] = sum;
}
