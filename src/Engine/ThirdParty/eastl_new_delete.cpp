#include <new>
#include <cstddef>
#include <cstdlib>

// EASTL debug operator new/delete overloads.
// These may be required depending on EASTL compile options.
static void* aligned_malloc_posix(std::size_t alignment, std::size_t size)
{
    void* p = nullptr;
    // posix_memalign requires alignment to be power of two and >= sizeof(void*)
    if (alignment < sizeof(void*)) alignment = sizeof(void*);
    if ((alignment & (alignment - 1)) != 0) {
        // not a power of two -> fall back
        return std::malloc(size);
    }
    if (posix_memalign(&p, alignment, size) != 0) return nullptr;
    return p;
}

void* operator new[](size_t size, size_t alignment, size_t alignmentOffset,
                     const char* pName, int flags, unsigned debugFlags,
                     const char* file, int line)
{
    (void)alignmentOffset; (void)pName; (void)flags; (void)debugFlags; (void)file; (void)line;
    if (void* p = aligned_malloc_posix(alignment, size)) return p;
    throw std::bad_alloc();
}

void* operator new(size_t size, size_t alignment, size_t alignmentOffset,
                   const char* pName, int flags, unsigned debugFlags,
                   const char* file, int line)
{
    (void)alignmentOffset; (void)pName; (void)flags; (void)debugFlags; (void)file; (void)line;
    if (void* p = aligned_malloc_posix(alignment, size)) return p;
    throw std::bad_alloc();
}

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

void operator delete(void* p, std::size_t) noexcept { ::operator delete(p); }
void operator delete[](void* p, std::size_t) noexcept { ::operator delete[](p); }
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

void operator delete(void* p, size_t, size_t, size_t,
                     const char*, int, unsigned,
                     const char*, int) noexcept
{
    std::free(p);
}

void operator delete[](void* p, size_t, size_t, size_t,
                       const char*, int, unsigned,
                       const char*, int) noexcept
{
    std::free(p);
}