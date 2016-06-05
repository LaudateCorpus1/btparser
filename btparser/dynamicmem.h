#pragma once

static void* emalloc(size_t size)
{
    return malloc(size);
}

static void efree(void* ptr)
{
    free(ptr);
}

static void* erealloc(void* ptr, size_t size)
{
    return realloc(ptr, size);
}

template<typename T>
class Memory
{
public:
    //
    // This class guarantees that the returned allocated memory
    // will always be zeroed
    //
    explicit Memory(const char* Reason = "Memory:???")
    {
        m_Ptr = nullptr;
        m_Size = 0;
        m_Reason = Reason;
    }

    explicit Memory(size_t Size, const char* Reason = "Memory:???")
    {
        m_Ptr = reinterpret_cast<T>(emalloc(Size));
        m_Size = Size;
        m_Reason = Reason;

        memset(m_Ptr, 0, Size);
    }

    ~Memory()
    {
        if(m_Ptr)
            efree(m_Ptr);
    }

    T realloc(size_t Size, const char* Reason = "Memory:???")
    {
        m_Ptr = reinterpret_cast<T>(erealloc(m_Ptr, Size));
        m_Size = Size;
        m_Reason = Reason;

        return (T)memset(m_Ptr, 0, m_Size);
    }

    size_t size()
    {
        return m_Size;
    }

    T operator()()
    {
        return m_Ptr;
    }

private:
    T           m_Ptr;
    size_t      m_Size;
    const char* m_Reason;
};