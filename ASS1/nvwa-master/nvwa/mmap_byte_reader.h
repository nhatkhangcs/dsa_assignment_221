// -*- Mode: C++; tab-width: 4; c-basic-offset: 4; indent-tabs-mode: nil -*-
// vim:tabstop=4:shiftwidth=4:expandtab:

/*
 * Copyright (C) 2017-2021 Wu Yongwei <wuyongwei at gmail dot com>
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
 * @file  mmap_byte_reader.h
 *
 * Header file for mmap_byte_reader, an easy-to-use byte-based file reader.
 * It is implemented with memory-mapped file APIs.
 *
 * @date  2021-08-06
 */

#ifndef NVWA_MMAP_BYTE_READER_H
#define NVWA_MMAP_BYTE_READER_H

#include <stddef.h>             // ptrdiff_t/size_t
#include <iterator>             // std::random_access_iterator_tag
#include "_nvwa.h"              // NVWA_NAMESPACE_*
#include "mmap_reader_base.h"   // nvwa::mmap_reader_base

NVWA_NAMESPACE_BEGIN

/** Class template to allow iteration over all bytes of a mmappable file. */
template <typename _Tp>
class basic_mmap_byte_reader : private mmap_reader_base {
public:
    static_assert(sizeof(_Tp) == 1, "size of an element must be one");

    /** Iterator over the bytes. */
    class iterator {  // implements RandomAccessIterator
    public:
        typedef _Tp                             value_type;
        typedef const value_type*               pointer;
        typedef const value_type&               reference;
        typedef ptrdiff_t                       difference_type;
        typedef std::random_access_iterator_tag iterator_category;

        explicit iterator(const basic_mmap_byte_reader* reader,
                          size_t offset = 0) noexcept
            : _M_reader(reader), _M_offset(offset)
        {
        }

        reference operator*() const noexcept
        {
            return _M_reader->get(_M_offset);
        }
        pointer operator->() const noexcept
        {
            return &_M_reader->get(_M_offset);
        }
        iterator& operator++() noexcept
        {
            ++_M_offset;
            return *this;
        }
        iterator operator++(int) noexcept
        {
            iterator temp(*this);
            ++*this;
            return temp;
        }
        iterator& operator--() noexcept
        {
            --_M_offset;
            return *this;
        }
        iterator operator--(int) noexcept
        {
            iterator temp(*this);
            --*this;
            return temp;
        }
        iterator& operator+=(difference_type i) noexcept
        {
            _M_offset += i;
            return *this;
        }
        iterator& operator-=(difference_type i) noexcept
        {
            _M_offset -= i;
            return *this;
        }
        iterator operator+(difference_type i) const noexcept
        {
            return iterator(_M_reader, _M_offset + i);
        }
        iterator operator-(difference_type i) const noexcept
        {
            return iterator(_M_reader, _M_offset - i);
        }
        difference_type operator-(const iterator& rhs) const noexcept
        {
            return _M_offset - rhs._M_offset;
        }
        reference operator[](difference_type i) const noexcept
        {
            return _M_reader->get(_M_offset + i);
        }

        bool operator==(const iterator& rhs) const noexcept
        {
            return _M_reader == rhs._M_reader && _M_offset == rhs._M_offset;
        }
        bool operator!=(const iterator& rhs) const noexcept
        {
            return !operator==(rhs);
        }
        bool operator<(const iterator& rhs) const noexcept
        {
            return _M_reader < rhs._M_reader ||
                   (_M_reader == rhs._M_reader &&
                    _M_offset < rhs._M_offset);
        }
        bool operator>(const iterator& rhs) const noexcept
        {
            return _M_reader > rhs._M_reader ||
                   (_M_reader == rhs._M_reader &&
                    _M_offset > rhs._M_offset);
        }
        bool operator<=(const iterator& rhs) const noexcept
        {
            return !operator>(rhs);
        }
        bool operator>=(const iterator& rhs) const noexcept
        {
            return !operator<(rhs);
        }

    private:
        const basic_mmap_byte_reader* _M_reader;
        size_t                        _M_offset;
    };

    typedef iterator const_iterator;

    explicit basic_mmap_byte_reader(const char* path)
        : mmap_reader_base(path)
    {
    }
#if NVWA_WINDOWS
    explicit basic_mmap_byte_reader(const wchar_t* path)
        : mmap_reader_base(path)
    {
    }
#endif
#if NVWA_UNIX
    explicit basic_mmap_byte_reader(int fd) : mmap_reader_base(fd) {}
#endif
    basic_mmap_byte_reader(const basic_mmap_byte_reader&) = delete;
    basic_mmap_byte_reader& operator=(const basic_mmap_byte_reader&) = delete;
    ~basic_mmap_byte_reader() = default;

    iterator begin() const noexcept
    {
        return iterator(this);
    }
    iterator end() const noexcept
    {
        return iterator(this, _M_size);
    }

    const _Tp& get(size_t offset) const noexcept
    {
        // Cast is necessary for unsigned char support
        return reinterpret_cast<const _Tp&>(_M_mmap_ptr[offset]);
    }
};

typedef basic_mmap_byte_reader<char>          mmap_char_reader;
typedef basic_mmap_byte_reader<unsigned char> mmap_byte_reader;

NVWA_NAMESPACE_END

#endif // NVWA_MMAP_BYTE_READER_H
