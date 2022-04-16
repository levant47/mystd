void assert(bool condition, const char* message = NULL)
{
    if (condition)
    {
        return;
    }
    if (message == NULL)
    {
        printf("Assertion failed\n");
    }
    else
    {
        printf("Assertion failed: %s\n", message);
    }
    exit(1);
}
