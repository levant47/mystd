Result<u64, s64> get_file_size(CStringView path)
{
    StatResult target_stat_result;
    auto error = stat(path, &target_stat_result);
    if (error != 0)
    {
        return Result<u64, s64>::fail(error);
    }
    return Result<u64, s64>::success((u64)target_stat_result.size);
}

Option<String> read_whole_file(CStringView path)
{
    auto file_size_result = get_file_size(path);
    if (!file_size_result.is_success) { return Option<String>::empty(); }
    auto file_size = file_size_result.value;

    auto result = String::allocate(file_size);

    auto file_id = open(path, OpenFlagReadOnly);
    if (file_id == -1) { return Option<String>::empty(); }

    auto bytes_read = read(file_id, result.data, file_size);
    if (bytes_read != file_size) { return Option<String>::empty(); }

    result.size = file_size;

    close(file_id);

    return Option<String>::construct(result);
}
