#include <new>
#include <cstddef>
#include <cstdlib>

#if defined(_WIN32)
    #include <malloc.h> // _aligned_malloc, _aligned_free
#endif

// EASTL debug operator new/delete overloads.
// These may be required depending on EASTL compile options.

static void* aligned_malloc_platform(std::size_t alignment, std::size_t size)
{
    // alignment must be power-of-two and >= sizeof(void*)
    if (alignment < sizeof(void*)) alignment = sizeof(void*);
    if ((alignment & (alignment - 1)) != 0) {
        // not a power of two -> fall back
        return std::malloc(size);
    }

#if defined(_WIN32)
    return _aligned_malloc(size, alignment);
#else
    void* p = nullptr;
    if (posix_memalign(&p, alignment, size) != 0) return nullptr;
    return p;
#endif
}

static void aligned_free_platform(void* p, std::size_t alignment) noexcept
{
    if (!p) return;

    // If we fell back to std::malloc because alignment wasn't power-of-two,
    // then std::free is correct.
    if (alignment < sizeof(void*)) alignment = sizeof(void*);
    const bool powerOfTwo = ((alignment & (alignment - 1)) == 0);

#if defined(_WIN32)
    if (powerOfTwo) _aligned_free(p);
    else std::free(p);
#else
    (void)alignment;
    std::free(p); // posix_memalign memory is freed with free()
#endif
}

void* operator new[](size_t size, size_t alignment, size_t alignmentOffset,
                     const char* pName, int flags, unsigned debugFlags,
                     const char* file, int line)
{
    (void)alignmentOffset; (void)pName; (void)flags; (void)debugFlags; (void)file; (void)line;
    if (void* p = aligned_malloc_platform(alignment, size)) return p;
    throw std::bad_alloc();
}

void* operator new(size_t size, size_t alignment, size_t alignmentOffset,
                   const char* pName, int flags, unsigned debugFlags,
                   const char* file, int line)
{
    (void)alignmentOffset; (void)pName; (void)flags; (void)debugFlags; (void)file; (void)line;
    if (void* p = aligned_malloc_platform(alignment, size)) return p;
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

// sized deletes (fine to forward)
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

// EASTL debug aligned delete overloads MUST match the aligned allocation used above.
void operator delete(void* p, size_t /*size*/, size_t alignment, size_t /*alignmentOffset*/,
                     const char*, int, unsigned,
                     const char*, int) noexcept
{
    aligned_free_platform(p, alignment);
}

void operator delete[](void* p, size_t /*size*/, size_t alignment, size_t /*alignmentOffset*/,
                       const char*, int, unsigned,
                       const char*, int) noexcept
{
    aligned_free_platform(p, alignment);
}
