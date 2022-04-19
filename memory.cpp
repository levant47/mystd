void copy_memory(const void* passed_source, u64 size, void* passed_destination)
{
    auto source = (byte*)passed_source;
    auto destination = (byte*)passed_destination;
    for (u64 i = 0; i < size; i++)
    {
        destination[i] = source[i];
    }
}

void reverse_memory(void* passed_source, u64 size)
{
    auto source = (byte*)passed_source;
    for (u64 i = 0; i < size / 2; i++)
    {
        byte temp = source[i];
        source[i] = source[size - i - 1];
        source[size - i - 1] = temp;
    }
}

template <typename T>
T* copy_to_heap(T value)
{
    auto value_on_heap = (T*)default_allocate(sizeof(T));
    copy_memory(&value, sizeof(T), value_on_heap);
    return value_on_heap;
}
