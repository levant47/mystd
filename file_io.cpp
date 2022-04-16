#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

u64 get_file_size(const char* path)
{
    struct stat stat_result;
    stat(path, &stat_result);
    return (u64)stat_result.st_size;
}

String read_whole_file(const char* path)
{
    auto file_size = get_file_size(path);
    auto result = String::allocate(file_size);
    auto file_id = open(path, O_RDONLY);
    assert(file_id != -1, "read_file failed to open file");
    auto bytes_read = read(file_id, result.data, file_size);
    assert(bytes_read == file_size, "read_file failed to read whole file");
    result.size = file_size;
    close(file_id);
    return result;
}
