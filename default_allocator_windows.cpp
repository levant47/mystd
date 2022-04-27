// TODO: better implementation!

byte* default_allocate(u64 size)
{
    return (byte*)VirtualAlloc(NULL, size, MEM_COMMIT, PAGE_READWRITE);
}

void default_deallocate(void* address)
{
    VirtualFree(address, 0, MEM_RELEASE);
}

byte* default_reallocate(void* old_address, u64 old_size, u64 new_size)
{
    assert(new_size > old_size);
    auto new_address = default_allocate(new_size);
    copy_memory(old_address, old_size, new_address);
    default_deallocate(old_address);
    return new_address;
}
