// -*- Mode: C++; tab-width: 4; c-basic-offset: 4; indent-tabs-mode: nil -*-
// vim:tabstop=4:shiftwidth=4:expandtab:

/*
 * Copyright (C) 2004-2022 Wu Yongwei <wuyongwei at gmail dot com>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any
 * damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute
 * it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must
 *    not claim that you wrote the original software.  If you use this
 *    software in a product, an acknowledgement in the product
 *    documentation would be appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must
 *    not be misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source
 *    distribution.
 *
 * This file is part of Stones of Nvwa:
 *      https://github.com/adah1972/nvwa
 *
 */

/**
 * @file  bool_array.cpp
 *
 * Code for class bool_array (packed boolean array).  The current code
 * requires a C++14-compliant compiler.
 *
 * @date  2022-01-05
 */

#include "bool_array.h"         // bool_array
#include <limits.h>             // UINT_MAX, ULONG_MAX
#include <string.h>             // memset/memcpy/size_t
#include <array>                // std::array
#include <new>                  // std::bad_alloc
#include <ostream>              // std::ostream
#include <type_traits>          // std::enable_if_t/is_same
#include <utility>              // std::index_sequence/swap
#include "_nvwa.h"              // NVWA macros
#include "c++_features.h"       // NVWA_USES_CXX20
#include "static_assert.h"      // STATIC_ASSERT

// I am sure there are other cases where std::popcount/__builtin_popcount
// can help with the bool_array::count performance, but I want to turn on
// use of popcount only after tests show a performance win (I know using
// popcount will slow down the code in some cases).  Patches are welcome.
#ifndef NVWA_USES_POPCOUNT
#if NVWA_CLANG ||                                                          \
    (NVWA_GCC && defined(__POPCNT__) || defined(__SSE4_2__) ||             \
     defined(__aarch64__)) ||                                              \
    (NVWA_MSVC && NVWA_USES_CXX20)
#define NVWA_USES_POPCOUNT 1
#else
#define NVWA_USES_POPCOUNT 0
#endif
#endif

#if NVWA_USES_POPCOUNT
#if NVWA_USES_CXX20 && __has_include(<bit>)
#include <bit>
namespace {

constexpr int popcount(size_t x)
{
    return std::popcount(x);
}

} /* unnamed namespace */
#elif NVWA_GCC || NVWA_CLANG
namespace {

template <typename T = size_t>
constexpr std::enable_if_t<std::is_same<T, unsigned>::value, int>
popcount(unsigned x)
{
    return __builtin_popcount(x);
}

template <typename T = size_t>
constexpr std::enable_if_t<std::is_same<T, unsigned long>::value, int>
popcount(unsigned long x)
{
    return __builtin_popcountl(x);
}

template <typename T = size_t>
constexpr std::enable_if_t<std::is_same<T, unsigned long long>::value, int>
popcount(unsigned long long x)
{
    return __builtin_popcountll(x);
}

} /* unnamed namespace */
#else
#error "No popcount function is available"
#endif
#endif

NVWA_NAMESPACE_BEGIN

namespace {

// Calculates how many 1-bits there are in a given byte.
constexpr int count_bits(unsigned char value)
{
    if (value == 0) {
        return 0;
    } else {
        return (value & 1) + count_bits(value >> 1);
    }
}

// Calculates at which offset the first 1-bit is for a given byte.
// The value for 0 indicates it is invalid (all bits are 0s).
constexpr int first_bit_one_offset(unsigned char value)
{
    if (value == 0) {
        return 9;
    } else if (value & 1) {
        return 0;
    } else {
        return 1 + first_bit_one_offset(value >> 1);
    }
}

template <size_t... _V>
constexpr auto get_bit_count(std::index_sequence<_V...>)
{
    return std::array<unsigned char, sizeof...(_V)>{
        static_cast<unsigned char>(count_bits(_V))...};
}

template <size_t... _V>
constexpr auto get_bit_ordinal(std::index_sequence<_V...>)
{
    return std::array<unsigned char, sizeof...(_V)>{
        static_cast<unsigned char>(first_bit_one_offset(_V))...};
}

/**
 * Object that contains pre-calculated values how many 1-bits there are
 * in a given byte.
 */
auto _S_bit_count = get_bit_count(std::make_index_sequence<256>());

/**
 * Object that contains pre-calculated values at which offset the first
 * 1-bit is for a given byte.
 */
auto _S_bit_ordinal = get_bit_ordinal(std::make_index_sequence<256>());

/**
 * Outputs the bits in a byte.
 *
 * @param os        the stream to output to
 * @param value     the byte to output
 * @param num_bits  number of bits to output (default is 8)
 */
void output_bits(std::ostream& os, unsigned char value,
                 unsigned num_bits = 8)
{
    char output[9];
    assert(num_bits < sizeof output);
    unsigned i = 0;
    while (i < num_bits) {
        output[i++] = ((value & 1U) ? '1' : '0');
        value >>= 1;
    }
    output[i] = '\0';
    os << output;
}

} /* unnamed namespace */

