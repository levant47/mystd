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
        NULL,
        NULL,
        false,
        0,
        NULL,
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
