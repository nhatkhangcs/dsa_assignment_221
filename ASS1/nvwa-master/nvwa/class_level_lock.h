// -*- Mode: C++; tab-width: 4; c-basic-offset: 4; indent-tabs-mode: nil -*-
// vim:tabstop=4:shiftwidth=4:expandtab:

/*
 * Copyright (C) 2004-2021 Wu Yongwei <wuyongwei at gmail dot com>
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
 * @file  class_level_lock.h
 *
 * In essence Loki ClassLevelLockable re-engineered to use a fast_mutex class.
 *
 * @date  2021-08-06
 */

#ifndef NVWA_CLASS_LEVEL_LOCK_H
#define NVWA_CLASS_LEVEL_LOCK_H

#include "fast_mutex.h"         // nvwa::fast_mutex/_NOTHREADS
#include "_nvwa.h"              // NVWA_NAMESPACE_*

NVWA_NAMESPACE_BEGIN

# ifdef _NOTHREADS
    /**
     * Helper class for class-level locking.  This is the
     * single-threaded implementation.
     */
    template <class _Host, bool _RealLock = false>
    class class_level_lock {
    public:
        /** Type that provides locking/unlocking semantics. */
        class lock {
        public:
            lock() = default;
        };

        typedef _Host volatile_type;
    };
# else
    /**
     * Helper class for class-level locking.  This is the multi-threaded
     * implementation.  The main departure from Loki ClassLevelLockable
     * is that there is an additional template parameter which can make
     * the lock not %lock at all even in multi-threaded environments.
     * See static_mem_pool.h for real usage.
     */
    template <class _Host, bool _RealLock = true>
    class class_level_lock {
        static fast_mutex _S_mtx;

    public:
        // The C++ 1998 Standard required the use of `friend' here, but
        // this requirement was considered a defect and subsequently
        // changed.  It is still used here for compatibility with older
        // compilers.
        class lock;
        friend class lock;

        /** Type that provides locking/unlocking semantics. */
        class lock {
        public:
            lock()
            {
                if (_RealLock) {
                    _S_mtx.lock();
                }
            }
            lock(const lock&) = delete;
            lock& operator=(const lock&) = delete;
            ~lock()
            {
                if (_RealLock) {
                    _S_mtx.unlock();
                }
            }
        };

        typedef volatile _Host volatile_type;
    };

    /** Partial specialization that makes null locking. */
    template <class _Host>
    class class_level_lock<_Host, false> {
    public:
        /** Type that provides locking/unlocking semantics. */
        class lock {
        public:
            lock() = default;
        };

        typedef _Host volatile_type;
    };

    template <class _Host, bool _RealLock>
    fast_mutex class_level_lock<_Host, _RealLock>::_S_mtx;
# endif // _NOTHREADS

NVWA_NAMESPACE_END

#endif // NVWA_CLASS_LEVEL_LOCK_H
