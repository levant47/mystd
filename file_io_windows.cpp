Option<u64> get_file_size(CStringView path)
{
    auto target_file_handle = CreateFileA(
        path,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    if (target_file_handle == INVALID_HANDLE_VALUE)
    {
        return Option<u64>::empty();
    }
    auto target_file_size = GetFileSize(target_file_handle, NULL);
    CloseHandle(target_file_handle);
    return Option<u64>::construct(target_file_size);
}

Option<String> read_whole_file(CStringView path)
{
    auto target_file_handle = CreateFileA(
        path,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    if (target_file_handle == INVALID_HANDLE_VALUE)
    {
        return Option<String>::empty();
    }
    auto target_file_size = GetFileSize(target_file_handle, NULL);
    auto contents = String::allocate(target_file_size);
    ReadFile(target_file_handle, contents.data, target_file_size, NULL, NULL);
    contents.size = target_file_size;
    CloseHandle(target_file_handle);
    return Option<String>::construct(contents);
}
