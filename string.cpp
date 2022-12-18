static char to_lower(char c) { return c >= 'A' && c <= 'Z' ? c + ('a' - 'A') : c; }

struct StringView
{
    u64 size;
    const char* data;
};

static StringView make_string_view(u64 size, const char* data)
{
    StringView result;
    result.size = size;
    result.data = data;
    return result;
}

static StringView make_string_view(const char* source)
{
    StringView result;
    result.size = get_length(source);
    result.data = source;
    return result;
}

struct String
{
    u64 capacity;
    u64 size;
    char* data;
};

#define DEFAULT_STRING_CAPACITY 16

static String allocate_string(u64 capacity = DEFAULT_STRING_CAPACITY)
{
    String result;
    result.capacity = capacity;
    result.size = 0;
    result.data = (char*)allocate(sizeof(char) * capacity);
    return result;
}

static String allocate_string_from_number(u64 value, u64 base = 10)
{
    assert(base <= 36, "number base out of range");
    auto result = allocate_string(64);
    result.size = number_to_string(value, result.data, base);
    return result;
}

static String allocate_string_from_number(s64 value, u64 base = 10)
{
    assert(base <= 36, "number base out of range");
    auto result = allocate_string(64);
    result.size = number_to_string(value, result.data, base);
    return result;
}

static String copy(String source)
{
    String result;
    result.capacity = source.size;
    result.size = source.size;
    result.data = (char*)allocate(sizeof(char) * source.size);
    for (u64 i = 0; i < source.size; i++)
    {
        result.data[i] = source.data[i];
    }
    return result;
}

static void deallocate(String string) { deallocate(string.data); }

static void push(char c, String* string)
{
    if (string->size == string->capacity)
    {
        string->capacity *= 2;
        string->data = (char*)reallocate(string->capacity * sizeof(char), string->data);
    }
    string->data[string->size] = c;
    string->size++;
}

static String allocate_string_copy(const char* source)
{
    auto source_length = get_length(source);
    auto result = allocate_string(source_length);
    for (u64 i = 0; i < source_length; i++)
    {
        push(source[i], &result);
    }
    return result;
}

static void push(const char* source, String* string)
{
    for (u64 i = 0; source[i] != '\0'; i++)
    {
        push(source[i], string);
    }
}

static void push(String other_string, String* target)
{
    for (u64 i = 0; i < other_string.size; i++)
    {
        push(other_string.data[i], target);
    }
}

static void push(u64 number, u64 base, String* target)
{
    char buffer[20];
    auto digits_count = number_to_string(number, buffer, base);
    for (u64 i = 0; i < digits_count; i++)
    {
        push(buffer[i], target);
    }
}

static void push(u64 number, String* target) { push(number, 10, target); }

static void push(StringView source, String* target)
{
    for (u64 i = 0; i < source.size; i++)
    {
        push(source.data[i], target);
    }
}

static void pop(String* target)
{
    assert(target->size != 1);
    target->size--;
}

static void pop(u64 count, String* target)
{
    assert(target->size >= count);
    target->size -= count;
}

static void reverse(String* string) { reverse_memory(string->data, string->size); }

static void make_c_string_compatible(String* string) { push('\0', string); pop(string); }

static void clear(String* string) { string->size = 0; }

static StringView make_string_view(String string) { return make_string_view(string.size, string.data); }

static void reserve_at_least(u64 new_capacity, String* string)
{
    if (string->capacity >= new_capacity) { return; }
    string->data = (char*)reallocate(new_capacity * sizeof(char), string->data);
    string->capacity = new_capacity;
}

static bool operator==(String left, String right)
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

static bool operator==(String left, const char* right)
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

static bool operator!=(String left, const char* right)
{
    return !(left == right);
}

static void print(String string)
{
    print_buffer(string.data, string.size);
}
