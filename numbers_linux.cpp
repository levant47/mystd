typedef __UINT64_TYPE__ u64;
typedef __UINT32_TYPE__ u32;
typedef __UINT16_TYPE__ u16;
typedef __UINT8_TYPE__ u8;
typedef __INT64_TYPE__ s64;
typedef __INT32_TYPE__ s32;
typedef __INT16_TYPE__ s16;
typedef __INT8_TYPE__ s8;
typedef char byte;

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
