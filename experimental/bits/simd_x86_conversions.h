#ifndef _GLIBCXX_EXPERIMENTAL_SIMD_X86_CONVERSIONS_H
#define _GLIBCXX_EXPERIMENTAL_SIMD_X86_CONVERSIONS_H

#pragma GCC system_header

#if __cplusplus >= 201703L

// work around PR85827
// 1-arg __convert_x86 {{{1
template <class _To, class _V, class _Traits> _GLIBCXX_SIMD_INTRINSIC _To __convert_x86(_V __vv)
{
    using _T = typename _Traits::value_type;
    constexpr size_t _N = _Traits::width;
    const auto __intrin = __to_intrin(__vv);
    __storage<_T, _N> __v(__vv);
    using _U = typename __vector_traits<_To>::value_type;
    constexpr size_t _M = __vector_traits<_To>::width;

    // [xyz]_to_[xyz] {{{2
    constexpr bool __x_to_x = sizeof(__v) == 16 && sizeof(_To) == 16;
    constexpr bool __x_to_y = sizeof(__v) == 16 && sizeof(_To) == 32;
    constexpr bool __x_to_z = sizeof(__v) == 16 && sizeof(_To) == 64;
    constexpr bool __y_to_x = sizeof(__v) == 32 && sizeof(_To) == 16;
    constexpr bool __y_to_y = sizeof(__v) == 32 && sizeof(_To) == 32;
    constexpr bool __y_to_z = sizeof(__v) == 32 && sizeof(_To) == 64;
    constexpr bool __z_to_x = sizeof(__v) == 64 && sizeof(_To) == 16;
    constexpr bool __z_to_y = sizeof(__v) == 64 && sizeof(_To) == 32;
    constexpr bool __z_to_z = sizeof(__v) == 64 && sizeof(_To) == 64;

    // iX_to_iX {{{2
    constexpr bool __i_to_i = is_integral_v<_U> && is_integral_v<_T>;
    constexpr bool i8_to_i16  = __i_to_i && sizeof(_T) == 1 && sizeof(_U) == 2;
    constexpr bool i8_to_i32  = __i_to_i && sizeof(_T) == 1 && sizeof(_U) == 4;
    constexpr bool i8_to_i64  = __i_to_i && sizeof(_T) == 1 && sizeof(_U) == 8;
    constexpr bool i16_to_i8  = __i_to_i && sizeof(_T) == 2 && sizeof(_U) == 1;
    constexpr bool i16_to_i32 = __i_to_i && sizeof(_T) == 2 && sizeof(_U) == 4;
    constexpr bool i16_to_i64 = __i_to_i && sizeof(_T) == 2 && sizeof(_U) == 8;
    constexpr bool i32_to_i8  = __i_to_i && sizeof(_T) == 4 && sizeof(_U) == 1;
    constexpr bool i32_to_i16 = __i_to_i && sizeof(_T) == 4 && sizeof(_U) == 2;
    constexpr bool i32_to_i64 = __i_to_i && sizeof(_T) == 4 && sizeof(_U) == 8;
    constexpr bool i64_to_i8  = __i_to_i && sizeof(_T) == 8 && sizeof(_U) == 1;
    constexpr bool i64_to_i16 = __i_to_i && sizeof(_T) == 8 && sizeof(_U) == 2;
    constexpr bool i64_to_i32 = __i_to_i && sizeof(_T) == 8 && sizeof(_U) == 4;

    // [fsu]X_to_[fsu]X {{{2
    // ibw = integral && byte or word, i.e. char and short with any signedness
    constexpr bool s64_to_f32 = is_integral_v<_T> &&   is_signed_v<_T> && sizeof(_T) == 8 && is_floating_point_v<_U> && sizeof(_U) == 4;
    constexpr bool s32_to_f32 = is_integral_v<_T> &&   is_signed_v<_T> && sizeof(_T) == 4 && is_floating_point_v<_U> && sizeof(_U) == 4;
    constexpr bool s16_to_f32 = is_integral_v<_T> &&   is_signed_v<_T> && sizeof(_T) == 2 && is_floating_point_v<_U> && sizeof(_U) == 4;
    constexpr bool  s8_to_f32 = is_integral_v<_T> &&   is_signed_v<_T> && sizeof(_T) == 1 && is_floating_point_v<_U> && sizeof(_U) == 4;
    constexpr bool u64_to_f32 = is_integral_v<_T> && is_unsigned_v<_T> && sizeof(_T) == 8 && is_floating_point_v<_U> && sizeof(_U) == 4;
    constexpr bool u32_to_f32 = is_integral_v<_T> && is_unsigned_v<_T> && sizeof(_T) == 4 && is_floating_point_v<_U> && sizeof(_U) == 4;
    constexpr bool u16_to_f32 = is_integral_v<_T> && is_unsigned_v<_T> && sizeof(_T) == 2 && is_floating_point_v<_U> && sizeof(_U) == 4;
    constexpr bool  u8_to_f32 = is_integral_v<_T> && is_unsigned_v<_T> && sizeof(_T) == 1 && is_floating_point_v<_U> && sizeof(_U) == 4;
    constexpr bool s64_to_f64 = is_integral_v<_T> &&   is_signed_v<_T> && sizeof(_T) == 8 && is_floating_point_v<_U> && sizeof(_U) == 8;
    constexpr bool s32_to_f64 = is_integral_v<_T> &&   is_signed_v<_T> && sizeof(_T) == 4 && is_floating_point_v<_U> && sizeof(_U) == 8;
    constexpr bool u64_to_f64 = is_integral_v<_T> && is_unsigned_v<_T> && sizeof(_T) == 8 && is_floating_point_v<_U> && sizeof(_U) == 8;
    constexpr bool u32_to_f64 = is_integral_v<_T> && is_unsigned_v<_T> && sizeof(_T) == 4 && is_floating_point_v<_U> && sizeof(_U) == 8;
    constexpr bool f32_to_s64 = is_integral_v<_U> &&   is_signed_v<_U> && sizeof(_U) == 8 && is_floating_point_v<_T> && sizeof(_T) == 4;
    constexpr bool f32_to_s32 = is_integral_v<_U> &&   is_signed_v<_U> && sizeof(_U) == 4 && is_floating_point_v<_T> && sizeof(_T) == 4;
    constexpr bool f32_to_u64 = is_integral_v<_U> && is_unsigned_v<_U> && sizeof(_U) == 8 && is_floating_point_v<_T> && sizeof(_T) == 4;
    constexpr bool f32_to_u32 = is_integral_v<_U> && is_unsigned_v<_U> && sizeof(_U) == 4 && is_floating_point_v<_T> && sizeof(_T) == 4;
    constexpr bool f64_to_s64 = is_integral_v<_U> &&   is_signed_v<_U> && sizeof(_U) == 8 && is_floating_point_v<_T> && sizeof(_T) == 8;
    constexpr bool f64_to_s32 = is_integral_v<_U> &&   is_signed_v<_U> && sizeof(_U) == 4 && is_floating_point_v<_T> && sizeof(_T) == 8;
    constexpr bool f64_to_u64 = is_integral_v<_U> && is_unsigned_v<_U> && sizeof(_U) == 8 && is_floating_point_v<_T> && sizeof(_T) == 8;
    constexpr bool f64_to_u32 = is_integral_v<_U> && is_unsigned_v<_U> && sizeof(_U) == 4 && is_floating_point_v<_T> && sizeof(_T) == 8;
    constexpr bool ibw_to_f32 = is_integral_v<_T> && sizeof(_T) <= 2 && is_floating_point_v<_U> && sizeof(_U) == 4;
    constexpr bool ibw_to_f64 = is_integral_v<_T> && sizeof(_T) <= 2 && is_floating_point_v<_U> && sizeof(_U) == 8;
    constexpr bool f32_to_ibw = is_integral_v<_U> && sizeof(_U) <= 2 && is_floating_point_v<_T> && sizeof(_T) == 4;
    constexpr bool f64_to_ibw = is_integral_v<_U> && sizeof(_U) <= 2 && is_floating_point_v<_T> && sizeof(_T) == 8;
    constexpr bool f32_to_f64 = is_floating_point_v<_T> && sizeof(_T) == 4 && is_floating_point_v<_U> && sizeof(_U) == 8;
    constexpr bool f64_to_f32 = is_floating_point_v<_T> && sizeof(_T) == 8 && is_floating_point_v<_U> && sizeof(_U) == 4;

    if constexpr (__i_to_i && __y_to_x && !__have_avx2) {  //{{{2
        return __convert_x86<_To>(__lo128(__v), __hi128(__v));
    } else if constexpr (__i_to_i && __x_to_y && !__have_avx2) {  //{{{2
        return __concat(__convert_x86<__vector_type_t<_U, _M / 2>>(__v),
                        __convert_x86<__vector_type_t<_U, _M / 2>>(
                            __extract_part<1, _N / _M * 2>(__v)));
    } else if constexpr (__i_to_i) {  //{{{2
        static_assert(__x_to_x || __have_avx2,
                      "integral conversions with ymm registers require AVX2");
        static_assert(__have_avx512bw || ((sizeof(_T) >= 4 || sizeof(__v) < 64) &&
                                        (sizeof(_U) >= 4 || sizeof(_To) < 64)),
                      "8/16-bit integers in zmm registers require AVX512BW");
        static_assert((sizeof(__v) < 64 && sizeof(_To) < 64) || __have_avx512f,
                      "integral conversions with ymm registers require AVX2");
    }

    if constexpr (is_floating_point_v<_T> == is_floating_point_v<_U> &&  //{{{2
                  sizeof(_T) == sizeof(_U)) {
        // conversion uses simple bit reinterpretation (or no conversion at all)
        if constexpr (_N >= _M) {
            return __intrin_bitcast<_To>(__vv);
        } else {
            return __zero_extend(__vector_bitcast<_U>(__v));
        }
    } else if constexpr (_N < _M && sizeof(_To) > 16) {  // zero extend (eg. xmm -> ymm){{{2
        return __zero_extend(
            __convert_x86<
                __vector_type_t<_U, (16 / sizeof(_U) > _N) ? 16 / sizeof(_U) : _N>>(__v));
    } else if constexpr (_N > _M && sizeof(__v) > 16) {  // partial input (eg. ymm -> xmm){{{2
        return __convert_x86<_To>(__extract_part<0, _N / _M>(__v));
    } else if constexpr (i64_to_i32) {  //{{{2
        if constexpr (__x_to_x && __have_avx512vl) {
            return __intrin_bitcast<_To>(_mm_cvtepi64_epi32(__v));
        } else if constexpr (__x_to_x) {
            return __auto_bitcast(_mm_shuffle_ps(__auto_bitcast(__v), __m128(), 8));
            // return __intrin_bitcast<_To>(_mm_unpacklo_epi64(_mm_shuffle_epi32(__v, 8), __m128i()));
        } else if constexpr (__y_to_x && __have_avx512vl) {
            return __intrin_bitcast<_To>(_mm256_cvtepi64_epi32(__v));
        } else if constexpr (__y_to_x && __have_avx512f) {
            return __intrin_bitcast<_To>(__lo128(_mm512_cvtepi64_epi32(__auto_bitcast(__v.d))));
        } else if constexpr (__y_to_x) {
            return __intrin_bitcast<_To>(__lo128(_mm256_permute4x64_epi64(_mm256_shuffle_epi32(__v, 8), 0 + 4 * 2)));
        } else if constexpr (__z_to_y) {
            return __intrin_bitcast<_To>(_mm512_cvtepi64_epi32(__v));
        }
    } else if constexpr (i64_to_i16) {  //{{{2
        if constexpr (__x_to_x && __have_avx512vl) {
            return __intrin_bitcast<_To>(_mm_cvtepi64_epi16(__v));
        } else if constexpr (__x_to_x && __have_avx512f) {
            return __intrin_bitcast<_To>(__lo128(_mm512_cvtepi64_epi16(__auto_bitcast(__v))));
        } else if constexpr (__x_to_x && __have_ssse3) {
            return __intrin_bitcast<_To>(_mm_shuffle_epi8(
                __v, _mm_setr_epi8(0, 1, 8, 9, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
                                   -0x80, -0x80, -0x80, -0x80, -0x80, -0x80)));
            // fallback without SSSE3
        } else if constexpr (__y_to_x && __have_avx512vl) {
            return __intrin_bitcast<_To>(_mm256_cvtepi64_epi16(__v));
        } else if constexpr (__y_to_x && __have_avx512f) {
            return __intrin_bitcast<_To>(__lo128(_mm512_cvtepi64_epi16(__auto_bitcast(__v))));
        } else if constexpr (__y_to_x) {
            const auto a = _mm256_shuffle_epi8(
                __v, _mm256_setr_epi8(0, 1, 8, 9, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
                                    -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
                                    -0x80, -0x80, -0x80, 0, 1, 8, 9, -0x80, -0x80, -0x80,
                                    -0x80, -0x80, -0x80, -0x80, -0x80));
            return __intrin_bitcast<_To>(__lo128(a) | __hi128(a));
        } else if constexpr (__z_to_x) {
            return __intrin_bitcast<_To>(_mm512_cvtepi64_epi16(__v));
        }
    } else if constexpr (i64_to_i8) {   //{{{2
        if constexpr (__x_to_x && __have_avx512vl) {
            return __intrin_bitcast<_To>(_mm_cvtepi64_epi8(__v));
        } else if constexpr (__x_to_x && __have_avx512f) {
            return __intrin_bitcast<_To>(__lo128(_mm512_cvtepi64_epi8(__zero_extend(__v.intrin()))));
        } else if constexpr (__y_to_x && __have_avx512vl) {
            return __intrin_bitcast<_To>(_mm256_cvtepi64_epi8(__v));
        } else if constexpr (__y_to_x && __have_avx512f) {
            return __intrin_bitcast<_To>(_mm512_cvtepi64_epi8(__zero_extend(__v.intrin())));
        } else if constexpr (__z_to_x) {
            return __intrin_bitcast<_To>(_mm512_cvtepi64_epi8(__v));
        }
    } else if constexpr (i32_to_i64) {    //{{{2
        if constexpr (__have_sse4_1 && __x_to_x) {
            return __intrin_bitcast<_To>(is_signed_v<_T> ? _mm_cvtepi32_epi64(__v) : _mm_cvtepu32_epi64(__v));
        } else if constexpr (__x_to_x) {
            return __intrin_bitcast<_To>(_mm_unpacklo_epi32(
                __v, is_signed_v<_T> ? _mm_srai_epi32(__v, 31) : __m128i()));
        } else if constexpr (__x_to_y) {
            return __intrin_bitcast<_To>(is_signed_v<_T> ? _mm256_cvtepi32_epi64(__v) : _mm256_cvtepu32_epi64(__v));
        } else if constexpr (__y_to_z) {
            return __intrin_bitcast<_To>(is_signed_v<_T> ? _mm512_cvtepi32_epi64(__v) : _mm512_cvtepu32_epi64(__v));
        }
    } else if constexpr (i32_to_i16) {  //{{{2
        if constexpr (__x_to_x && __have_avx512vl) {
            return __intrin_bitcast<_To>(_mm_cvtepi32_epi16(__v));
        } else if constexpr (__x_to_x && __have_avx512f) {
            return __intrin_bitcast<_To>(__lo128(_mm512_cvtepi32_epi16(__auto_bitcast(__v))));
        } else if constexpr (__x_to_x && __have_ssse3) {
            return __intrin_bitcast<_To>(_mm_shuffle_epi8(
                __v, _mm_setr_epi8(0, 1, 4, 5, 8, 9, 12, 13, -0x80, -0x80, -0x80, -0x80,
                                   -0x80, -0x80, -0x80, -0x80)));
        } else if constexpr (__x_to_x) {
            auto a = _mm_unpacklo_epi16(__v, __m128i());          // 0o.o 1o.o
            auto b = _mm_unpackhi_epi16(__v, __m128i());          // 2o.o 3o.o
            auto c = _mm_unpacklo_epi16(a, b);                    // 02oo ..oo
            auto d = _mm_unpackhi_epi16(a, b);                    // 13oo ..oo
            return __intrin_bitcast<_To>(_mm_unpacklo_epi16(c, d));  // 0123 oooo
        } else if constexpr (__y_to_x && __have_avx512vl) {
            return __intrin_bitcast<_To>(_mm256_cvtepi32_epi16(__v));
        } else if constexpr (__y_to_x && __have_avx512f) {
            return __intrin_bitcast<_To>(__lo128(_mm512_cvtepi32_epi16(__auto_bitcast(__v))));
        } else if constexpr (__y_to_x) {
            auto a = _mm256_shuffle_epi8(
                __v,
                _mm256_setr_epi8(0, 1, 4, 5, 8, 9, 12, 13, -0x80, -0x80, -0x80, -0x80,
                                 -0x80, -0x80, -0x80, -0x80, 0, 1, 4, 5, 8, 9, 12, 13,
                                 -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80));
            return __intrin_bitcast<_To>(
                __lo128(_mm256_permute4x64_epi64(a, 0xf8)));  // a[0] a[2] | a[3] a[3]
        } else if constexpr (__z_to_y) {
            return __intrin_bitcast<_To>(_mm512_cvtepi32_epi16(__v));
        }
    } else if constexpr (i32_to_i8) {   //{{{2
        if constexpr (__x_to_x && __have_avx512vl) {
            return __intrin_bitcast<_To>(_mm_cvtepi32_epi8(__v));
        } else if constexpr (__x_to_x && __have_avx512f) {
            return __intrin_bitcast<_To>(__lo128(_mm512_cvtepi32_epi8(__zero_extend(__v.intrin()))));
        } else if constexpr (__x_to_x && __have_ssse3) {
            return __intrin_bitcast<_To>(_mm_shuffle_epi8(
                __v, _mm_setr_epi8(0, 4, 8, 12, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
                                   -0x80, -0x80, -0x80, -0x80, -0x80, -0x80)));
        } else if constexpr (__x_to_x) {
            const auto a = _mm_unpacklo_epi8(__v, __v);  // 0... .... 1... ....
            const auto b = _mm_unpackhi_epi8(__v, __v);  // 2... .... 3... ....
            const auto c = _mm_unpacklo_epi8(a, b);  // 02.. .... .... ....
            const auto d = _mm_unpackhi_epi8(a, b);  // 13.. .... .... ....
            const auto e = _mm_unpacklo_epi8(c, d);  // 0123 .... .... ....
            return __intrin_bitcast<_To>(e & _mm_cvtsi32_si128(-1));
        } else if constexpr (__y_to_x && __have_avx512vl) {
            return __intrin_bitcast<_To>(_mm256_cvtepi32_epi8(__v));
        } else if constexpr (__y_to_x && __have_avx512f) {
            return __intrin_bitcast<_To>(_mm512_cvtepi32_epi8(__zero_extend(__v.intrin())));
        } else if constexpr (__z_to_x) {
            return __intrin_bitcast<_To>(_mm512_cvtepi32_epi8(__v));
        }
    } else if constexpr (i16_to_i64) {  //{{{2
        if constexpr (__x_to_x && __have_sse4_1) {
            return __intrin_bitcast<_To>(is_signed_v<_T> ? _mm_cvtepi16_epi64(__v) : _mm_cvtepu16_epi64(__v));
        } else if constexpr (__x_to_x && is_signed_v<_T>) {
            auto x = _mm_srai_epi16(__v, 15);
            auto y = _mm_unpacklo_epi16(__v, x);
            x = _mm_unpacklo_epi16(x, x);
            return __intrin_bitcast<_To>(_mm_unpacklo_epi32(y, x));
        } else if constexpr (__x_to_x) {
            return __intrin_bitcast<_To>(_mm_unpacklo_epi32(_mm_unpacklo_epi16(__v, __m128i()), __m128i()));
        } else if constexpr (__x_to_y) {
            return __intrin_bitcast<_To>(is_signed_v<_T> ? _mm256_cvtepi16_epi64(__v) : _mm256_cvtepu16_epi64(__v));
        } else if constexpr (__x_to_z) {
            return __intrin_bitcast<_To>(is_signed_v<_T> ? _mm512_cvtepi16_epi64(__v) : _mm512_cvtepu16_epi64(__v));
        }
    } else if constexpr (i16_to_i32) {  //{{{2
        if constexpr (__x_to_x && __have_sse4_1) {
            return __intrin_bitcast<_To>(is_signed_v<_T> ? _mm_cvtepi16_epi32(__v) : _mm_cvtepu16_epi32(__v));
        } else if constexpr (__x_to_x && is_signed_v<_T>) {
            return __intrin_bitcast<_To>(_mm_srai_epi32(_mm_unpacklo_epi16(__v, __v), 16));
        } else if constexpr (__x_to_x && is_unsigned_v<_T>) {
            return __intrin_bitcast<_To>(_mm_unpacklo_epi16(__v, __m128i()));
        } else if constexpr (__x_to_y) {
            return __intrin_bitcast<_To>(is_signed_v<_T> ? _mm256_cvtepi16_epi32(__v) : _mm256_cvtepu16_epi32(__v));
        } else if constexpr (__y_to_z) {
            return __intrin_bitcast<_To>(is_signed_v<_T> ? _mm512_cvtepi16_epi32(__v) : _mm512_cvtepu16_epi32(__v));
        }
    } else if constexpr (i16_to_i8) {   //{{{2
        if constexpr (__x_to_x && __have_avx512bw_vl) {
            return __intrin_bitcast<_To>(_mm_cvtepi16_epi8(__v));
        } else if constexpr (__x_to_x && __have_avx512bw) {
            return __intrin_bitcast<_To>(__lo128(_mm512_cvtepi16_epi8(__zero_extend(__v.intrin()))));
        } else if constexpr (__x_to_x && __have_ssse3) {
            return __intrin_bitcast<_To>(_mm_shuffle_epi8(
                __v, _mm_setr_epi8(0, 2, 4, 6, 8, 10, 12, 14, -0x80, -0x80, -0x80, -0x80,
                                   -0x80, -0x80, -0x80, -0x80)));
        } else if constexpr (__x_to_x) {
            auto a = _mm_unpacklo_epi8(__v, __v);  // 00.. 11.. 22.. 33..
            auto b = _mm_unpackhi_epi8(__v, __v);  // 44.. 55.. 66.. 77..
            auto c = _mm_unpacklo_epi8(a, b);  // 0404 .... 1515 ....
            auto d = _mm_unpackhi_epi8(a, b);  // 2626 .... 3737 ....
            auto e = _mm_unpacklo_epi8(c, d);  // 0246 0246 .... ....
            auto f = _mm_unpackhi_epi8(c, d);  // 1357 1357 .... ....
            return __intrin_bitcast<_To>(_mm_unpacklo_epi8(e, f));
        } else if constexpr (__y_to_x && __have_avx512bw_vl) {
            return __intrin_bitcast<_To>(_mm256_cvtepi16_epi8(__v));
        } else if constexpr (__y_to_x && __have_avx512bw) {
            return __intrin_bitcast<_To>(__lo256(_mm512_cvtepi16_epi8(__zero_extend(__v.intrin()))));
        } else if constexpr (__y_to_x) {
            auto a = _mm256_shuffle_epi8(
                __v,
                _mm256_setr_epi8(0, 2, 4, 6, 8, 10, 12, 14, -0x80, -0x80, -0x80, -0x80,
                                 -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
                                 -0x80, -0x80, -0x80, -0x80, 0, 2, 4, 6, 8, 10, 12, 14));
            return __intrin_bitcast<_To>(__lo128(a) | __hi128(a));
        } else if constexpr (__z_to_y && __have_avx512bw) {
            return __intrin_bitcast<_To>(_mm512_cvtepi16_epi8(__v));
        } else if constexpr (__z_to_y)  {
            __assert_unreachable<_T>();
        }
    } else if constexpr (i8_to_i64) {  //{{{2
        if constexpr (__x_to_x && __have_sse4_1) {
            return __intrin_bitcast<_To>(is_signed_v<_T> ? _mm_cvtepi8_epi64(__v) : _mm_cvtepu8_epi64(__v));
        } else if constexpr (__x_to_x && is_signed_v<_T>) {
            if constexpr (__have_ssse3) {
                auto dup = _mm_unpacklo_epi8(__v, __v);
                auto epi16 = _mm_srai_epi16(dup, 8);
                _mm_shuffle_epi8(
                    epi16, _mm_setr_epi8(0, 1, 1, 1, 1, 1, 1, 1, 2, 3, 3, 3, 3, 3, 3, 3));
            } else {
                auto x = _mm_unpacklo_epi8(__v, __v);
                x = _mm_unpacklo_epi16(x, x);
                return __intrin_bitcast<_To>(
                    _mm_unpacklo_epi32(_mm_srai_epi32(x, 24), _mm_srai_epi32(x, 31)));
            }
        } else if constexpr (__x_to_x) {
            return __intrin_bitcast<_To>(_mm_unpacklo_epi32(
                _mm_unpacklo_epi16(_mm_unpacklo_epi8(__v, __m128i()), __m128i()),
                __m128i()));
        } else if constexpr (__x_to_y) {
            return __intrin_bitcast<_To>(is_signed_v<_T> ? _mm256_cvtepi8_epi64(__v) : _mm256_cvtepu8_epi64(__v));
        } else if constexpr (__x_to_z) {
            return __intrin_bitcast<_To>(is_signed_v<_T> ? _mm512_cvtepi8_epi64(__v) : _mm512_cvtepu8_epi64(__v));
        }
    } else if constexpr (i8_to_i32) {  //{{{2
        if constexpr (__x_to_x && __have_sse4_1) {
            return __intrin_bitcast<_To>(is_signed_v<_T> ? _mm_cvtepi8_epi32(__v) : _mm_cvtepu8_epi32(__v));
        } else if constexpr (__x_to_x && is_signed_v<_T>) {
            const auto x = _mm_unpacklo_epi8(__v, __v);
            return __intrin_bitcast<_To>(_mm_srai_epi32(_mm_unpacklo_epi16(x, x), 24));
        } else if constexpr (__x_to_x && is_unsigned_v<_T>) {
            return __intrin_bitcast<_To>(_mm_unpacklo_epi16(_mm_unpacklo_epi8(__v, __m128i()), __m128i()));
        } else if constexpr (__x_to_y) {
            return __intrin_bitcast<_To>(is_signed_v<_T> ? _mm256_cvtepi8_epi32(__v) : _mm256_cvtepu8_epi32(__v));
        } else if constexpr (__x_to_z) {
            return __intrin_bitcast<_To>(is_signed_v<_T> ? _mm512_cvtepi8_epi32(__v) : _mm512_cvtepu8_epi32(__v));
        }
    } else if constexpr (i8_to_i16) {   //{{{2
        if constexpr (__x_to_x && __have_sse4_1) {
            return __intrin_bitcast<_To>(is_signed_v<_T> ? _mm_cvtepi8_epi16(__v) : _mm_cvtepu8_epi16(__v));
        } else if constexpr (__x_to_x && is_signed_v<_T>) {
            return __intrin_bitcast<_To>(_mm_srai_epi16(_mm_unpacklo_epi8(__v, __v), 8));
        } else if constexpr (__x_to_x && is_unsigned_v<_T>) {
            return __intrin_bitcast<_To>(_mm_unpacklo_epi8(__v, __m128i()));
        } else if constexpr (__x_to_y) {
            return __intrin_bitcast<_To>(is_signed_v<_T> ? _mm256_cvtepi8_epi16(__v) : _mm256_cvtepu8_epi16(__v));
        } else if constexpr (__y_to_z && __have_avx512bw) {
            return __intrin_bitcast<_To>(is_signed_v<_T> ? _mm512_cvtepi8_epi16(__v) : _mm512_cvtepu8_epi16(__v));
        } else if constexpr (__y_to_z) {
            __assert_unreachable<_T>();
        }
    } else if constexpr (f32_to_s64) {  //{{{2
        if constexpr (__have_avx512dq_vl && __x_to_x) {
            return __intrin_bitcast<_To>(_mm_cvttps_epi64(__v));
        } else if constexpr (__have_avx512dq_vl && __x_to_y) {
            return __intrin_bitcast<_To>(_mm256_cvttps_epi64(__v));
        } else if constexpr (__have_avx512dq && __y_to_z) {
            return __intrin_bitcast<_To>(_mm512_cvttps_epi64(__v));
        } // else use scalar fallback
    } else if constexpr (f32_to_u64) {  //{{{2
        if constexpr (__have_avx512dq_vl && __x_to_x) {
            return __intrin_bitcast<_To>(_mm_cvttps_epu64(__v));
        } else if constexpr (__have_avx512dq_vl && __x_to_y) {
            return __intrin_bitcast<_To>(_mm256_cvttps_epu64(__v));
        } else if constexpr (__have_avx512dq && __y_to_z) {
            return __intrin_bitcast<_To>(_mm512_cvttps_epu64(__v));
        } // else use scalar fallback
    } else if constexpr (f32_to_s32) {  //{{{2
        if constexpr (__x_to_x || __y_to_y || __z_to_z) {
            // go to fallback, it does the right thing
        } else {
            __assert_unreachable<_T>();
        }
    } else if constexpr (f32_to_u32) {  //{{{2
        // the __builtin_constant_p hack enables constant propagation
        if constexpr (__have_avx512vl && __x_to_x) {
            const __vector_type_t<float, 4> x = __v.d;
            return __builtin_constant_p(x) ? __make_builtin<_U>(x[0], x[1], x[2], x[3])
                                           : __vector_bitcast<_U>(_mm_cvttps_epu32(__v));
        } else if constexpr (__have_avx512f && __x_to_x) {
            const __vector_type_t<float, 4> x = __v.d;
            return __builtin_constant_p(x)
                       ? __make_builtin<_U>(x[0], x[1], x[2], x[3])
                       : __vector_bitcast<_U>(__lo128(_mm512_cvttps_epu32(__auto_bitcast(__v))));
        } else if constexpr (__have_avx512vl && __y_to_y) {
            const __vector_type_t<float, 8> x = __v.d;
            return __builtin_constant_p(x) ? __make_builtin<_U>(x[0], x[1], x[2], x[3],
                                                                x[4], x[5], x[6], x[7])
                                           : __vector_bitcast<_U>(_mm256_cvttps_epu32(__v));
        } else if constexpr (__have_avx512f && __y_to_y) {
            const __vector_type_t<float, 8> x = __v.d;
            return __builtin_constant_p(x)
                       ? __make_builtin<_U>(x[0], x[1], x[2], x[3], x[4], x[5], x[6],
                                            x[7])
                       : __vector_bitcast<_U>(__lo256(_mm512_cvttps_epu32(__auto_bitcast(__v))));
        } else if constexpr (__x_to_x || __y_to_y || __z_to_z) {
            // go to fallback, it does the right thing. We can't use the _mm_floor_ps -
            // 0x8000'0000 trick for f32->u32 because it would discard small input values
            // (only 24 mantissa bits)
        } else {
            __assert_unreachable<_T>();
        }
    } else if constexpr (f32_to_ibw) {  //{{{2
        return __convert_x86<_To>(__convert_x86<__vector_type_t<int, _N>>(__v));
    } else if constexpr (f64_to_s64) {  //{{{2
        if constexpr (__have_avx512dq_vl && __x_to_x) {
            return __intrin_bitcast<_To>(_mm_cvttpd_epi64(__v));
        } else if constexpr (__have_avx512dq_vl && __y_to_y) {
            return __intrin_bitcast<_To>(_mm256_cvttpd_epi64(__v));
        } else if constexpr (__have_avx512dq && __z_to_z) {
            return __intrin_bitcast<_To>(_mm512_cvttpd_epi64(__v));
        } // else use scalar fallback
    } else if constexpr (f64_to_u64) {  //{{{2
        if constexpr (__have_avx512dq_vl && __x_to_x) {
            return __intrin_bitcast<_To>(_mm_cvttpd_epu64(__v));
        } else if constexpr (__have_avx512dq_vl && __y_to_y) {
            return __intrin_bitcast<_To>(_mm256_cvttpd_epu64(__v));
        } else if constexpr (__have_avx512dq && __z_to_z) {
            return __intrin_bitcast<_To>(_mm512_cvttpd_epu64(__v));
        } // else use scalar fallback
    } else if constexpr (f64_to_s32) {  //{{{2
        if constexpr (__x_to_x) {
            return __intrin_bitcast<_To>(_mm_cvttpd_epi32(__v));
        } else if constexpr (__y_to_x) {
            return __intrin_bitcast<_To>(_mm256_cvttpd_epi32(__v));
        } else if constexpr (__z_to_y) {
            return __intrin_bitcast<_To>(_mm512_cvttpd_epi32(__v));
        }
    } else if constexpr (f64_to_u32) {  //{{{2
        if constexpr (__have_avx512vl && __x_to_x) {
            return __intrin_bitcast<_To>(_mm_cvttpd_epu32(__v));
        } else if constexpr (__have_sse4_1 && __x_to_x) {
            return __vector_bitcast<_U>(_mm_cvttpd_epi32(_mm_floor_pd(__v) - 0x8000'0000u)) ^
                   0x8000'0000u;
        } else if constexpr (__x_to_x) {
            // use scalar fallback: it's only 2 values to convert, can't get much better
            // than scalar decomposition
        } else if constexpr (__have_avx512vl && __y_to_x) {
            return __intrin_bitcast<_To>(_mm256_cvttpd_epu32(__v));
        } else if constexpr (__y_to_x) {
            return __intrin_bitcast<_To>(__vector_bitcast<_U>(_mm256_cvttpd_epi32(
                                          _mm256_floor_pd(__v) - 0x8000'0000u)) ^
                                      0x8000'0000u);
        } else if constexpr (__z_to_y) {
            return __intrin_bitcast<_To>(_mm512_cvttpd_epu32(__v));
        }
    } else if constexpr (f64_to_ibw) {  //{{{2
        return __convert_x86<_To>(__convert_x86<__vector_type_t<int, (_N < 4 ? 4 : _N)>>(__v));
    } else if constexpr (s64_to_f32) {  //{{{2
        if constexpr (__x_to_x && __have_avx512dq_vl) {
            return __intrin_bitcast<_To>(_mm_cvtepi64_ps(__v));
        } else if constexpr (__y_to_x && __have_avx512dq_vl) {
            return __intrin_bitcast<_To>(_mm256_cvtepi64_ps(__v));
        } else if constexpr (__z_to_y && __have_avx512dq) {
            return __intrin_bitcast<_To>(_mm512_cvtepi64_ps(__v));
        } else if constexpr (__z_to_y) {
            return __intrin_bitcast<_To>(_mm512_cvtpd_ps(__convert_x86<__vector_type_t<double, 8>>(__v)));
        }
    } else if constexpr (u64_to_f32) {  //{{{2
        if constexpr (__x_to_x && __have_avx512dq_vl) {
            return __intrin_bitcast<_To>(_mm_cvtepu64_ps(__v));
        } else if constexpr (__y_to_x && __have_avx512dq_vl) {
            return __intrin_bitcast<_To>(_mm256_cvtepu64_ps(__v));
        } else if constexpr (__z_to_y && __have_avx512dq) {
            return __intrin_bitcast<_To>(_mm512_cvtepu64_ps(__v));
        } else if constexpr (__z_to_y) {
            return __intrin_bitcast<_To>(
                __lo256(_mm512_cvtepu32_ps(
                    __auto_bitcast(_mm512_cvtepi64_epi32(_mm512_srai_epi64(__v, 32))))) *
                    0x100000000LL +
                __lo256(_mm512_cvtepu32_ps(__auto_bitcast(_mm512_cvtepi64_epi32(__v)))));
        }
    } else if constexpr (s32_to_f32) {  //{{{2
        // use fallback (builtin conversion)
    } else if constexpr (u32_to_f32) {  //{{{2
        if constexpr(__x_to_x && __have_avx512vl) {
            // use fallback
        } else if constexpr(__x_to_x && __have_avx512f) {
            return __intrin_bitcast<_To>(__lo128(_mm512_cvtepu32_ps(__auto_bitcast(__v))));
        } else if constexpr(__x_to_x && (__have_fma || __have_fma4)) {
            // work around PR85819
            return 0x10000 * _mm_cvtepi32_ps(__to_intrin(__vv >> 16)) +
                   _mm_cvtepi32_ps(__to_intrin(__vv & 0xffff));
        } else if constexpr(__y_to_y && __have_avx512vl) {
            // use fallback
        } else if constexpr(__y_to_y && __have_avx512f) {
            return __intrin_bitcast<_To>(__lo256(_mm512_cvtepu32_ps(__auto_bitcast(__v))));
        } else if constexpr(__y_to_y) {
            // work around PR85819
            return 0x10000 * _mm256_cvtepi32_ps(__to_intrin(__vv >> 16)) +
                   _mm256_cvtepi32_ps(__to_intrin(__vv & 0xffff));
        } // else use fallback (builtin conversion)
    } else if constexpr (ibw_to_f32) {  //{{{2
        if constexpr (_M == 4 || __have_avx2) {
            return __convert_x86<_To>(__convert_x86<__vector_type_t<int, _M>>(__v));
        } else {
            static_assert(__x_to_y);
            __m128i a, b;
            if constexpr (__have_sse4_1) {
                a = sizeof(_T) == 2
                        ? (is_signed_v<_T> ? _mm_cvtepi16_epi32(__v) : _mm_cvtepu16_epi32(__v))
                        : (is_signed_v<_T> ? _mm_cvtepi8_epi32(__v) : _mm_cvtepu8_epi32(__v));
                const auto w = _mm_shuffle_epi32(__v, sizeof(_T) == 2 ? 0xee : 0xe9);
                b = sizeof(_T) == 2
                        ? (is_signed_v<_T> ? _mm_cvtepi16_epi32(w) : _mm_cvtepu16_epi32(w))
                        : (is_signed_v<_T> ? _mm_cvtepi8_epi32(w) : _mm_cvtepu8_epi32(w));
            } else {
                __m128i tmp;
                if constexpr (sizeof(_T) == 1) {
                    tmp = is_signed_v<_T> ? _mm_srai_epi16(_mm_unpacklo_epi8(__v, __v), 8):
                        _mm_unpacklo_epi8(__v, __m128i());
                } else {
                    static_assert(sizeof(_T) == 2);
                    tmp = __v;
                }
                a = is_signed_v<_T> ? _mm_srai_epi32(_mm_unpacklo_epi16(tmp, tmp), 16)
                                   : _mm_unpacklo_epi16(tmp, __m128i());
                b = is_signed_v<_T> ? _mm_srai_epi32(_mm_unpackhi_epi16(tmp, tmp), 16)
                                   : _mm_unpackhi_epi16(tmp, __m128i());
            }
            return __convert_x86<_To>(__vector_bitcast<int>(a), __vector_bitcast<int>(b));
        }
    } else if constexpr (s64_to_f64) {  //{{{2
        if constexpr (__x_to_x && __have_avx512dq_vl) {
            return __intrin_bitcast<_To>(_mm_cvtepi64_pd(__v));
        } else if constexpr (__y_to_y && __have_avx512dq_vl) {
            return __intrin_bitcast<_To>(_mm256_cvtepi64_pd(__v));
        } else if constexpr (__z_to_z && __have_avx512dq) {
            return __intrin_bitcast<_To>(_mm512_cvtepi64_pd(__v));
        } else if constexpr (__z_to_z) {
            return __intrin_bitcast<_To>(
                _mm512_cvtepi32_pd(_mm512_cvtepi64_epi32(__to_intrin(__vv >> 32))) *
                    0x100000000LL +
                _mm512_cvtepu32_pd(_mm512_cvtepi64_epi32(__v)));
        }
    } else if constexpr (u64_to_f64) {  //{{{2
        if constexpr (__x_to_x && __have_avx512dq_vl) {
            return __intrin_bitcast<_To>(_mm_cvtepu64_pd(__v));
        } else if constexpr (__y_to_y && __have_avx512dq_vl) {
            return __intrin_bitcast<_To>(_mm256_cvtepu64_pd(__v));
        } else if constexpr (__z_to_z && __have_avx512dq) {
            return __intrin_bitcast<_To>(_mm512_cvtepu64_pd(__v));
        } else if constexpr (__z_to_z) {
            return __intrin_bitcast<_To>(
                _mm512_cvtepu32_pd(_mm512_cvtepi64_epi32(__to_intrin(__vv >> 32))) *
                    0x100000000LL +
                _mm512_cvtepu32_pd(_mm512_cvtepi64_epi32(__v)));
        }
    } else if constexpr (s32_to_f64) {  //{{{2
        if constexpr (__x_to_x) {
            return __intrin_bitcast<_To>(_mm_cvtepi32_pd(__v));
        } else if constexpr (__x_to_y) {
            return __intrin_bitcast<_To>(_mm256_cvtepi32_pd(__v));
        } else if constexpr (__y_to_z) {
            return __intrin_bitcast<_To>(_mm512_cvtepi32_pd(__v));
        }
    } else if constexpr (u32_to_f64) {  //{{{2
        if constexpr (__x_to_x && __have_avx512vl) {
            return __intrin_bitcast<_To>(_mm_cvtepu32_pd(__v));
        } else if constexpr (__x_to_x && __have_avx512f) {
            return __intrin_bitcast<_To>(__lo128(_mm512_cvtepu32_pd(__auto_bitcast(__v))));
        } else if constexpr (__x_to_x) {
            return __intrin_bitcast<_To>(_mm_cvtepi32_pd(__to_intrin(__vv ^ 0x8000'0000u)) + 0x8000'0000u);
        } else if constexpr (__x_to_y && __have_avx512vl) {
            return __intrin_bitcast<_To>(_mm256_cvtepu32_pd(__v));
        } else if constexpr (__x_to_y && __have_avx512f) {
            return __intrin_bitcast<_To>(__lo256(_mm512_cvtepu32_pd(__auto_bitcast(__v))));
        } else if constexpr (__x_to_y) {
            return __intrin_bitcast<_To>(_mm256_cvtepi32_pd(__to_intrin(__vv ^ 0x8000'0000u)) + 0x8000'0000u);
        } else if constexpr (__y_to_z) {
            return __intrin_bitcast<_To>(_mm512_cvtepu32_pd(__v));
        }
    } else if constexpr (ibw_to_f64) {  //{{{2
        return __convert_x86<_To>(__convert_x86<__vector_type_t<int, std::max(size_t(4), _M)>>(__v));
    } else if constexpr (f32_to_f64) {  //{{{2
        if constexpr (__x_to_x) {
            return __intrin_bitcast<_To>(_mm_cvtps_pd(__v));
        } else if constexpr (__x_to_y) {
            return __intrin_bitcast<_To>(_mm256_cvtps_pd(__v));
        } else if constexpr (__y_to_z) {
            return __intrin_bitcast<_To>(_mm512_cvtps_pd(__v));
        }
    } else if constexpr (f64_to_f32) {  //{{{2
        if constexpr (__x_to_x) {
            return __intrin_bitcast<_To>(_mm_cvtpd_ps(__v));
        } else if constexpr (__y_to_x) {
            return __intrin_bitcast<_To>(_mm256_cvtpd_ps(__v));
        } else if constexpr (__z_to_y) {
            return __intrin_bitcast<_To>(_mm512_cvtpd_ps(__v));
        }
    } else {  //{{{2
        __assert_unreachable<_T>();
    }

    // fallback:{{{2
    return __vector_convert<_To>(__vv, make_index_sequence<std::min(_M, _N)>());
    //}}}
} // }}}
// 2-arg __convert_x86 {{{1
template <class _To, class _V, class _Traits> _GLIBCXX_SIMD_INTRINSIC _To __convert_x86(_V vv0, _V vv1)
{
    using _T = typename _Traits::value_type;
    constexpr size_t _N = _Traits::width;
    __storage<_T, _N> v0(vv0);
    __storage<_T, _N> v1(vv1);
    using _U = typename __vector_traits<_To>::value_type;
    constexpr size_t _M = __vector_traits<_To>::width;

    static_assert(
        2 * _N <= _M,
        "v1 would be discarded; use the one-argument __convert_x86 overload instead");

    // [xyz]_to_[xyz] {{{2
    constexpr bool __x_to_x = sizeof(v0) == 16 && sizeof(_To) == 16;
    constexpr bool __x_to_y = sizeof(v0) == 16 && sizeof(_To) == 32;
    constexpr bool __x_to_z = sizeof(v0) == 16 && sizeof(_To) == 64;
    constexpr bool __y_to_x = sizeof(v0) == 32 && sizeof(_To) == 16;
    constexpr bool __y_to_y = sizeof(v0) == 32 && sizeof(_To) == 32;
    constexpr bool __y_to_z = sizeof(v0) == 32 && sizeof(_To) == 64;
    constexpr bool __z_to_x = sizeof(v0) == 64 && sizeof(_To) == 16;
    constexpr bool __z_to_y = sizeof(v0) == 64 && sizeof(_To) == 32;
    constexpr bool __z_to_z = sizeof(v0) == 64 && sizeof(_To) == 64;

    // iX_to_iX {{{2
    constexpr bool __i_to_i = std::is_integral_v<_U> && std::is_integral_v<_T>;
    constexpr bool i8_to_i16  = __i_to_i && sizeof(_T) == 1 && sizeof(_U) == 2;
    constexpr bool i8_to_i32  = __i_to_i && sizeof(_T) == 1 && sizeof(_U) == 4;
    constexpr bool i8_to_i64  = __i_to_i && sizeof(_T) == 1 && sizeof(_U) == 8;
    constexpr bool i16_to_i8  = __i_to_i && sizeof(_T) == 2 && sizeof(_U) == 1;
    constexpr bool i16_to_i32 = __i_to_i && sizeof(_T) == 2 && sizeof(_U) == 4;
    constexpr bool i16_to_i64 = __i_to_i && sizeof(_T) == 2 && sizeof(_U) == 8;
    constexpr bool i32_to_i8  = __i_to_i && sizeof(_T) == 4 && sizeof(_U) == 1;
    constexpr bool i32_to_i16 = __i_to_i && sizeof(_T) == 4 && sizeof(_U) == 2;
    constexpr bool i32_to_i64 = __i_to_i && sizeof(_T) == 4 && sizeof(_U) == 8;
    constexpr bool i64_to_i8  = __i_to_i && sizeof(_T) == 8 && sizeof(_U) == 1;
    constexpr bool i64_to_i16 = __i_to_i && sizeof(_T) == 8 && sizeof(_U) == 2;
    constexpr bool i64_to_i32 = __i_to_i && sizeof(_T) == 8 && sizeof(_U) == 4;

    // [fsu]X_to_[fsu]X {{{2
    // ibw = integral && byte or word, i.e. char and short with any signedness
    constexpr bool i64_to_f32 = is_integral_v<_T> &&                     sizeof(_T) == 8 && is_floating_point_v<_U> && sizeof(_U) == 4;
    constexpr bool s32_to_f32 = is_integral_v<_T> &&   is_signed_v<_T> && sizeof(_T) == 4 && is_floating_point_v<_U> && sizeof(_U) == 4;
    constexpr bool s16_to_f32 = is_integral_v<_T> &&   is_signed_v<_T> && sizeof(_T) == 2 && is_floating_point_v<_U> && sizeof(_U) == 4;
    constexpr bool  s8_to_f32 = is_integral_v<_T> &&   is_signed_v<_T> && sizeof(_T) == 1 && is_floating_point_v<_U> && sizeof(_U) == 4;
    constexpr bool u32_to_f32 = is_integral_v<_T> && is_unsigned_v<_T> && sizeof(_T) == 4 && is_floating_point_v<_U> && sizeof(_U) == 4;
    constexpr bool u16_to_f32 = is_integral_v<_T> && is_unsigned_v<_T> && sizeof(_T) == 2 && is_floating_point_v<_U> && sizeof(_U) == 4;
    constexpr bool  u8_to_f32 = is_integral_v<_T> && is_unsigned_v<_T> && sizeof(_T) == 1 && is_floating_point_v<_U> && sizeof(_U) == 4;
    constexpr bool s64_to_f64 = is_integral_v<_T> &&   is_signed_v<_T> && sizeof(_T) == 8 && is_floating_point_v<_U> && sizeof(_U) == 8;
    constexpr bool s32_to_f64 = is_integral_v<_T> &&   is_signed_v<_T> && sizeof(_T) == 4 && is_floating_point_v<_U> && sizeof(_U) == 8;
    constexpr bool s16_to_f64 = is_integral_v<_T> &&   is_signed_v<_T> && sizeof(_T) == 2 && is_floating_point_v<_U> && sizeof(_U) == 8;
    constexpr bool  s8_to_f64 = is_integral_v<_T> &&   is_signed_v<_T> && sizeof(_T) == 1 && is_floating_point_v<_U> && sizeof(_U) == 8;
    constexpr bool u64_to_f64 = is_integral_v<_T> && is_unsigned_v<_T> && sizeof(_T) == 8 && is_floating_point_v<_U> && sizeof(_U) == 8;
    constexpr bool u32_to_f64 = is_integral_v<_T> && is_unsigned_v<_T> && sizeof(_T) == 4 && is_floating_point_v<_U> && sizeof(_U) == 8;
    constexpr bool u16_to_f64 = is_integral_v<_T> && is_unsigned_v<_T> && sizeof(_T) == 2 && is_floating_point_v<_U> && sizeof(_U) == 8;
    constexpr bool  u8_to_f64 = is_integral_v<_T> && is_unsigned_v<_T> && sizeof(_T) == 1 && is_floating_point_v<_U> && sizeof(_U) == 8;
    constexpr bool f32_to_s64 = is_integral_v<_U> &&   is_signed_v<_U> && sizeof(_U) == 8 && is_floating_point_v<_T> && sizeof(_T) == 4;
    constexpr bool f32_to_s32 = is_integral_v<_U> &&   is_signed_v<_U> && sizeof(_U) == 4 && is_floating_point_v<_T> && sizeof(_T) == 4;
    constexpr bool f32_to_u64 = is_integral_v<_U> && is_unsigned_v<_U> && sizeof(_U) == 8 && is_floating_point_v<_T> && sizeof(_T) == 4;
    constexpr bool f32_to_u32 = is_integral_v<_U> && is_unsigned_v<_U> && sizeof(_U) == 4 && is_floating_point_v<_T> && sizeof(_T) == 4;
    constexpr bool f64_to_s64 = is_integral_v<_U> &&   is_signed_v<_U> && sizeof(_U) == 8 && is_floating_point_v<_T> && sizeof(_T) == 8;
    constexpr bool f64_to_s32 = is_integral_v<_U> &&   is_signed_v<_U> && sizeof(_U) == 4 && is_floating_point_v<_T> && sizeof(_T) == 8;
    constexpr bool f64_to_u64 = is_integral_v<_U> && is_unsigned_v<_U> && sizeof(_U) == 8 && is_floating_point_v<_T> && sizeof(_T) == 8;
    constexpr bool f64_to_u32 = is_integral_v<_U> && is_unsigned_v<_U> && sizeof(_U) == 4 && is_floating_point_v<_T> && sizeof(_T) == 8;
    constexpr bool f32_to_ibw = is_integral_v<_U> && sizeof(_U) <= 2 && is_floating_point_v<_T> && sizeof(_T) == 4;
    constexpr bool f64_to_ibw = is_integral_v<_U> && sizeof(_U) <= 2 && is_floating_point_v<_T> && sizeof(_T) == 8;
    constexpr bool f32_to_f64 = is_floating_point_v<_T> && sizeof(_T) == 4 && is_floating_point_v<_U> && sizeof(_U) == 8;
    constexpr bool f64_to_f32 = is_floating_point_v<_T> && sizeof(_T) == 8 && is_floating_point_v<_U> && sizeof(_U) == 4;

    if constexpr (__i_to_i && __y_to_x && !__have_avx2) {  //{{{2
        // <double, 4>, <double, 4> => <short, 8>
        return __convert_x86<_To>(__lo128(v0), __hi128(v0), __lo128(v1), __hi128(v1));
    } else if constexpr (__i_to_i) {  // assert ISA {{{2
        static_assert(__x_to_x || __have_avx2,
                      "integral conversions with ymm registers require AVX2");
        static_assert(__have_avx512bw || ((sizeof(_T) >= 4 || sizeof(v0) < 64) &&
                                        (sizeof(_U) >= 4 || sizeof(_To) < 64)),
                      "8/16-bit integers in zmm registers require AVX512BW");
        static_assert((sizeof(v0) < 64 && sizeof(_To) < 64) || __have_avx512f,
                      "integral conversions with ymm registers require AVX2");
    }
    // concat => use 1-arg __convert_x86 {{{2
    if constexpr ((sizeof(v0) == 16 && __have_avx2) ||
                  (sizeof(v0) == 16 && __have_avx && std::is_floating_point_v<_T>) ||
                  (sizeof(v0) == 32 && __have_avx512f && (sizeof(_T) >= 4 || __have_avx512bw))) {
        // The ISA can handle wider input registers, so concat and use one-arg
        // implementation. This reduces code duplication considerably.
        return __convert_x86<_To>(__concat(v0, v1));
    } else {  //{{{2
        // conversion using bit reinterpretation (or no conversion at all) should all go
        // through the concat branch above:
        static_assert(!(std::is_floating_point_v<_T> == std::is_floating_point_v<_U> &&
                        sizeof(_T) == sizeof(_U)));
        if constexpr (2 * _N < _M && sizeof(_To) > 16) {  // handle all zero extension{{{2
            constexpr size_t Min = 16 / sizeof(_U);
            return __zero_extend(
                __convert_x86<__vector_type_t<_U, (Min > 2 * _N) ? Min : 2 * _N>>(v0, v1));
        } else if constexpr (i64_to_i32) {  //{{{2
            if constexpr (__x_to_x) {
                return __auto_bitcast(_mm_shuffle_ps(__auto_bitcast(v0), __auto_bitcast(v1), 0x88));
            } else if constexpr (__y_to_y) {
                // AVX512F is not available (would concat otherwise)
                return __auto_bitcast(__xzyw(
                    _mm256_shuffle_ps(__auto_bitcast(v0), __auto_bitcast(v1), 0x88)));
                // alternative:
                // const auto v0_abxxcdxx = _mm256_shuffle_epi32(v0, 8);
                // const auto v1_efxxghxx = _mm256_shuffle_epi32(v1, 8);
                // const auto v_abefcdgh = _mm256_unpacklo_epi64(v0_abxxcdxx,
                // v1_efxxghxx); return _mm256_permute4x64_epi64(v_abefcdgh,
                // 0x01 * 0 + 0x04 * 2 + 0x10 * 1 + 0x40 * 3);  // abcdefgh
            } else if constexpr (__z_to_z) {
                return __intrin_bitcast<_To>(
                    __concat(_mm512_cvtepi64_epi32(v0), _mm512_cvtepi64_epi32(v1)));
            }
        } else if constexpr (i64_to_i16) {  //{{{2
            if constexpr (__x_to_x) {
                // AVX2 is not available (would concat otherwise)
                if constexpr (__have_sse4_1) {
                    return __intrin_bitcast<_To>(_mm_shuffle_epi8(
                        _mm_blend_epi16(v0, _mm_slli_si128(v1, 4), 0x44),
                        _mm_setr_epi8(0, 1, 8, 9, 4, 5, 12, 13, -0x80, -0x80, -0x80,
                                      -0x80, -0x80, -0x80, -0x80, -0x80)));
                } else {
                    return __vector_type_t<_U, _M>{_U(v0[0]), _U(v0[1]), _U(v1[0]), _U(v1[1])};
                }
            } else if constexpr (__y_to_x) {
                auto a = _mm256_unpacklo_epi16(v0, v1);  // 04.. .... 26.. ....
                auto b = _mm256_unpackhi_epi16(v0, v1);  // 15.. .... 37.. ....
                auto c = _mm256_unpacklo_epi16(a, b);    // 0145 .... 2367 ....
                return __intrin_bitcast<_To>(
                    _mm_unpacklo_epi32(__lo128(c), __hi128(c)));  // 0123 4567
            } else if constexpr (__z_to_y) {
                return __intrin_bitcast<_To>(
                    __concat(_mm512_cvtepi64_epi16(v0), _mm512_cvtepi64_epi16(v1)));
            }
        } else if constexpr (i64_to_i8) {  //{{{2
            if constexpr (__x_to_x && __have_sse4_1) {
                return __intrin_bitcast<_To>(_mm_shuffle_epi8(
                    _mm_blend_epi16(v0, _mm_slli_si128(v1, 4), 0x44),
                    _mm_setr_epi8(0, 8, 4, 12, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
                                  -0x80, -0x80, -0x80, -0x80, -0x80, -0x80)));
            } else if constexpr (__x_to_x && __have_ssse3) {
                return __intrin_bitcast<_To>(_mm_unpacklo_epi16(
                    _mm_shuffle_epi8(
                        v0, _mm_setr_epi8(0, 8, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
                                          -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
                                          -0x80)),
                    _mm_shuffle_epi8(
                        v1, _mm_setr_epi8(0, 8, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
                                          -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
                                          -0x80))));
            } else if constexpr (__x_to_x) {
                return __vector_type_t<_U, _M>{_U(v0[0]), _U(v0[1]), _U(v1[0]), _U(v1[1])};
            } else if constexpr (__y_to_x) {
                const auto a = _mm256_shuffle_epi8(
                    _mm256_blend_epi32(v0, _mm256_slli_epi64(v1, 32), 0xAA),
                    _mm256_setr_epi8(0, 8, -0x80, -0x80, 4, 12, -0x80, -0x80, -0x80,
                                     -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
                                     -0x80, -0x80, 0, 8, -0x80, -0x80, 4, 12, -0x80,
                                     -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80));
                return __intrin_bitcast<_To>(__lo128(a) | __hi128(a));
            } // __z_to_x uses concat fallback
        } else if constexpr (i32_to_i16) {  //{{{2
            if constexpr (__x_to_x) {
                // AVX2 is not available (would concat otherwise)
                if constexpr (__have_sse4_1) {
                    return __intrin_bitcast<_To>(
                        _mm_shuffle_epi8(_mm_blend_epi16(v0, _mm_slli_si128(v1, 2), 0xaa),
                                         _mm_setr_epi8(0, 1, 4, 5, 8, 9, 12, 13, 2, 3, 6,
                                                       7, 10, 11, 14, 15)));
                } else if constexpr (__have_ssse3) {
                    return __intrin_bitcast<_To>(
                        _mm_hadd_epi16(__to_intrin(vv0 << 16), __to_intrin(vv1 << 16)));
                    /*
                    return _mm_unpacklo_epi64(
                        _mm_shuffle_epi8(v0, _mm_setr_epi8(0, 1, 4, 5, 8, 9, 12, 13, 8, 9,
                                                           12, 13, 12, 13, 14, 15)),
                        _mm_shuffle_epi8(v1, _mm_setr_epi8(0, 1, 4, 5, 8, 9, 12, 13, 8, 9,
                                                           12, 13, 12, 13, 14, 15)));
                                                           */
                } else {
                    auto a = _mm_unpacklo_epi16(v0, v1);                  // 04.. 15..
                    auto b = _mm_unpackhi_epi16(v0, v1);                  // 26.. 37..
                    auto c = _mm_unpacklo_epi16(a, b);                    // 0246 ....
                    auto d = _mm_unpackhi_epi16(a, b);                    // 1357 ....
                    return __intrin_bitcast<_To>(_mm_unpacklo_epi16(c, d));  // 0123 4567
                }
            } else if constexpr (__y_to_y) {
                const auto shuf = _mm256_setr_epi8(
                    0, 1, 4, 5, 8, 9, 12, 13, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
                    -0x80, -0x80, 0, 1, 4, 5, 8, 9, 12, 13, -0x80, -0x80, -0x80, -0x80,
                    -0x80, -0x80, -0x80, -0x80);
                auto a = _mm256_shuffle_epi8(v0, shuf);
                auto b = _mm256_shuffle_epi8(v1, shuf);
                return __intrin_bitcast<_To>(__xzyw(_mm256_unpacklo_epi64(a, b)));
            } // __z_to_z uses concat fallback
        } else if constexpr (i32_to_i8) {  //{{{2
            if constexpr (__x_to_x && __have_ssse3) {
                const auto shufmask =
                    _mm_setr_epi8(0, 4, 8, 12, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
                                  -0x80, -0x80, -0x80, -0x80, -0x80, -0x80);
                return __intrin_bitcast<_To>(_mm_unpacklo_epi32(
                    _mm_shuffle_epi8(v0, shufmask), _mm_shuffle_epi8(v1, shufmask)));
            } else if constexpr (__x_to_x) {
                auto a = _mm_unpacklo_epi8(v0, v1);  // 04.. .... 15.. ....
                auto b = _mm_unpackhi_epi8(v0, v1);  // 26.. .... 37.. ....
                auto c = _mm_unpacklo_epi8(a, b);    // 0246 .... .... ....
                auto d = _mm_unpackhi_epi8(a, b);    // 1357 .... .... ....
                auto e = _mm_unpacklo_epi8(c, d);    // 0123 4567 .... ....
                return __intrin_bitcast<_To>(e & __m128i{-1, 0});
            } else if constexpr (__y_to_x) {
                const auto a = _mm256_shuffle_epi8(
                    _mm256_blend_epi16(v0, _mm256_slli_epi32(v1, 16), 0xAA),
                    _mm256_setr_epi8(0, 4, 8, 12, -0x80, -0x80, -0x80, -0x80, 2, 6, 10,
                                     14, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
                                     -0x80, 0, 4, 8, 12, -0x80, -0x80, -0x80, -0x80, 2, 6,
                                     10, 14));
                return __intrin_bitcast<_To>(__lo128(a) | __hi128(a));
            } // __z_to_y uses concat fallback
        } else if constexpr (i16_to_i8) {  //{{{2
            if constexpr (__x_to_x && __have_ssse3) {
                const auto shuf = reinterpret_cast<__m128i>(
                    __vector_type_t<__uchar, 16>{0, 2, 4, 6, 8, 10, 12, 14, 0x80, 0x80, 0x80,
                                              0x80, 0x80, 0x80, 0x80, 0x80});
                return __intrin_bitcast<_To>(_mm_unpacklo_epi64(_mm_shuffle_epi8(v0, shuf),
                                                             _mm_shuffle_epi8(v1, shuf)));
            } else if constexpr (__x_to_x) {
                auto a = _mm_unpacklo_epi8(v0, v1);  // 08.. 19.. 2A.. 3B..
                auto b = _mm_unpackhi_epi8(v0, v1);  // 4C.. 5D.. 6E.. 7F..
                auto c = _mm_unpacklo_epi8(a, b);    // 048C .... 159D ....
                auto d = _mm_unpackhi_epi8(a, b);    // 26AE .... 37BF ....
                auto e = _mm_unpacklo_epi8(c, d);    // 0246 8ACE .... ....
                auto f = _mm_unpackhi_epi8(c, d);    // 1357 9BDF .... ....
                return __intrin_bitcast<_To>(_mm_unpacklo_epi8(e, f));
            } else if constexpr (__y_to_y) {
                return __intrin_bitcast<_To>(__xzyw(_mm256_shuffle_epi8(
                    (v0.intrin() & _mm256_set1_epi32(0x00ff00ff)) |
                        _mm256_slli_epi16(v1, 8),
                    _mm256_setr_epi8(0, 2, 4, 6, 8, 10, 12, 14, 1, 3, 5, 7, 9, 11, 13, 15,
                                     0, 2, 4, 6, 8, 10, 12, 14, 1, 3, 5, 7, 9, 11, 13,
                                     15))));
            } // __z_to_z uses concat fallback
        } else if constexpr (i64_to_f32) {  //{{{2
            if constexpr (__x_to_x) {
                return __make_storage<float>(v0[0], v0[1], v1[0], v1[1]);
            } else if constexpr (__y_to_y) {
                static_assert(__y_to_y && __have_avx2);
                const auto a = _mm256_unpacklo_epi32(v0, v1);   // aeAE cgCG
                const auto b = _mm256_unpackhi_epi32(v0, v1);   // bfBF dhDH
                const auto lo32 = _mm256_unpacklo_epi32(a, b);  // abef cdgh
                const auto hi32 =
                    __vector_bitcast<conditional_t<is_signed_v<_T>, int, __uint>>(
                        _mm256_unpackhi_epi32(a, b));  // ABEF CDGH
                const auto hi = 0x100000000LL * __convert_x86<__vector_type_t<float, 8>>(hi32);
                const auto mid =
                    0x10000 * _mm256_cvtepi32_ps(_mm256_srli_epi32(lo32, 16));
                const auto lo = _mm256_cvtepi32_ps(_mm256_set1_epi32(0x0000ffffu) & lo32);
                return __xzyw((hi + mid) + lo);
            } else if constexpr (__z_to_z && __have_avx512dq) {
                return std::is_signed_v<_T> ? __concat(_mm512_cvtepi64_ps(v0),
                                                            _mm512_cvtepi64_ps(v1))
                                           : __concat(_mm512_cvtepu64_ps(v0),
                                                            _mm512_cvtepu64_ps(v1));
            } else if constexpr (__z_to_z && std::is_signed_v<_T>) {
                const __m512 hi32 = _mm512_cvtepi32_ps(
                    __concat(_mm512_cvtepi64_epi32(__to_intrin(vv0 >> 32)),
                                   _mm512_cvtepi64_epi32(__to_intrin(vv1 >> 32))));
                const __m512i lo32 =
                    __concat(_mm512_cvtepi64_epi32(v0), _mm512_cvtepi64_epi32(v1));
                // split low 32-bits, because if hi32 is a small negative number, the
                // 24-bit mantissa may lose important information if any of the high 8
                // bits of lo32 is set, leading to catastrophic cancelation in the FMA
                const __m512 hi16 =
                    _mm512_cvtepu32_ps(_mm512_set1_epi32(0xffff0000u) & lo32);
                const __m512 lo16 =
                    _mm512_cvtepi32_ps(_mm512_set1_epi32(0x0000ffffu) & lo32);
                return (hi32 * 0x100000000LL + hi16) + lo16;
            } else if constexpr (__z_to_z && std::is_unsigned_v<_T>) {
                return __intrin_bitcast<_To>(
                    _mm512_cvtepu32_ps(
                        __concat(_mm512_cvtepi64_epi32(_mm512_srai_epi64(v0, 32)),
                                 _mm512_cvtepi64_epi32(_mm512_srai_epi64(v1, 32)))) *
                        0x100000000LL +
                    _mm512_cvtepu32_ps(
                        __concat(_mm512_cvtepi64_epi32(v0), _mm512_cvtepi64_epi32(v1))));
            }
        } else if constexpr (f64_to_s32) {  //{{{2
            // use concat fallback
        } else if constexpr (f64_to_u32) {  //{{{2
            if constexpr (__x_to_x && __have_sse4_1) {
                return __vector_bitcast<_U>(_mm_unpacklo_epi64(
                           _mm_cvttpd_epi32(_mm_floor_pd(v0) - 0x8000'0000u),
                           _mm_cvttpd_epi32(_mm_floor_pd(v1) - 0x8000'0000u))) ^
                       0x8000'0000u;
                // without SSE4.1 just use the scalar fallback, it's only four values
            } else if constexpr (__y_to_y) {
                return __vector_bitcast<_U>(__concat(
                           _mm256_cvttpd_epi32(_mm256_floor_pd(v0) - 0x8000'0000u),
                           _mm256_cvttpd_epi32(_mm256_floor_pd(v1) - 0x8000'0000u))) ^
                       0x8000'0000u;
            } // __z_to_z uses fallback
        } else if constexpr (f64_to_ibw) {  //{{{2
            // one-arg f64_to_ibw goes via __storage<int, ?>. The fallback would go via two
            // independet conversions to __storage<_To> and subsequent interleaving. This is
            // better, because f64->i32 allows to combine v0 and v1 into one register:
            //if constexpr (__z_to_x || __y_to_x) {
            return __convert_x86<_To>(__convert_x86<__vector_type_t<int, _N * 2>>(v0, v1));
            //}
        } else if constexpr (f32_to_ibw) {  //{{{2
            return __convert_x86<_To>(__convert_x86<__vector_type_t<int, _N>>(v0),
                                     __convert_x86<__vector_type_t<int, _N>>(v1));
            //}}}
        }

        // fallback: {{{2
        if constexpr (sizeof(_To) >= 32) {
            // if _To is ymm or zmm, then __storage<_U, _M / 2> is xmm or ymm
            return __concat(__convert_x86<__vector_type_t<_U, _M / 2>>(v0),
                            __convert_x86<__vector_type_t<_U, _M / 2>>(v1));
        } else if constexpr (sizeof(_To) == 16) {
            const auto lo = __to_intrin(__convert_x86<_To>(v0));
            const auto hi = __to_intrin(__convert_x86<_To>(v1));
            if constexpr (sizeof(_U) * _N == 8) {
                if constexpr (is_floating_point_v<_U>) {
                    return __auto_bitcast(_mm_unpacklo_pd(__vector_bitcast<double>(lo),
                                                          __vector_bitcast<double>(hi)));
                } else {
                    return __intrin_bitcast<_To>(_mm_unpacklo_epi64(lo, hi));
                }
            } else if constexpr (sizeof(_U) * _N == 4) {
                if constexpr (is_floating_point_v<_U>) {
                    return __auto_bitcast(_mm_unpacklo_ps(__vector_bitcast<float>(lo),
                                                          __vector_bitcast<float>(hi)));
                } else {
                    return __intrin_bitcast<_To>(_mm_unpacklo_epi32(lo, hi));
                }
            } else if constexpr (sizeof(_U) * _N == 2) {
                return __intrin_bitcast<_To>(_mm_unpacklo_epi16(lo, hi));
            } else {
                __assert_unreachable<_T>();
            }
        } else {
            return __vector_convert<_To>(vv0, vv1, make_index_sequence<_N>());
        }  //}}}
    }
}//}}}1
// 4-arg __convert_x86 {{{1
template <class _To, class _V, class _Traits> _GLIBCXX_SIMD_INTRINSIC _To __convert_x86(_V vv0, _V vv1,_V vv2,_V vv3)
{
    using _T = typename _Traits::value_type;
    constexpr size_t _N = _Traits::width;
    __storage<_T, _N> v0(vv0);
    __storage<_T, _N> v1(vv1);
    __storage<_T, _N> v2(vv2);
    __storage<_T, _N> v3(vv3);
    using _U = typename __vector_traits<_To>::value_type;
    constexpr size_t _M = __vector_traits<_To>::width;

    static_assert(
        4 * _N <= _M,
        "v2/v3 would be discarded; use the two/one-argument __convert_x86 overload instead");

    // [xyz]_to_[xyz] {{{2
    constexpr bool __x_to_x = sizeof(v0) == 16 && sizeof(_To) == 16;
    constexpr bool __x_to_y = sizeof(v0) == 16 && sizeof(_To) == 32;
    constexpr bool __x_to_z = sizeof(v0) == 16 && sizeof(_To) == 64;
    constexpr bool __y_to_x = sizeof(v0) == 32 && sizeof(_To) == 16;
    constexpr bool __y_to_y = sizeof(v0) == 32 && sizeof(_To) == 32;
    constexpr bool __y_to_z = sizeof(v0) == 32 && sizeof(_To) == 64;
    constexpr bool __z_to_x = sizeof(v0) == 64 && sizeof(_To) == 16;
    constexpr bool __z_to_y = sizeof(v0) == 64 && sizeof(_To) == 32;
    constexpr bool __z_to_z = sizeof(v0) == 64 && sizeof(_To) == 64;

    // iX_to_iX {{{2
    constexpr bool __i_to_i = std::is_integral_v<_U> && std::is_integral_v<_T>;
    constexpr bool i8_to_i16  = __i_to_i && sizeof(_T) == 1 && sizeof(_U) == 2;
    constexpr bool i8_to_i32  = __i_to_i && sizeof(_T) == 1 && sizeof(_U) == 4;
    constexpr bool i8_to_i64  = __i_to_i && sizeof(_T) == 1 && sizeof(_U) == 8;
    constexpr bool i16_to_i8  = __i_to_i && sizeof(_T) == 2 && sizeof(_U) == 1;
    constexpr bool i16_to_i32 = __i_to_i && sizeof(_T) == 2 && sizeof(_U) == 4;
    constexpr bool i16_to_i64 = __i_to_i && sizeof(_T) == 2 && sizeof(_U) == 8;
    constexpr bool i32_to_i8  = __i_to_i && sizeof(_T) == 4 && sizeof(_U) == 1;
    constexpr bool i32_to_i16 = __i_to_i && sizeof(_T) == 4 && sizeof(_U) == 2;
    constexpr bool i32_to_i64 = __i_to_i && sizeof(_T) == 4 && sizeof(_U) == 8;
    constexpr bool i64_to_i8  = __i_to_i && sizeof(_T) == 8 && sizeof(_U) == 1;
    constexpr bool i64_to_i16 = __i_to_i && sizeof(_T) == 8 && sizeof(_U) == 2;
    constexpr bool i64_to_i32 = __i_to_i && sizeof(_T) == 8 && sizeof(_U) == 4;

    // [fsu]X_to_[fsu]X {{{2
    // ibw = integral && byte or word, i.e. char and short with any signedness
    constexpr bool i64_to_f32 = is_integral_v<_T> &&                     sizeof(_T) == 8 && is_floating_point_v<_U> && sizeof(_U) == 4;
    constexpr bool s32_to_f32 = is_integral_v<_T> &&   is_signed_v<_T> && sizeof(_T) == 4 && is_floating_point_v<_U> && sizeof(_U) == 4;
    constexpr bool s16_to_f32 = is_integral_v<_T> &&   is_signed_v<_T> && sizeof(_T) == 2 && is_floating_point_v<_U> && sizeof(_U) == 4;
    constexpr bool  s8_to_f32 = is_integral_v<_T> &&   is_signed_v<_T> && sizeof(_T) == 1 && is_floating_point_v<_U> && sizeof(_U) == 4;
    constexpr bool u32_to_f32 = is_integral_v<_T> && is_unsigned_v<_T> && sizeof(_T) == 4 && is_floating_point_v<_U> && sizeof(_U) == 4;
    constexpr bool u16_to_f32 = is_integral_v<_T> && is_unsigned_v<_T> && sizeof(_T) == 2 && is_floating_point_v<_U> && sizeof(_U) == 4;
    constexpr bool  u8_to_f32 = is_integral_v<_T> && is_unsigned_v<_T> && sizeof(_T) == 1 && is_floating_point_v<_U> && sizeof(_U) == 4;
    constexpr bool s64_to_f64 = is_integral_v<_T> &&   is_signed_v<_T> && sizeof(_T) == 8 && is_floating_point_v<_U> && sizeof(_U) == 8;
    constexpr bool s32_to_f64 = is_integral_v<_T> &&   is_signed_v<_T> && sizeof(_T) == 4 && is_floating_point_v<_U> && sizeof(_U) == 8;
    constexpr bool s16_to_f64 = is_integral_v<_T> &&   is_signed_v<_T> && sizeof(_T) == 2 && is_floating_point_v<_U> && sizeof(_U) == 8;
    constexpr bool  s8_to_f64 = is_integral_v<_T> &&   is_signed_v<_T> && sizeof(_T) == 1 && is_floating_point_v<_U> && sizeof(_U) == 8;
    constexpr bool u64_to_f64 = is_integral_v<_T> && is_unsigned_v<_T> && sizeof(_T) == 8 && is_floating_point_v<_U> && sizeof(_U) == 8;
    constexpr bool u32_to_f64 = is_integral_v<_T> && is_unsigned_v<_T> && sizeof(_T) == 4 && is_floating_point_v<_U> && sizeof(_U) == 8;
    constexpr bool u16_to_f64 = is_integral_v<_T> && is_unsigned_v<_T> && sizeof(_T) == 2 && is_floating_point_v<_U> && sizeof(_U) == 8;
    constexpr bool  u8_to_f64 = is_integral_v<_T> && is_unsigned_v<_T> && sizeof(_T) == 1 && is_floating_point_v<_U> && sizeof(_U) == 8;
    constexpr bool f32_to_s64 = is_integral_v<_U> &&   is_signed_v<_U> && sizeof(_U) == 8 && is_floating_point_v<_T> && sizeof(_T) == 4;
    constexpr bool f32_to_s32 = is_integral_v<_U> &&   is_signed_v<_U> && sizeof(_U) == 4 && is_floating_point_v<_T> && sizeof(_T) == 4;
    constexpr bool f32_to_u64 = is_integral_v<_U> && is_unsigned_v<_U> && sizeof(_U) == 8 && is_floating_point_v<_T> && sizeof(_T) == 4;
    constexpr bool f32_to_u32 = is_integral_v<_U> && is_unsigned_v<_U> && sizeof(_U) == 4 && is_floating_point_v<_T> && sizeof(_T) == 4;
    constexpr bool f64_to_s64 = is_integral_v<_U> &&   is_signed_v<_U> && sizeof(_U) == 8 && is_floating_point_v<_T> && sizeof(_T) == 8;
    constexpr bool f64_to_s32 = is_integral_v<_U> &&   is_signed_v<_U> && sizeof(_U) == 4 && is_floating_point_v<_T> && sizeof(_T) == 8;
    constexpr bool f64_to_u64 = is_integral_v<_U> && is_unsigned_v<_U> && sizeof(_U) == 8 && is_floating_point_v<_T> && sizeof(_T) == 8;
    constexpr bool f64_to_u32 = is_integral_v<_U> && is_unsigned_v<_U> && sizeof(_U) == 4 && is_floating_point_v<_T> && sizeof(_T) == 8;
    constexpr bool f32_to_ibw = is_integral_v<_U> && sizeof(_U) <= 2 && is_floating_point_v<_T> && sizeof(_T) == 4;
    constexpr bool f64_to_ibw = is_integral_v<_U> && sizeof(_U) <= 2 && is_floating_point_v<_T> && sizeof(_T) == 8;
    constexpr bool f32_to_f64 = is_floating_point_v<_T> && sizeof(_T) == 4 && is_floating_point_v<_U> && sizeof(_U) == 8;
    constexpr bool f64_to_f32 = is_floating_point_v<_T> && sizeof(_T) == 8 && is_floating_point_v<_U> && sizeof(_U) == 4;

    if constexpr (__i_to_i && __y_to_x && !__have_avx2) {  //{{{2
        // <double, 4>, <double, 4>, <double, 4>, <double, 4> => <char, 16>
        return __convert_x86<_To>(__lo128(v0), __hi128(v0), __lo128(v1), __hi128(v1),
                                 __lo128(v2), __hi128(v2), __lo128(v3), __hi128(v3));
    } else if constexpr (__i_to_i) {  // assert ISA {{{2
        static_assert(__x_to_x || __have_avx2,
                      "integral conversions with ymm registers require AVX2");
        static_assert(__have_avx512bw || ((sizeof(_T) >= 4 || sizeof(v0) < 64) &&
                                        (sizeof(_U) >= 4 || sizeof(_To) < 64)),
                      "8/16-bit integers in zmm registers require AVX512BW");
        static_assert((sizeof(v0) < 64 && sizeof(_To) < 64) || __have_avx512f,
                      "integral conversions with ymm registers require AVX2");
    }
    // concat => use 2-arg __convert_x86 {{{2
    if constexpr ((sizeof(v0) == 16 && __have_avx2) ||
                  (sizeof(v0) == 16 && __have_avx && std::is_floating_point_v<_T>) ||
                  (sizeof(v0) == 32 && __have_avx512f)) {
        // The ISA can handle wider input registers, so concat and use two-arg
        // implementation. This reduces code duplication considerably.
        return __convert_x86<_To>(__concat(v0, v1), __concat(v2, v3));
    } else {  //{{{2
        // conversion using bit reinterpretation (or no conversion at all) should all go
        // through the concat branch above:
        static_assert(!(std::is_floating_point_v<_T> == std::is_floating_point_v<_U> &&
                        sizeof(_T) == sizeof(_U)));
        if constexpr (4 * _N < _M && sizeof(_To) > 16) {  // handle all zero extension{{{2
            constexpr size_t Min = 16 / sizeof(_U);
            return __zero_extend(
                __convert_x86<__vector_type_t<_U, (Min > 4 * _N) ? Min : 4 * _N>>(v0, v1,
                                                                                 v2, v3));
        } else if constexpr (i64_to_i16) {  //{{{2
            if constexpr (__x_to_x && __have_sse4_1) {
                return __intrin_bitcast<_To>(_mm_shuffle_epi8(
                    _mm_blend_epi16(_mm_blend_epi16(v0, _mm_slli_si128(v1, 2), 0x22),
                                    _mm_blend_epi16(_mm_slli_si128(v2, 4),
                                                    _mm_slli_si128(v3, 6), 0x88),
                                    0xcc),
                    _mm_setr_epi8(0, 1, 8, 9, 2, 3, 10, 11, 4, 5, 12, 13, 6, 7, 14, 15)));
            } else if constexpr (__y_to_y) {
                return __intrin_bitcast<_To>(_mm256_shuffle_epi8(
                    __xzyw(_mm256_blend_epi16(
                        __auto_bitcast(_mm256_shuffle_ps(__vector_bitcast<float>(v0),
                                                      __vector_bitcast<float>(v2),
                                                      0x88)),  // 0.1. 8.9. 2.3. A.B.
                        __to_intrin(
                            __vector_bitcast<int>(_mm256_shuffle_ps(
                                __vector_bitcast<float>(v1), __vector_bitcast<float>(v3), 0x88))
                            << 16),      // .4.5 .C.D .6.7 .E.F
                        0xaa)            // 0415 8C9D 2637 AEBF
                                     ),  // 0415 2637 8C9D AEBF
                    _mm256_setr_epi8(0, 1, 4, 5, 8, 9, 12, 13, 2, 3, 6, 7, 10, 11, 14, 15,
                                     0, 1, 4, 5, 8, 9, 12, 13, 2, 3, 6, 7, 10, 11, 14,
                                     15)));
                /*
                auto a = _mm256_unpacklo_epi16(v0, v1);  // 04.. .... 26.. ....
                auto b = _mm256_unpackhi_epi16(v0, v1);  // 15.. .... 37.. ....
                auto c = _mm256_unpacklo_epi16(v2, v3);  // 8C.. .... AE.. ....
                auto d = _mm256_unpackhi_epi16(v2, v3);  // 9D.. .... BF.. ....
                auto e = _mm256_unpacklo_epi16(a, b);    // 0145 .... 2367 ....
                auto f = _mm256_unpacklo_epi16(c, d);    // 89CD .... ABEF ....
                auto g = _mm256_unpacklo_epi64(e, f);    // 0145 89CD 2367 ABEF
                return __concat(
                    _mm_unpacklo_epi32(__lo128(g), __hi128(g)),
                    _mm_unpackhi_epi32(__lo128(g), __hi128(g)));  // 0123 4567 89AB CDEF
                    */
            }  // else use fallback
        } else if constexpr (i64_to_i8) {  //{{{2
            if constexpr (__x_to_x) {
                // TODO: use fallback for now
            } else if constexpr (__y_to_x) {
                auto a =
                    _mm256_srli_epi32(_mm256_slli_epi32(v0, 24), 24) |
                    _mm256_srli_epi32(_mm256_slli_epi32(v1, 24), 16) |
                    _mm256_srli_epi32(_mm256_slli_epi32(v2, 24), 8) |
                    _mm256_slli_epi32(v3, 24);  // 048C .... 159D .... 26AE .... 37BF ....
                /*return _mm_shuffle_epi8(
                    _mm_blend_epi32(__lo128(a) << 32, __hi128(a), 0x5),
                    _mm_setr_epi8(4, 12, 0, 8, 5, 13, 1, 9, 6, 14, 2, 10, 7, 15, 3, 11));*/
                auto b = _mm256_unpackhi_epi64(a, a);  // 159D .... 159D .... 37BF .... 37BF ....
                auto c = _mm256_unpacklo_epi8(a, b);  // 0145 89CD .... .... 2367 ABEF .... ....
                return __intrin_bitcast<_To>(_mm_unpacklo_epi16(__lo128(c), __hi128(c)));  // 0123 4567 89AB CDEF
            }
        } else if constexpr (i32_to_i8) {  //{{{2
            if constexpr (__x_to_x) {
                if constexpr (__have_ssse3) {
                    const auto x0 =  __vector_bitcast<uint>(v0.d) & 0xff;
                    const auto x1 = (__vector_bitcast<uint>(v1.d) & 0xff) << 8;
                    const auto x2 = (__vector_bitcast<uint>(v2.d) & 0xff) << 16;
                    const auto x3 =  __vector_bitcast<uint>(v3.d)         << 24;
                    return __intrin_bitcast<_To>(
                        _mm_shuffle_epi8(__to_intrin(x0 | x1 | x2 | x3),
                                         _mm_setr_epi8(0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10,
                                                       14, 3, 7, 11, 15)));
                } else {
                    auto a = _mm_unpacklo_epi8(v0, v2);  // 08.. .... 19.. ....
                    auto b = _mm_unpackhi_epi8(v0, v2);  // 2A.. .... 3B.. ....
                    auto c = _mm_unpacklo_epi8(v1, v3);  // 4C.. .... 5D.. ....
                    auto d = _mm_unpackhi_epi8(v1, v3);  // 6E.. .... 7F.. ....
                    auto e = _mm_unpacklo_epi8(a, c);    // 048C .... .... ....
                    auto f = _mm_unpackhi_epi8(a, c);    // 159D .... .... ....
                    auto g = _mm_unpacklo_epi8(b, d);    // 26AE .... .... ....
                    auto h = _mm_unpackhi_epi8(b, d);    // 37BF .... .... ....
                    return __intrin_bitcast<_To>(_mm_unpacklo_epi8(
                        _mm_unpacklo_epi8(e, g),  // 0246 8ACE .... ....
                        _mm_unpacklo_epi8(f, h)   // 1357 9BDF .... ....
                        ));                       // 0123 4567 89AB CDEF
                }
            } else if constexpr (__y_to_y) {
                const auto a = _mm256_shuffle_epi8(
                    __to_intrin((__vector_bitcast<ushort>(_mm256_blend_epi16(
                                   v0, _mm256_slli_epi32(v1, 16), 0xAA)) &
                               0xff) |
                              (__vector_bitcast<ushort>(_mm256_blend_epi16(
                                   v2, _mm256_slli_epi32(v3, 16), 0xAA))
                               << 8)),
                    _mm256_setr_epi8(0, 4, 8, 12, 2, 6, 10, 14, 1, 5, 9, 13, 3, 7, 11, 15,
                                     0, 4, 8, 12, 2, 6, 10, 14, 1, 5, 9, 13, 3, 7, 11, 15));
                return __intrin_bitcast<_To>(_mm256_permutevar8x32_epi32(
                    a, _mm256_setr_epi32(0, 4, 1, 5, 2, 6, 3, 7)));
            }
        } else if constexpr (i64_to_f32) {  //{{{2
            // this branch is only relevant with AVX and w/o AVX2 (i.e. no ymm integers)
            if constexpr (__x_to_y) {
                return __make_storage<float>(v0[0], v0[1], v1[0], v1[1], v2[0], v2[1], v3[0], v3[1]);

                const auto a = _mm_unpacklo_epi32(v0, v1);   // acAC
                const auto b = _mm_unpackhi_epi32(v0, v1);   // bdBD
                const auto c = _mm_unpacklo_epi32(v2, v3);   // egEG
                const auto d = _mm_unpackhi_epi32(v2, v3);   // fhFH
                const auto lo32a = _mm_unpacklo_epi32(a, b);  // abcd
                const auto lo32b = _mm_unpacklo_epi32(c, d);  // efgh
                const auto hi32 =
                    __vector_bitcast<conditional_t<is_signed_v<_T>, int, __uint>>(
                        __concat(_mm_unpackhi_epi32(a, b),
                                 _mm_unpackhi_epi32(c, d)));  // ABCD EFGH
                const auto hi =
                    0x100000000LL * __convert_x86<__vector_type_t<float, 8>>(hi32);
                const auto mid =
                    0x10000 * _mm256_cvtepi32_ps(__concat(_mm_srli_epi32(lo32a, 16),
                                                          _mm_srli_epi32(lo32b, 16)));
                const auto lo =
                    _mm256_cvtepi32_ps(__concat(_mm_set1_epi32(0x0000ffffu) & lo32a,
                                                _mm_set1_epi32(0x0000ffffu) & lo32b));
                return (hi + mid) + lo;
            }
        } else if constexpr (f64_to_ibw) {  //{{{2
            return __convert_x86<_To>(__convert_x86<__vector_type_t<int, _N * 2>>(v0, v1),
                                     __convert_x86<__vector_type_t<int, _N * 2>>(v2, v3));
        } else if constexpr (f32_to_ibw) {  //{{{2
            return __convert_x86<_To>(__convert_x86<__vector_type_t<int, _N>>(v0),
                                     __convert_x86<__vector_type_t<int, _N>>(v1),
                                     __convert_x86<__vector_type_t<int, _N>>(v2),
                                     __convert_x86<__vector_type_t<int, _N>>(v3));
        }  //}}}

        // fallback: {{{2
        if constexpr (sizeof(_To) >= 32) {
            // if _To is ymm or zmm, then __storage<_U, _M / 2> is xmm or ymm
            return __concat(__convert_x86<__vector_type_t<_U, _M / 2>>(v0, v1),
                            __convert_x86<__vector_type_t<_U, _M / 2>>(v2, v3));
        } else if constexpr (sizeof(_To) == 16) {
            const auto lo = __to_intrin(__convert_x86<_To>(v0, v1));
            const auto hi = __to_intrin(__convert_x86<_To>(v2, v3));
            if constexpr (sizeof(_U) * _N * 2 == 8) {
                if constexpr (is_floating_point_v<_U>) {
                    return __auto_bitcast(_mm_unpacklo_pd(lo, hi));
                } else {
                    return __intrin_bitcast<_To>(_mm_unpacklo_epi64(lo, hi));
                }
            } else if constexpr (sizeof(_U) * _N * 2 == 4) {
                if constexpr (is_floating_point_v<_U>) {
                    return __auto_bitcast(_mm_unpacklo_ps(lo, hi));
                } else {
                    return __intrin_bitcast<_To>(_mm_unpacklo_epi32(lo, hi));
                }
            } else {
                __assert_unreachable<_T>();
            }
        } else {
            return __vector_convert<_To>(v0.d, v1.d, v2.d, v3.d,
                                         make_index_sequence<_N>());
        }  //}}}2
    }
}//}}}
// 8-arg __convert_x86 {{{1
template <class _To, class _V, class _Traits> _GLIBCXX_SIMD_INTRINSIC _To __convert_x86(_V vv0, _V vv1,_V vv2,_V vv3,_V vv4,_V vv5, _V vv6, _V vv7)
{
    using _T = typename _Traits::value_type;
    constexpr size_t _N = _Traits::width;
    __storage<_T, _N> v0(vv0);
    __storage<_T, _N> v1(vv1);
    __storage<_T, _N> v2(vv2);
    __storage<_T, _N> v3(vv3);
    __storage<_T, _N> v4(vv4);
    __storage<_T, _N> v5(vv5);
    __storage<_T, _N> v6(vv6);
    __storage<_T, _N> v7(vv7);
    using _U = typename __vector_traits<_To>::value_type;
    constexpr size_t _M = __vector_traits<_To>::width;

    static_assert(8 * _N <= _M, "v4-v7 would be discarded; use the four/two/one-argument "
                              "__convert_x86 overload instead");

    // [xyz]_to_[xyz] {{{2
    constexpr bool __x_to_x = sizeof(v0) == 16 && sizeof(_To) == 16;
    constexpr bool __x_to_y = sizeof(v0) == 16 && sizeof(_To) == 32;
    constexpr bool __x_to_z = sizeof(v0) == 16 && sizeof(_To) == 64;
    constexpr bool __y_to_x = sizeof(v0) == 32 && sizeof(_To) == 16;
    constexpr bool __y_to_y = sizeof(v0) == 32 && sizeof(_To) == 32;
    constexpr bool __y_to_z = sizeof(v0) == 32 && sizeof(_To) == 64;
    constexpr bool __z_to_x = sizeof(v0) == 64 && sizeof(_To) == 16;
    constexpr bool __z_to_y = sizeof(v0) == 64 && sizeof(_To) == 32;
    constexpr bool __z_to_z = sizeof(v0) == 64 && sizeof(_To) == 64;

    // [if]X_to_i8 {{{2
    constexpr bool __i_to_i = std::is_integral_v<_U> && std::is_integral_v<_T>;
    constexpr bool i64_to_i8 = __i_to_i && sizeof(_T) == 8 && sizeof(_U) == 1;
    constexpr bool f64_to_i8 = is_integral_v<_U> && sizeof(_U) == 1 && is_floating_point_v<_T> && sizeof(_T) == 8;

    if constexpr (__i_to_i) {  // assert ISA {{{2
        static_assert(__x_to_x || __have_avx2,
                      "integral conversions with ymm registers require AVX2");
        static_assert(__have_avx512bw || ((sizeof(_T) >= 4 || sizeof(v0) < 64) &&
                                        (sizeof(_U) >= 4 || sizeof(_To) < 64)),
                      "8/16-bit integers in zmm registers require AVX512BW");
        static_assert((sizeof(v0) < 64 && sizeof(_To) < 64) || __have_avx512f,
                      "integral conversions with ymm registers require AVX2");
    }
    // concat => use 4-arg __convert_x86 {{{2
    if constexpr ((sizeof(v0) == 16 && __have_avx2) ||
                  (sizeof(v0) == 16 && __have_avx && std::is_floating_point_v<_T>) ||
                  (sizeof(v0) == 32 && __have_avx512f)) {
        // The ISA can handle wider input registers, so concat and use two-arg
        // implementation. This reduces code duplication considerably.
        return __convert_x86<_To>(__concat(v0, v1), __concat(v2, v3), __concat(v4, v5),
                                 __concat(v6, v7));
    } else {  //{{{2
        // conversion using bit reinterpretation (or no conversion at all) should all go
        // through the concat branch above:
        static_assert(!(std::is_floating_point_v<_T> == std::is_floating_point_v<_U> &&
                        sizeof(_T) == sizeof(_U)));
        static_assert(!(8 * _N < _M && sizeof(_To) > 16),
                      "zero extension should be impossible");
        if constexpr (i64_to_i8) {  //{{{2
            if constexpr (__x_to_x && __have_ssse3) {
                // unsure whether this is better than the variant below
                return __intrin_bitcast<_To>(_mm_shuffle_epi8(
                    __to_intrin(
                        (((v0.intrin() & 0xff) | ((v1.intrin() & 0xff) << 8)) |
                         (((v2.intrin() & 0xff) << 16) | ((v3.intrin() & 0xff) << 24))) |
                        ((((v4.intrin() & 0xff) << 32) | ((v5.intrin() & 0xff) << 40)) |
                         (((v6.intrin() & 0xff) << 48) | (v7.intrin() << 56)))),
                    _mm_setr_epi8(0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15)));
            } else if constexpr (__x_to_x) {
                const auto a = _mm_unpacklo_epi8(v0, v1); // ac
                const auto b = _mm_unpackhi_epi8(v0, v1); // bd
                const auto c = _mm_unpacklo_epi8(v2, v3); // eg
                const auto d = _mm_unpackhi_epi8(v2, v3); // fh
                const auto e = _mm_unpacklo_epi8(v4, v5); // ik
                const auto f = _mm_unpackhi_epi8(v4, v5); // jl
                const auto g = _mm_unpacklo_epi8(v6, v7); // mo
                const auto h = _mm_unpackhi_epi8(v6, v7); // np
                return __intrin_bitcast<_To>(_mm_unpacklo_epi64(
                    _mm_unpacklo_epi32(_mm_unpacklo_epi8(a, b),   // abcd
                                       _mm_unpacklo_epi8(c, d)),  // efgh
                    _mm_unpacklo_epi32(_mm_unpacklo_epi8(e, f),   // ijkl
                                       _mm_unpacklo_epi8(g, h))   // mnop
                    ));
            } else if constexpr (__y_to_y) {
                auto a =  // 048C GKOS 159D HLPT 26AE IMQU 37BF JNRV
                    __to_intrin(((( v0.intrin() & 0xff       ) | ((v1.intrin() & 0xff) <<  8)) |
                               (((v2.intrin() & 0xff) << 16) | ((v3.intrin() & 0xff) << 24))) |
                              ((((v4.intrin() & 0xff) << 32) | ((v5.intrin() & 0xff) << 40)) |
                               (((v6.intrin() & 0xff) << 48) | ((v7.intrin() << 56)))));
                /*
                auto b = _mm256_unpackhi_epi64(a, a);  // 159D HLPT 159D HLPT 37BF JNRV 37BF JNRV
                auto c = _mm256_unpacklo_epi8(a, b);  // 0145 89CD GHKL OPST 2367 ABEF IJMN QRUV
                auto d = __xzyw(c); // 0145 89CD 2367 ABEF GHKL OPST IJMN QRUV
                return _mm256_shuffle_epi8(
                    d, _mm256_setr_epi8(0, 1, 8, 9, 2, 3, 10, 11, 4, 5, 12, 13, 6, 7, 14,
                                        15, 0, 1, 8, 9, 2, 3, 10, 11, 4, 5, 12, 13, 6, 7,
                                        14, 15));
                                        */
                auto b = _mm256_shuffle_epi8( // 0145 89CD GHKL OPST 2367 ABEF IJMN QRUV
                    a, _mm256_setr_epi8(0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15,
                                        0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15));
                auto c = __xzyw(b); // 0145 89CD 2367 ABEF GHKL OPST IJMN QRUV
                return __intrin_bitcast<_To>(_mm256_shuffle_epi8(
                    c, _mm256_setr_epi8(0, 1, 8, 9, 2, 3, 10, 11, 4, 5, 12, 13, 6, 7, 14,
                                        15, 0, 1, 8, 9, 2, 3, 10, 11, 4, 5, 12, 13, 6, 7,
                                        14, 15)));
            } else if constexpr(__z_to_z) {
                return __concat(
                    __convert_x86<__vector_type_t<_U, _M / 2>>(v0, v1, v2, v3),
                    __convert_x86<__vector_type_t<_U, _M / 2>>(v4, v5, v6, v7));
            }
        } else if constexpr (f64_to_i8) {  //{{{2
            return __convert_x86<_To>(__convert_x86<__vector_type_t<int, _N * 2>>(v0, v1),
                                     __convert_x86<__vector_type_t<int, _N * 2>>(v2, v3),
                                     __convert_x86<__vector_type_t<int, _N * 2>>(v4, v5),
                                     __convert_x86<__vector_type_t<int, _N * 2>>(v6, v7));
        } else { // unreachable {{{2
            __assert_unreachable<_T>();
        }  //}}}

        // fallback: {{{2
        if constexpr (sizeof(_To) >= 32) {
            // if _To is ymm or zmm, then __storage<_U, _M / 2> is xmm or ymm
            return __concat(__convert_x86<__vector_type_t<_U, _M / 2>>(v0, v1, v2, v3),
                            __convert_x86<__vector_type_t<_U, _M / 2>>(v4, v5, v6, v7));
        } else if constexpr (sizeof(_To) == 16) {
            const auto lo = __to_intrin(__convert_x86<_To>(v0, v1, v2, v3));
            const auto hi = __to_intrin(__convert_x86<_To>(v4, v5, v6, v7));
            static_assert(sizeof(_U) == 1 && _N == 2);
            return __intrin_bitcast<_To>(_mm_unpacklo_epi64(lo, hi));
        } else {
            __assert_unreachable<_T>();
            //return __vector_convert<_To>(v0.d, v1.d, v2.d, v3.d, v4.d, v5.d, v6.d, v7.d,
            //                             make_index_sequence<_N>());
        }  //}}}2
    }
}//}}}

#endif  // __cplusplus >= 201703L
#endif  // _GLIBCXX_EXPERIMENTAL_SIMD_X86_CONVERSIONS_H
// vim: foldmethod=marker
