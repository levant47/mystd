typedef float f32;
typedef double f64;

u64 align_to(u64 alignment, u64 value)
{
    if (value % alignment == 0)
    {
        return value;
    }
    return (value / alignment + 1) * alignment;
}

u64 number_to_string(u64 value, char* buffer)
{
    u64 size = 0;
    do
    {
        buffer[size] = (value % 10) + '0';
        value /= 10;
        size++;
    }
    while (value != 0);

    for (u64 i = 0; i < size / 2; i++)
    {
        auto temp = buffer[i];
        buffer[i] = buffer[size - i - 1];
        buffer[size - i - 1] = temp;
    }

    return size;
}

template <typename T>
T min(T left, T right)
{
    if (left < right)
    {
        return left;
    }
    return right;
}

template <typename T>
T max(T left, T right)
{
    if (left > right)
    {
        return left;
    }
    return right;
}
