template <typename T>
struct Option
{
    bool has_data;
    T value;
};

template <typename T>
static Option<T> make_option()
{
    Option<T> result;
    result.has_data = false;
    return result;
}

template <typename T>
static Option<T> make_option(T value)
{
    Option<T> result;
    result.has_data = true;
    result.value = value;
    return result;
}

template <typename T>
static T unwrap(Option<T> option)
{
    assert(option.has_data, "unwrap failed");
    return value;
}

template <typename T>
static T unwrap(const char* error, Option<T> option)
{
    assert(option.has_data, error);
    return value;
}

template <typename TResult, typename TError>
struct Result
{
    bool is_success;
    union
    {
        TResult value;
        TError error;
    };
};

template <typename TResult, typename TError>
static Result<TResult, TError> make_fail(TError error)
{
    Result<TResult, TError> result;
    result.is_success = false;
    result.error = error;
    return result;
}

template <typename TResult, typename TError>
static Result<TResult, TError> make_success(TResult value)
{
    Result<TResult, TError> result;
    result.is_success = true;
    result.value = value;
    return result;
}
