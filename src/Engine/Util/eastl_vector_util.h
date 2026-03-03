#pragma once

#include <EASTL/fixed_vector.h>


namespace Muharrik
{
    template <typename Vec>
    void erase_unordered(Vec& v, typename Vec::value_type value)
    {
        auto it = eastl::find(v.begin(), v.end(), value);
        if (it == v.end())
        {
            return;
        }
        *it = eastl::move(v.back());
        v.pop_back();
    }

    template <typename Vec>
    void erase_unordered(Vec& v, typename Vec::iterator it)
    {
        *it = eastl::move(v.back());
        v.pop_back();
    }
}