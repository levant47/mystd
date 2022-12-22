template <typename T>
struct ListView
{
    u64 size;
    T* data;
};

template <typename T>
static ListView<T> make_list_view(u64 size, T* data)
{
    ListView<T> result;
    result.size = size;
    result.data = data;
    return result;
}

template <typename T>
struct List
{
    u64 capacity;
    u64 size;
    T* data;

};

#define DEFAULT_LIST_CAPACITY 16

template <typename T>
static List<T> allocate_list(u64 capacity = DEFAULT_LIST_CAPACITY)
{
    List<T> result;
    result.capacity = capacity;
    result.size = 0;
    result.data = (T*)allocate(sizeof(T) * capacity);
    return result;
}

template <typename T>
static void deallocate(List<T> list) { deallocate(list.data); }

template <typename T>
static void push(T element, List<T>* list)
{
    if (list->size == list->capacity)
    {
        list->capacity *= 2;
        list->data = (T*)reallocate(list->data, sizeof(T) * list->capacity);
    }
    list->data[list->size] = element;
    list->size++;
}

template <typename T>
static void push(ListView<T> source, List<T>* list)
{
    for (u64 i = 0; i < source.size; i++)
    {
        push(source.data[i], list);
    }
}

template <typename T>
static void pop(List<T>* list) { list->size--; }

template <typename T>
static bool contains(T element, List<T> list)
{
    for (u64 i = 0; i < list.size; i++)
    {
        if (list.data[i] == element)
        {
            return true;
        }
    }
    return false;
}

template <typename T>
static void clear(List<T>* list)
{
    list->size = 0;
}
