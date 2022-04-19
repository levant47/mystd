typedef __UINT64_TYPE__ u64;
typedef __UINT32_TYPE__ u32;
typedef __UINT16_TYPE__ u16;
typedef __UINT8_TYPE__ u8;
typedef __INT64_TYPE__ s64;
typedef __INT32_TYPE__ s32;
typedef __INT16_TYPE__ s16;
typedef __INT8_TYPE__ s8;
typedef float f32;
typedef double f64;
typedef char byte;

u64 align_to(u64 alignment, u64 value)
{
    if (value % alignment == 0)
    {
        return value;
    }
    return (value / alignment + 1) * alignment;
}
