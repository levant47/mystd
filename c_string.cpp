typedef char* CString;
typedef const char* CStringView;

u64 get_c_string_length(CStringView source)
{
    u64 i = 0;
    while (source[i] != '\0')
    {
        i++;
    }
    return i;
}