/**
 * Constructs a bool_array with a specific size.
 *
 * @param size          size of the array
 * @throw out_of_range  \a size equals \c 0
 * @throw bad_alloc     memory is insufficient
 */
bool_array::bool_array(size_type size)
{
    if (size == 0) {
        throw std::out_of_range("invalid bool_array size");
    }
    if (!create(size)) {
        throw std::bad_alloc();
    }
}

/**
 * Constructs a bool_array from a given bitmap.
 *
 * @param ptr           pointer to a bitmap
 * @param size          size of the array
 * @throw out_of_range  \a size equals \c 0
 * @throw bad_alloc     memory is insufficient
 */
bool_array::bool_array(const void* ptr, size_type size)
{
    if (size == 0) {
        throw std::out_of_range("invalid bool_array size");
    }
    if (!create(size)) {
        throw std::bad_alloc();
    }

    size_t byte_cnt = get_num_bytes_from_bits(_M_length);
    memcpy(_M_byte_ptr, ptr, byte_cnt);
    int valid_bits_in_last_byte = (_M_length - 1) % 8 + 1;
    _M_byte_ptr[byte_cnt - 1] &= ~(~0U << valid_bits_in_last_byte);
}

/**
 * Copy-constructor.
 *
 * @param rhs        the bool_array to copy from
 * @throw bad_alloc  memory is insufficient
 */
bool_array::bool_array(const bool_array& rhs)
{
    if (rhs.size() == 0) {
        return;
    }
    if (!create(rhs.size())) {
        throw std::bad_alloc();
    }
    memcpy(_M_byte_ptr, rhs._M_byte_ptr, (_M_length - 1) / 8 + 1);
}

/**
 * Assignment operator.
 *
 * @param rhs        the bool_array to copy from
 * @throw bad_alloc  memory is insufficient
 */
bool_array& bool_array::operator=(const bool_array& rhs)
{
    bool_array temp(rhs);
    swap(temp);
    return *this;
}

/**
 * Creates the packed boolean array with a specific size.
 *
 * @param size  size of the array
 * @return      \c false if \a size equals \c 0 or is too big, or if
 *              memory is insufficient; \c true if \a size has a
 *              suitable value and memory allocation is successful.
 */
bool bool_array::create(size_type size) noexcept
{
    if (size == 0) {
        return false;
    }

#if defined(__x86_64) || defined(__ia64) || defined(__ppc64__) || \
    defined(_WIN64) || defined(_M_IA64) || \
    defined(__lp64) || defined(_LP64)
    STATIC_ASSERT(sizeof(size_t) == sizeof(size_type),  Wrong_size_type);
#else
    STATIC_ASSERT(sizeof(size_t) <= sizeof(size_type),  Wrong_size_type);
    STATIC_ASSERT(sizeof(size_t)==sizeof(unsigned int), Wrong_size_assumption);
    // Will be optimized away by a decent compiler if ULONG_MAX == UINT_MAX
    if (ULONG_MAX > UINT_MAX && ((size - 1) / 8 + 1) > UINT_MAX) {
        return false;
    }
#endif

    size_t byte_cnt = get_num_bytes_from_bits(size);
    byte* byte_ptr = (byte*)malloc(byte_cnt);
    if (byte_ptr == nullptr) {
        return false;
    }

    if (_M_byte_ptr) {
        free(_M_byte_ptr);
    }

    _M_byte_ptr = byte_ptr;
    _M_length = size;
    return true;
}

/**
 * Initializes all array elements to a specific value optimally.
 *
 * @param value  the boolean value to assign to all elements
 */
