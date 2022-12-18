static String get_environment_strings()
{
    auto result = allocate_string();
    auto environment = GetEnvironmentStringsA();
    for (u64 i = 0; i < 2 || environment[i - 2] != '\0' || environment[i - 1] != '\0'; i++) { push(environment[i], &result); }
    FreeEnvironmentStringsA(environment);
    return result;
}

static Option<String> get_environment_variable(char* environment_variable_name)
{
    // this size includes null-terminator
    u64 environment_variable_size = GetEnvironmentVariableA(environment_variable_name, nullptr, 0);
    if (environment_variable_size == 0) { return make_option<String>(); }
    auto environment_variable = allocate_string(environment_variable_size);
    // here the size of the string WITHOUT the null-terminator is returned, for details check the docs
    environment_variable.size = GetEnvironmentVariableA(
        environment_variable_name,
        environment_variable.data,
        environment_variable_size
    );
    assert(environment_variable.size + 1 == environment_variable_size);
    return make_option(environment_variable);
}
