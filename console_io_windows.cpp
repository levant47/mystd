bool is_console_io_initialized = false;
HANDLE STDOUT;

static void print_buffer(const char* data, u64 size)
{
    if (!is_console_io_initialized)
    {
        STDOUT = GetStdHandle(STD_OUTPUT_HANDLE);
        if (STDOUT == INVALID_HANDLE_VALUE)
        {
            ExitProcess(2);
        }
        is_console_io_initialized = true;
    }
    WriteFile(STDOUT, data, size, NULL, NULL); // WriteConsole doesn't handle pipes!
}
