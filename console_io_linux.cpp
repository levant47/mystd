void print(CStringView data, u64 size)
{
    write(STDOUT, data, size);
}
