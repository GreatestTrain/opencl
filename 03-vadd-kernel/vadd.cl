kernel void vadd(
    global const float* a,
    global const float* b,
    global float* c,
    const unsigned int count
)
{
    int i = get_global_id(0);
    if (i < count) {
        c[i] = a[i] + b[i];
    } else {
        c[i] = i;
    }
}