void bool_array::initialize(bool value) noexcept
{
    assert(_M_byte_ptr);
    size_t byte_cnt = get_num_bytes_from_bits(_M_length);
    memset(_M_byte_ptr, value ? ~0 : 0, byte_cnt);
    if (value) {
        int valid_bits_in_last_byte = (_M_length - 1) % 8 + 1;
        _M_byte_ptr[byte_cnt - 1] &= ~(~0U << valid_bits_in_last_byte);
    }
}

/**
 * Counts elements with a \c true value.
 *
 * @return  the count of \c true elements
 */
bool_array::size_type bool_array::count() const noexcept
{
    assert(_M_byte_ptr);
    size_type true_cnt = 0;
    size_t byte_cnt = get_num_bytes_from_bits(_M_length);
    size_t i = 0;
#if NVWA_USES_POPCOUNT
    if (byte_cnt >= sizeof(size_t)) {
        auto ptr = reinterpret_cast<size_t*>(_M_byte_ptr);
        while (i <= byte_cnt - sizeof(size_t)) {
            true_cnt += popcount(*ptr);
            ++ptr;
            i += sizeof(size_t);
        }
    }
#endif
    for (; i < byte_cnt; ++i) {
        true_cnt += _S_bit_count[_M_byte_ptr[i]];
    }
    return true_cnt;
}

/**
 * Counts elements with a \c true value in a specified range.
 *
 * @param begin         beginning of the range
 * @param end           end of the range (exclusive)
 * @return              the count of \c true elements
 * @throw out_of_range  the range [begin, end) is invalid
 */
bool_array::size_type bool_array::count(size_type begin, size_type end) const
{
    assert(_M_byte_ptr);
    if (end == npos) {
        end = _M_length;
    }
    if (begin == end) {
        return 0;
    }
    if (begin > end || end > _M_length) {
        throw std::out_of_range("invalid bool_array range");
    }

    size_type true_cnt = 0;
    size_t byte_pos_beg = begin / 8;
    size_t byte_pos_end = (end - 1) / 8;
    int valid_bits_in_last_byte = (end - 1) % 8 + 1;
    if (begin % 8 != 0) {
        byte byte_val = _M_byte_ptr[byte_pos_beg];
        byte_val &= ~0U << (begin % 8);
        if (byte_pos_beg == byte_pos_end) {
            byte_val &= ~(~0U << valid_bits_in_last_byte);
            true_cnt = _S_bit_count[byte_val];
            return true_cnt;
        } else {  // byte_pos_beg < byte_pos_end
            true_cnt = _S_bit_count[byte_val];
            ++byte_pos_beg;
        }
    }
    if (valid_bits_in_last_byte != 8) {
        byte byte_val = _M_byte_ptr[byte_pos_end];
        byte_val &= ~(~0U << valid_bits_in_last_byte);
        true_cnt += _S_bit_count[byte_val];
    } else {
        ++byte_pos_end;
    }
    // [byte_pos_beg, byte_pos_end) is now the byte range we need to count

#if NVWA_USES_POPCOUNT
    constexpr auto pc_unit = sizeof(size_t);
    if ((byte_pos_beg + pc_unit - 1) / pc_unit * pc_unit + pc_unit <=
        byte_pos_end) {
        while (byte_pos_beg % pc_unit != 0) {
            true_cnt += _S_bit_count[_M_byte_ptr[byte_pos_beg]];
            ++byte_pos_beg;
        }
        auto ptr = reinterpret_cast<size_t*>(&_M_byte_ptr[byte_pos_beg]);
        while (byte_pos_beg <= byte_pos_end - pc_unit) {
            true_cnt += popcount(*ptr);
            ++ptr;
            byte_pos_beg += pc_unit;
        }
    }
#endif
    for (; byte_pos_beg < byte_pos_end; ++byte_pos_beg) {
        true_cnt += _S_bit_count[_M_byte_ptr[byte_pos_beg]];
    }
    return true_cnt;
}

/**
 * Searches for the specified boolean value.  This function accepts a
 * range expressed in [begin, end).
 *
 * @param begin         the position at which the search is to begin
 * @param end           the end position (exclusive) to stop searching
 * @param value         the boolean value to find
 * @return              position of the first value found if successful;
 *                      \c #npos otherwise
 * @throw out_of_range  the range [begin, end) is invalid
 */
