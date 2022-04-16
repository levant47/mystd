template <typename T>
struct Option
{
    bool has_data;
    T value;

    static Option<T> empty()
    {
        Option<T> result;
        result.has_data = false;
        return result;
    }

    static Option<T> construct(T value)
    {
        Option<T> result;
        result.has_data = true;
        result.value = value;
        return result;
    }
};
