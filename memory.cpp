template <typename T>
T* copy_to_heap(T value)
{
    auto value_on_heap = (T*)malloc(sizeof(T));
    for (u64 i = 0; i < sizeof(T); i++)
    {
        ((char*)value_on_heap)[i] = ((char*)&value)[i];
    }
    return value_on_heap;
}
