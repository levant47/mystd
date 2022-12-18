bool is_allocator_initialized;
byte* MEMORY;
// 1 MB
// I'll change this code so that the capacity could be redefinable
// (and I'll make memory allocation unrestricted at some point probably, or maybe a capacity of a few gigs would be enough, we'll see)
// capacity should be aligned to page size
#define MEMORY_CAPACITY (1024 * 1024)

struct AllocationMark
{
    bool is_in_use;
    u64 size;
};

u64 get_bytes_available(AllocationMark* mark)
{
    u64 result = 0;
    while (true)
    {
        if ((byte*)mark == MEMORY + MEMORY_CAPACITY || mark->is_in_use) { return result; }
        result += sizeof(AllocationMark) + mark->size;
        mark = (AllocationMark*)((byte*)mark + sizeof(AllocationMark) + mark->size);
    }
}

void* allocate(u64 size)
{
    if (!is_allocator_initialized)
    {
        MEMORY = (byte*)VirtualAlloc(nullptr, MEMORY_CAPACITY, MEM_RESERVE, PAGE_READWRITE);
        auto mark = (AllocationMark*)MEMORY;
        mark->is_in_use = false;
        mark->size = MEMORY_CAPACITY;
        is_allocator_initialized = true;
     }

    auto allocation_size = sizeof(AllocationMark) + size;
    auto mark = (AllocationMark*)MEMORY;
    while (true)
    {
        auto bytes_available = get_bytes_available(mark);
        if (bytes_available >= allocation_size)
        {
            if (bytes_available - allocation_size <= sizeof(AllocationMark))
            {
                allocation_size = bytes_available;
                size = allocation_size - sizeof(AllocationMark);
            }
            else
            {
                auto next_mark = (AllocationMark*)((byte*)mark + allocation_size);
                next_mark->is_in_use = true;
                next_mark->size = bytes_available - allocation_size;
            }
            break;
        }
        mark = (AllocationMark*)((byte*)mark + sizeof(AllocationMark) + mark->size);
        assert((byte*)mark != MEMORY + MEMORY_CAPACITY, "out of memory");
    }
    mark->is_in_use = true;
    mark->size = size;
    return (byte*)mark + sizeof(AllocationMark);
}

void deallocate(void* data)
{
    auto mark = (AllocationMark*)((byte*)data - sizeof(AllocationMark));
    assert(mark->is_in_use, "double free");
    mark->is_in_use = false;
}

void* reallocate(u64 new_size, void* data)
{
    auto mark = (AllocationMark*)((byte*)data - sizeof(AllocationMark));
    assert(mark->is_in_use, "reallocating deallocated memory");

    auto next_mark = (AllocationMark*)((byte*)data + sizeof(AllocationMark) + mark->size);
    u64 bytes_available = get_bytes_available(next_mark);
    if (mark->size + bytes_available >= new_size)
    {
        if (mark->size + bytes_available - new_size <= sizeof(AllocationMark))
        {
            new_size = mark->size + bytes_available;
        }
        else
        {
            next_mark = (AllocationMark*)((byte*)mark + sizeof(AllocationMark) + new_size);
            next_mark->is_in_use = false;
            next_mark->size = mark->size + bytes_available - new_size - sizeof(AllocationMark);
        }
        mark->size = new_size;
        return data;
    }
    else
    {
        auto new_data = (byte*)allocate(new_size);
        for (u64 i = 0; i < mark->size; i++) { new_data[i] = ((byte*)data)[i]; }
        deallocate(data);
        return new_data;
    }
}
