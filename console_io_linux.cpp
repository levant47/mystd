void print_buffer(const char* data, u64 size)
{
    write(STDOUT, data, size);
}
