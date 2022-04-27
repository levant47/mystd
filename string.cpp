struct String
{
    u64 capacity;
    u64 size;
    char* data;

    static const u64 DEFAULT_CAPACITY = 16;

    static String allocate(u64 capacity = DEFAULT_CAPACITY)
    {
        String result;
        result.capacity = capacity;
        result.size = 0;
        result.data = (char*)default_allocate(sizeof(char) * result.capacity);
        return result;
    }

    static String copy_from_c_string(const char* source)
    {
        auto source_length = get_c_string_length(source);
        auto result = allocate(source_length);
        for (u64 i = 0; i < source_length; i++)
        {
            result.push(source[i]);
        }
        return result;
    }

    String copy()
    {
        String result;
        result.capacity = capacity;
        result.size = size;
        result.data = (char*)default_allocate(sizeof(char) * capacity);
        for (u64 i = 0; i < size; i++)
        {
            result.data[i] = data[i];
        }
        return result;
    }

    void deallocate()
    {
        assert(capacity != 0);
        default_deallocate(data);
        capacity = 0;
    }

    void push(char c)
    {
        if (size == capacity)
        {
            assert(capacity != 0);
            auto new_capacity = capacity * 2;
            data = (char*)default_reallocate(data, capacity * sizeof(char), new_capacity * sizeof(char));
            capacity *= 2;
        }
        data[size] = c;
        size++;
    }

    void push(const char* c_string)
    {
        for (u64 i = 0; c_string[i] != '\0'; i++)
        {
            push(c_string[i]);
        }
    }

    void push(String other_string)
    {
        for (u64 i = 0; i < other_string.size; i++)
        {
            push(other_string.data[i]);
        }
    }

    void pop()
    {
        assert(size != 0);
        size--;
    }

    void reverse()
    {
        reverse_memory(data, size);
    }

    // for use in a debugger
    char* debug()
    {
        push('\0');
        pop();
        return data;
    }
};

bool operator==(String left, String right)
{
    if (left.size != right.size)
    {
        return false;
    }
    for (u64 i = 0; i < left.size; i++)
    {
        if (left.data[i] != right.data[i])
        {
            return false;
        }
    }
    return true;
}

bool operator==(String left, const char* right)
{
    u64 i = 0;
    while (i != left.size && right[i] != '\0')
    {
        if (left.data[i] != right[i])
        {
            return false;
        }
        i++;
    }
    return i == left.size && right[i] == '\0';
}

bool operator!=(String left, const char* right)
{
    return !(left == right);
}

String number_to_string(u32 number)
{
    auto result = String::allocate();

    do
    {
        result.push((number % 10) + '0');
        number /= 10;
    }
    while (number != 0);

    result.reverse();

    return result;
}

void print(String string)
{
    print(string.data, string.size);
}
