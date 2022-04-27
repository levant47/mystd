bool is_console_io_initialized = false;
HANDLE stdout;

void print(CStringView data, u64 size)
{
    if (!is_console_io_initialized)
    {
        stdout = GetStdHandle(STD_OUTPUT_HANDLE);
        if (stdout == INVALID_HANDLE_VALUE)
        {
            ExitProcess(2);
        }
        is_console_io_initialized = true;
    }
    WriteConsole(stdout, data, size, NULL, NULL);
}
