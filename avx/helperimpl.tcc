/*  This file is part of the Vc library.

    Copyright (C) 2011-2012 Matthias Kretz <kretz@kde.org>

    Vc is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as
    published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version.

    Vc is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with Vc.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef VC_AVX_HELPERIMPL_TCC
#define VC_AVX_HELPERIMPL_TCC

Vc_NAMESPACE_BEGIN(Internal)

template<size_t X>
static constexpr size_t nextMultipleOf(size_t value)
{
    return (value % X) > 0 ? value + X - (value % X) : value;
}

template<Vc::MallocAlignment A>
Vc_ALWAYS_INLINE void *HelperImpl<VC_IMPL>::malloc(size_t n)
{
    switch (A) {
        case Vc::AlignOnVector:
            return _mm_malloc(nextMultipleOf<Vc::Vc_IMPL_NAMESPACE::VectorAlignment>(n), Vc::Vc_IMPL_NAMESPACE::VectorAlignment);
        case Vc::AlignOnCacheline:
            // TODO: hardcoding 64 is not such a great idea
            return _mm_malloc(nextMultipleOf<64>(n), 64);
        case Vc::AlignOnPage:
            // TODO: hardcoding 4096 is not such a great idea
            return _mm_malloc(nextMultipleOf<4096>(n), 4096);
        default:
#ifndef NDEBUG
            abort();
#endif
            return _mm_malloc(n, 8);
    }
}

Vc_ALWAYS_INLINE void HelperImpl<VC_IMPL>::free(void *p)
{
    _mm_free(p);
}

Vc_NAMESPACE_END

#endif // VC_AVX_HELPERIMPL_TCC
