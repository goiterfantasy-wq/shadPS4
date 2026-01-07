// SPDX-FileCopyrightText: Copyright 2024 shadPS4 Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include <condition_variable>
#include <mutex>

#include "common/assert.h"
#include "common/logging/log.h"
#include "core/libraries/error_codes.h"
#include "core/libraries/kernel/kernel.h"
#include "core/libraries/kernel/posix_error.h"
#include "core/libraries/kernel/threads/pthread.h"
#include "core/libraries/libs.h"

namespace Libraries::Kernel {

static constexpr u32 BARRIER_VALID = 0xBAB1F00D;
static constexpr u32 BARRIER_DEAD = 0xDEADBEEF;
static constexpr int SHAD_PTHREAD_BARRIER_SERIAL_THREAD = -1;

struct PthreadBarrierAttr {
    int pshared;
};
using PthreadBarrierAttrT = PthreadBarrierAttr*;

struct PthreadBarrier {
    u32 valid;
    std::mutex lock;
    std::condition_variable cond;
    int cycle;
    int count;
    int waiters;
    int refcount;
    int destroying;
    std::string name;
};
using PthreadBarrierT = PthreadBarrier*;

// Barrier attribute functions
int PS4_SYSV_ABI posix_pthread_barrierattr_init(PthreadBarrierAttrT* attr) {
    if (attr == nullptr) {
        return POSIX_EINVAL;
    }
    *attr = new PthreadBarrierAttr{};
    (*attr)->pshared = 0; // PTHREAD_PROCESS_PRIVATE
    return 0;
}

int PS4_SYSV_ABI posix_pthread_barrierattr_destroy(PthreadBarrierAttrT* attr) {
    if (attr == nullptr || *attr == nullptr) {
        return POSIX_EINVAL;
    }
    delete *attr;
    *attr = nullptr;
    return 0;
}

int PS4_SYSV_ABI posix_pthread_barrierattr_getpshared(PthreadBarrierAttrT* attr, int* pshared) {
    if (attr == nullptr || *attr == nullptr || pshared == nullptr) {
        return POSIX_EINVAL;
    }
    *pshared = (*attr)->pshared;
    return 0;
}

int PS4_SYSV_ABI posix_pthread_barrierattr_setpshared(PthreadBarrierAttrT* attr, int pshared) {
    if (attr == nullptr || *attr == nullptr) {
        return POSIX_EINVAL;
    }
    // Only PTHREAD_PROCESS_PRIVATE is supported
    if (pshared != 0) {
        return POSIX_EINVAL;
    }
    (*attr)->pshared = pshared;
    return 0;
}

// Barrier functions
int PS4_SYSV_ABI posix_pthread_barrier_init(PthreadBarrierT* bar, const PthreadBarrierAttrT* attr,
                                            u32 count) {
    if (bar == nullptr || count == 0 || count > static_cast<u32>(INT_MAX)) {
        return POSIX_EINVAL;
    }

    if (attr != nullptr && *attr != nullptr) {
        if ((*attr)->pshared != 0) {
            LOG_ERROR(Lib_Kernel, "Shared barriers not supported");
            return POSIX_ENOSYS;
        }
    }

    auto* barrier = new PthreadBarrier{};
    barrier->valid = BARRIER_VALID;
    barrier->count = static_cast<int>(count);
    barrier->cycle = 0;
    barrier->waiters = 0;
    barrier->refcount = 0;
    barrier->destroying = 0;

    *bar = barrier;
    return 0;
}

int PS4_SYSV_ABI posix_pthread_barrier_destroy(PthreadBarrierT* bar) {
    if (bar == nullptr || *bar == nullptr) {
        return POSIX_EINVAL;
    }

    PthreadBarrier* bv = *bar;
    if (bv->valid != BARRIER_VALID) {
        return POSIX_ESRCH;
    }

    std::unique_lock lk(bv->lock);

    if (bv->destroying != 0) {
        return POSIX_EBUSY;
    }

    bv->destroying = 1;

    while (true) {
        if (bv->waiters > 0) {
            bv->destroying = 0;
            return POSIX_EBUSY;
        }
        if (bv->refcount != 0) {
            bv->cond.wait(lk);
        } else {
            break;
        }
    }

    *bar = nullptr;
    bv->valid = BARRIER_DEAD;
    bv->destroying = 0;

    lk.unlock();
    delete bv;
    return 0;
}

int PS4_SYSV_ABI posix_pthread_barrier_wait(PthreadBarrierT* bar) {
    if (bar == nullptr || *bar == nullptr) {
        return POSIX_EINVAL;
    }

    PthreadBarrier* bv = *bar;
    if (bv->valid != BARRIER_VALID) {
        return POSIX_ESRCH;
    }

    std::unique_lock lk(bv->lock);

    bv->waiters++;
    if (bv->waiters == bv->count) {
        // Current thread is the last thread
        bv->waiters = 0;
        bv->cycle++;
        bv->cond.notify_all();
        return SHAD_PTHREAD_BARRIER_SERIAL_THREAD;
    } else {
        int cycle = bv->cycle;
        bv->refcount++;

        // Wait until cycle changes (to avoid spurious wakeups)
        while (cycle == bv->cycle) {
            bv->cond.wait(lk);
        }

        bv->refcount--;
        if (bv->refcount == 0 && bv->destroying != 0) {
            bv->cond.notify_all();
        }

        return 0;
    }
}

int PS4_SYSV_ABI posix_pthread_barrier_setname_np(PthreadBarrierT* bar, const char* name) {
    if (bar == nullptr || *bar == nullptr) {
        return POSIX_EINVAL;
    }

    PthreadBarrier* bv = *bar;
    if (bv->valid != BARRIER_VALID) {
        return POSIX_ESRCH;
    }

    std::unique_lock lk(bv->lock);
    if (name != nullptr) {
        bv->name = name;
    }
    return 0;
}

// SCE wrappers
int PS4_SYSV_ABI scePthreadBarrierattrInit(PthreadBarrierAttrT* attr) {
    int result = posix_pthread_barrierattr_init(attr);
    return result == 0 ? ORBIS_OK : ErrnoToSceKernelError(result);
}

int PS4_SYSV_ABI scePthreadBarrierattrDestroy(PthreadBarrierAttrT* attr) {
    int result = posix_pthread_barrierattr_destroy(attr);
    return result == 0 ? ORBIS_OK : ErrnoToSceKernelError(result);
}

int PS4_SYSV_ABI scePthreadBarrierattrGetpshared(PthreadBarrierAttrT* attr, int* pshared) {
    int result = posix_pthread_barrierattr_getpshared(attr, pshared);
    return result == 0 ? ORBIS_OK : ErrnoToSceKernelError(result);
}

int PS4_SYSV_ABI scePthreadBarrierattrSetpshared(PthreadBarrierAttrT* attr, int pshared) {
    int result = posix_pthread_barrierattr_setpshared(attr, pshared);
    return result == 0 ? ORBIS_OK : ErrnoToSceKernelError(result);
}

int PS4_SYSV_ABI scePthreadBarrierInit(PthreadBarrierT* bar, const PthreadBarrierAttrT* attr,
                                       u32 count, const char* name) {
    int result = posix_pthread_barrier_init(bar, attr, count);
    if (result == 0 && name != nullptr && *bar != nullptr) {
        (*bar)->name = name;
    }
    LOG_INFO(Lib_Kernel, "scePthreadBarrierInit: name={}, count={}, result={}", 
             name ? name : "", count, result);
    return result == 0 ? ORBIS_OK : ErrnoToSceKernelError(result);
}

int PS4_SYSV_ABI scePthreadBarrierDestroy(PthreadBarrierT* bar) {
    int result = posix_pthread_barrier_destroy(bar);
    return result == 0 ? ORBIS_OK : ErrnoToSceKernelError(result);
}

int PS4_SYSV_ABI scePthreadBarrierWait(PthreadBarrierT* bar) {
    int result = posix_pthread_barrier_wait(bar);
    // Note: SHAD_PTHREAD_BARRIER_SERIAL_THREAD (-1) is a valid return value
    if (result == SHAD_PTHREAD_BARRIER_SERIAL_THREAD) {
        return ORBIS_KERNEL_PTHREAD_BARRIER_SERIAL;
    }
    return result == 0 ? ORBIS_OK : ErrnoToSceKernelError(result);
}

void RegisterBarrier(Core::Loader::SymbolsResolver* sym) {
    // POSIX functions
    LIB_FUNCTION("mqoLmJSBdyQ", "libScePosix", 1, "libkernel", posix_pthread_barrierattr_init);
    LIB_FUNCTION("mqoLmJSBdyQ", "libkernel", 1, "libkernel", posix_pthread_barrierattr_init);
    LIB_FUNCTION("6lVPjlVjJfE", "libScePosix", 1, "libkernel", posix_pthread_barrierattr_destroy);
    LIB_FUNCTION("6lVPjlVjJfE", "libkernel", 1, "libkernel", posix_pthread_barrierattr_destroy);
    LIB_FUNCTION("Ffy4DnGOzyo", "libScePosix", 1, "libkernel", posix_pthread_barrierattr_getpshared);
    LIB_FUNCTION("Ffy4DnGOzyo", "libkernel", 1, "libkernel", posix_pthread_barrierattr_getpshared);
    LIB_FUNCTION("4LqrPuWpMn4", "libScePosix", 1, "libkernel", posix_pthread_barrierattr_setpshared);
    LIB_FUNCTION("4LqrPuWpMn4", "libkernel", 1, "libkernel", posix_pthread_barrierattr_setpshared);

    LIB_FUNCTION("IvFcF5bCmJo", "libScePosix", 1, "libkernel", posix_pthread_barrier_init);
    LIB_FUNCTION("IvFcF5bCmJo", "libkernel", 1, "libkernel", posix_pthread_barrier_init);
    LIB_FUNCTION("6d-2sCnLqnI", "libScePosix", 1, "libkernel", posix_pthread_barrier_destroy);
    LIB_FUNCTION("6d-2sCnLqnI", "libkernel", 1, "libkernel", posix_pthread_barrier_destroy);
    LIB_FUNCTION("Ht+WPExb-Ks", "libScePosix", 1, "libkernel", posix_pthread_barrier_wait);
    LIB_FUNCTION("Ht+WPExb-Ks", "libkernel", 1, "libkernel", posix_pthread_barrier_wait);

    // SCE functions
    LIB_FUNCTION("zhMHO2aQN-k", "libkernel", 1, "libkernel", scePthreadBarrierattrInit);
    LIB_FUNCTION("6lVPjlVjJfE", "libkernel", 1, "libkernel", scePthreadBarrierattrDestroy);
    LIB_FUNCTION("Ffy4DnGOzyo", "libkernel", 1, "libkernel", scePthreadBarrierattrGetpshared);
    LIB_FUNCTION("4LqrPuWpMn4", "libkernel", 1, "libkernel", scePthreadBarrierattrSetpshared);

    LIB_FUNCTION("b+lFLw7Bq3M", "libkernel", 1, "libkernel", scePthreadBarrierInit);
    LIB_FUNCTION("1r4AqoQMOM0", "libkernel", 1, "libkernel", scePthreadBarrierDestroy);
    LIB_FUNCTION("n20TI8gLJmo", "libkernel", 1, "libkernel", scePthreadBarrierWait);
}

} // namespace Libraries::Kernel
