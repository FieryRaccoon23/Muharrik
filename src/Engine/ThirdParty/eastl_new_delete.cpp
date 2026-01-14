#include <new>
#include <cstddef>

// EASTL debug operator new/delete overloads.
// These may be required depending on EASTL compile options.

void* operator new[](std::size_t size,
                     const char* /*name*/, int /*flags*/, unsigned /*debugFlags*/,
                     const char* /*file*/, int /*line*/)
{
    return ::operator new[](size);
}

void* operator new(std::size_t size,
                   const char* /*name*/, int /*flags*/, unsigned /*debugFlags*/,
                   const char* /*file*/, int /*line*/)
{
    return ::operator new(size);
}

void operator delete[](void* p,
                       const char* /*name*/, int /*flags*/, unsigned /*debugFlags*/,
                       const char* /*file*/, int /*line*/) noexcept
{
    ::operator delete[](p);
}

void operator delete(void* p,
                     const char* /*name*/, int /*flags*/, unsigned /*debugFlags*/,
                     const char* /*file*/, int /*line*/) noexcept
{
    ::operator delete(p);
}

void operator delete(void* p, std::size_t) noexcept { ::operator delete(p); }
void operator delete[](void* p, std::size_t) noexcept { ::operator delete[](p); }