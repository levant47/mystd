void assert(bool condition, const char* user_message = nullptr)
{
    if (condition)
    {
        return;
    }
    if (user_message == nullptr)
    {
        char message[] = "Assertion failed\n";
        write(STDERR, message, sizeof(message));
    }
    else
    {
        char message[] = "Assertion failed: ";
        write(STDERR, message, sizeof(message));
        auto user_message_length = get_c_string_length(user_message);
        write(STDERR, user_message, user_message_length);
        write(STDERR, "\n", 1);
    }
    exit(1);
}