bool_array::size_type bool_array::find_until(
        bool value,
        size_type begin,
        size_type end) const
{
    assert(_M_byte_ptr);
    if (begin == end) {
        return npos;
    }
    if (end == npos) {
        end = _M_length;
    }
    if (begin > end || end > _M_length) {
        throw std::out_of_range("invalid bool_array range");
    }
    --end;

    size_t byte_pos_beg = begin / 8;
    size_t byte_pos_end = end / 8;
    byte byte_val = _M_byte_ptr[byte_pos_beg];

    if (value) {
        byte_val &= ~0U << (begin % 8);
        for (size_t i = byte_pos_beg; i < byte_pos_end;) {
            if (byte_val != 0) {
                return i * 8 + _S_bit_ordinal[byte_val];
            }
            byte_val = _M_byte_ptr[++i];
        }
        byte_val &= ~(~0U << (end % 8 + 1));
        if (byte_val != 0) {
            return byte_pos_end * 8 + _S_bit_ordinal[byte_val];
        }
    } else {
        byte_val |= ~(~0U << (begin % 8));
        for (size_t i = byte_pos_beg; i < byte_pos_end;) {
            if (byte_val != 0xFF) {
                return i * 8 + _S_bit_ordinal[(byte)~byte_val];
            }
            byte_val = _M_byte_ptr[++i];
        }
        byte_val |= ~0U << (end % 8 + 1);
        if (byte_val != 0xFF) {
            return byte_pos_end * 8 + _S_bit_ordinal[(byte)~byte_val];
        }
    }

    return npos;
}

/**
 * Changes all \c true elements to \c false, and \c false ones to \c true.
 */
void bool_array::flip() noexcept
{
    assert(_M_byte_ptr);
    size_t byte_cnt = get_num_bytes_from_bits(_M_length);
    for (size_t i = 0; i < byte_cnt; ++i) {
        _M_byte_ptr[i] = ~_M_byte_ptr[i];
    }
    int valid_bits_in_last_byte = (_M_length - 1) % 8 + 1;
    _M_byte_ptr[byte_cnt - 1] &= ~(~0U << valid_bits_in_last_byte);
}

/**
 * Exchanges the content of this bool_array with another.
 *
 * @param rhs  another bool_array to exchange content with
 */
void bool_array::swap(bool_array& rhs) noexcept
{
    std::swap(_M_byte_ptr, rhs._M_byte_ptr);
    std::swap(_M_length,   rhs._M_length);
}

/**
 * Merges elements of another bool_array with a logical AND.
 *
 * @param rhs           another bool_array to merge
 * @param begin         beginning of the range in \a rhs
 * @param end           end of the range (exclusive) in \a rhs
 * @param offset        position to merge in this bool_array
 * @throw out_of_range  bad range for the source or the destination
 */
void bool_array::merge_and(
        const bool_array& rhs,
        size_type begin,
        size_type end,
        size_type offset)
{
    assert(_M_byte_ptr);
    if (begin == end) {
        return;
    }
    if (end == npos) {
        end = rhs._M_length;
    }
    if (begin > end || end > rhs._M_length) {
        throw std::out_of_range("invalid bool_array range");
    }
    if (offset + (end - begin) > _M_length) {
        throw std::out_of_range("destination overflown");
    }

    size_t byte_offset = offset / 8;
    size_t bit_offset = offset % 8;
    byte value;
    if (bit_offset != 0 && begin + 8 - bit_offset <= end) {
        // Merge the first byte (in destination), if it is partial and
        // there are remaining bits
        value = rhs.get_8bits(begin, end);
        value = ~(~value << bit_offset);
        _M_byte_ptr[byte_offset] &= value;
        begin += 8 - bit_offset;
        byte_offset++;
        bit_offset = 0;
    }
    while (begin + 8 <= end) {
        // Merge all the full bytes
        value = rhs.get_8bits(begin, end);
        _M_byte_ptr[byte_offset++] &= value;
        begin += 8;
    }
    if (begin < end) {
        // Merge the remaining bits
        assert(end - begin < 8);
        value = rhs.get_8bits(begin, end);
        value |= ~0U << (end - begin);
        if (bit_offset != 0) {
            value = ~(~value << bit_offset);
        }
        _M_byte_ptr[byte_offset] &= value;
    }
}

