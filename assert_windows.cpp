void assert(bool condition, const char* user_message = nullptr)
{
    if (condition)
    {
        return;
    }
    if (user_message == nullptr)
    {
        print("Assertion failed\n");
    }
    else
    {
        print("Assertion failed: ", user_message, "\n");
    }
    ExitProcess(1);
}
