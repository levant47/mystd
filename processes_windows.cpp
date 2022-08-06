CString CMD_PATH = "C:\\Windows\\System32\\cmd.exe";

PROCESS_INFORMATION start_process(
    CString app_path,
    CString arguments = nullptr,
    CString directory = nullptr,
    CStringView environment = nullptr
)
{
    if (directory != nullptr)
    {
        print(directory, ">");
    }
    print(app_path);
    if (arguments != nullptr)
    {
        print(" ", arguments);
    }
    print("\n");

    STARTUPINFOA startup_info;
    set_memory(0, sizeof(startup_info), (char*)&startup_info);
    startup_info.cb = sizeof(startup_info);
    PROCESS_INFORMATION process_info;
    auto success = CreateProcessA(
        app_path,
        arguments,
        nullptr,
        nullptr,
        false,
        0,
        (void*)environment,
        directory,
        &startup_info,
        &process_info
    );
    assert_winapi(success, "CreateProcess");

    return process_info;
}

u64 complete(PROCESS_INFORMATION process_info)
{
    WaitForSingleObject(process_info.hProcess, INFINITE);
    u64 exit_code;
    GetExitCodeProcess(process_info.hProcess, &exit_code);
    CloseHandle(process_info.hProcess);
    CloseHandle(process_info.hThread);
    return exit_code;
}

PROCESS_INFORMATION start_cmd(CStringView command, CString directory = nullptr, CStringView environment = nullptr)
{
    auto cmd_arguments = String::allocate();
    cmd_arguments.push("/C \"");
    cmd_arguments.push(command);
    cmd_arguments.push('"');
    cmd_arguments.push('\0');
    auto process = start_process(CMD_PATH, cmd_arguments.data, directory, environment);
    cmd_arguments.deallocate();
    return process;
}

PROCESS_INFORMATION start_cmd_without_window(CStringView command, CString directory = nullptr)
{
    auto cmd_arguments = String::allocate();
    cmd_arguments.push("/C \"");
    cmd_arguments.push(command);
    cmd_arguments.push('"');
    cmd_arguments.push('\0');

    STARTUPINFOA startup_info;
    set_memory(0, sizeof(startup_info), &startup_info);
    startup_info.cb = sizeof(startup_info);
    startup_info.dwFlags = STARTF_USESHOWWINDOW;
    startup_info.wShowWindow = SW_HIDE;
    PROCESS_INFORMATION process_info;
    auto success = CreateProcessA(
        CMD_PATH,
        cmd_arguments.data,
        nullptr,
        nullptr,
        false,
        0,
        nullptr,
        directory,
        &startup_info,
        &process_info
    );
    assert_winapi(success, "CreateProcess");

    cmd_arguments.deallocate();

    return process_info;
}

HANDLE start_thread(LPTHREAD_START_ROUTINE proc, void* parameter = nullptr)
{
    return CreateThread(
        nullptr, // default security attributes
        0, // default stack size
        proc,
        parameter,
        0, // default creation flags
        nullptr // do not store thread ID
    );
}

void complete_thread(HANDLE thread_handle)
{
    WaitForSingleObject(thread_handle, INFINITE);
    CloseHandle(thread_handle);
}

// If the function succeeds, the return value is nonzero.
// If the function fails, the return value is zero. To get extended error information, call GetLastError.
bool kill_thread(HANDLE thread_handle, u32 exit_code = 1) { return TerminateThread(thread_handle, exit_code); }

// If the function succeeds, the return value is nonzero.
// If the function fails, the return value is zero. To get extended error information, call GetLastError.
bool kill_process(HANDLE process_handle, u32 exit_code = 1) { return TerminateProcess(process_handle, exit_code); }

// kills the first process it finds with the provided name;
// returns false if no process with such name was found and true otherwise
bool kill_process_by_name(CString name, u32 exit_code = 1)
{
    auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 process_info;
    process_info.dwSize = sizeof(process_info);
    bool process_killed = false;
    while (Process32Next(snapshot, &process_info))
    {
        if (c_string_equal(name, process_info.szExeFile))
        {
            auto target_process_handle = OpenProcess(
                /* dwDesiredAccess: */ PROCESS_TERMINATE,
                /* bInheritHandle: */ false,
               process_info.th32ProcessID
            );
            process_killed = kill_process(target_process_handle, exit_code);
            CloseHandle(target_process_handle);
            break;
        }
    }
    CloseHandle(snapshot);
    return process_killed;
}