/**
 * Merges elements of another bool_array with a logical OR.
 *
 * @param rhs           another bool_array to merge
 * @param begin         beginning of the range in \a rhs
 * @param end           end of the range (exclusive) in \a rhs
 * @param offset        position to merge in this bool_array
 * @throw out_of_range  bad range for the source or the destination
 */
void bool_array::merge_or(
        const bool_array& rhs,
        size_type begin,
        size_type end,
        size_type offset)
{
    assert(_M_byte_ptr);
    if (begin == end) {
        return;
    }
    if (end == npos) {
        end = rhs._M_length;
    }
    if (begin > end || end > rhs._M_length) {
        throw std::out_of_range("invalid bool_array range");
    }
    if (offset + (end - begin) > _M_length) {
        throw std::out_of_range("destination overflown");
    }

    size_t byte_offset = offset / 8;
    size_t bit_offset = offset % 8;
    byte value;
    if (bit_offset != 0 && begin + 8 - bit_offset <= end) {
        // Merge the first byte (in destination), if it is partial and
        // there are remaining bits
        value = rhs.get_8bits(begin, end);
        value = value << bit_offset;
        _M_byte_ptr[byte_offset] |= value;
        begin += 8 - bit_offset;
        byte_offset++;
        bit_offset = 0;
    }
    while (begin + 8 <= end) {
        // Merge all the full bytes
        value = rhs.get_8bits(begin, end);
        _M_byte_ptr[byte_offset++] |= value;
        begin += 8;
    }
    if (begin < end) {
        // Merge the remaining bits
        assert(end - begin < 8);
        value = rhs.get_8bits(begin, end);
        value &= ~(~0U << (end - begin));
        if (bit_offset != 0) {
            value = value << bit_offset;
        }
        _M_byte_ptr[byte_offset] |= value;
    }
}

/**
 * Copies the bool_array content as bitmap to a specified buffer.  The
 * caller needs to ensure the destination buffer is big enough.
 *
 * @param dest          address of the destination buffer
 * @param begin         beginning of the range
 * @param end           end of the range (exclusive)
 * @throw out_of_range  bad range for the source or the destination
 */
void bool_array::copy_to_bitmap(void* dest, size_type begin, size_type end)
{
    assert(_M_byte_ptr);
    if (begin == end) {
        return;
    }
    if (end == npos) {
        end = _M_length;
    }
    if (begin > end || end > _M_length) {
        throw std::out_of_range("invalid bool_array range");
    }

    if (begin % 8 == 0) {
        memcpy(dest, _M_byte_ptr + begin / 8,
               get_num_bytes_from_bits(end - begin));
    } else {
        byte* byte_ptr = (byte*)dest;
        size_type offset = begin;
        while (offset < end) {
            *byte_ptr++ = get_8bits(offset, end);
            offset += 8;
        }
    }

    if (int extra_bits = (end - begin) % 8) {
        byte* last_byte_ptr = (byte*)dest +
                              get_num_bytes_from_bits(end - begin) - 1;
        *last_byte_ptr &= ~(~0U << extra_bits);
    }
}

/**
 * Retreive contiguous 8 bits from the bool_array.  If fewer than 8 bits
 * are available, the extra bits are undefined.
 *
 * @param offset  beginning position to retrieve the bits
 * @param end     end position beyond whose byte no bits will be taken
 */
bool_array::byte bool_array::get_8bits(size_type offset, size_type end) const
{
    size_t byte_offset = offset / 8;
    size_t bit_offset = offset % 8;
    byte retval = _M_byte_ptr[byte_offset] >> bit_offset;
    if (bit_offset != 0 && byte_offset < (end - 1) / 8) {
        retval |= _M_byte_ptr[byte_offset + 1] << (8 - bit_offset);
    }
    return retval;
}

std::ostream& operator<<(std::ostream& os, const bool_array& ba)
{
    size_t byte_cnt = bool_array::get_num_bytes_from_bits(ba.size());
    if (byte_cnt == 0) {
        return os;
    }
    size_t i = 0;
    for (; i < byte_cnt - 1; ++i) {
        output_bits(os, ba._M_byte_ptr[i]);
    }
    output_bits(os, ba._M_byte_ptr[i], ba.size() - (byte_cnt - 1) * 8);
    return os;
}

NVWA_NAMESPACE_END
