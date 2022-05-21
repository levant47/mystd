CString CMD_PATH = "C:\\Windows\\System32\\cmd.exe";

PROCESS_INFORMATION start_process(CString app_path, CString arguments = nullptr, CString directory = nullptr)
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
        nullptr,
        directory,
        &startup_info,
        &process_info
    );
    assert_winapi(success, "CreateProcess");

    return process_info;
}

void complete(PROCESS_INFORMATION process_info)
{
    WaitForSingleObject(process_info.hProcess, INFINITE);
    CloseHandle(process_info.hProcess);
    CloseHandle(process_info.hThread);
}

PROCESS_INFORMATION start_cmd(CStringView command, CString directory = nullptr)
{
    auto cmd_arguments = String::allocate();
    cmd_arguments.push("/C \"");
    cmd_arguments.push(command);
    cmd_arguments.push('"');
    cmd_arguments.push('\0');
    auto process = start_process(CMD_PATH, cmd_arguments.data, directory);
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
    set_memory(0, sizeof(startup_info), (char*)&startup_info);
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

