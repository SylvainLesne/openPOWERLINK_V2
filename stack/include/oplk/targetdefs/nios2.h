/**
********************************************************************************
\file   targetdefs/nios2.h

\brief  Target specific definitions for NIOS2 systems

This file contains target specific definitions for NIOS2 systems.
*******************************************************************************/

/*------------------------------------------------------------------------------
Copyright (c) 2014, Bernecker+Rainer Industrie-Elektronik Ges.m.b.H. (B&R)
Copyright (c) 2013, SYSTEC electronic GmbH
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the copyright holders nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
------------------------------------------------------------------------------*/

#ifndef _INC_targetdefs_nios2_H_
#define _INC_targetdefs_nios2_H_

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <alt_types.h>
#include <io.h>

#include <oplk/basictypes.h>

//------------------------------------------------------------------------------
// const defines
//------------------------------------------------------------------------------
#define ROM_INIT                // variables will be initialized directly in ROM (means no copy from RAM in startup)
#define ROM                     // code or variables mapped to ROM (i.e. flash)
                                // usage: CONST BYTE ROM foo = 0x00;

#define MEM                     // Memory attribute to optimize speed and code of pointer access.

#ifndef CONST
#define CONST const             // variables mapped to ROM (i.e. flash)
#endif

#define OPLKDLLEXPORT

#define UNUSED_PARAMETER(par)   (void)par

#if !defined(__OPTIMIZE__)
//restore default: disable inlining if optimization is disabled
#define INLINE_FUNCTION
#undef  INLINE_ENABLED
#undef  INLINE_FUNCTION_DEF
#endif

#ifndef NDEBUG
#define PRINTF(...)                 printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

// Target IO functions
// - Write
#define OPLK_IO_WR8(addr, val)      IOWR_8DIRECT(addr, 0, val)
#define OPLK_IO_WR16(addr, val)     IOWR_16DIRECT(addr, 0, val)
#define OPLK_IO_WR32(addr, val)     IOWR_32DIRECT(addr, 0, val)
// - Read
#define OPLK_IO_RD8(addr)           IORD_8DIRECT(addr, 0)
#define OPLK_IO_RD16(addr)          IORD_16DIRECT(addr, 0)
#define OPLK_IO_RD32(addr)          IORD_32DIRECT(addr, 0)

// Target data cache functions
#define OPLK_DCACHE_FLUSH(addr, len)        ((void)0)
#define OPLK_DCACHE_INVALIDATE(addr, len)   ((void)0)

// Target memory barrier function
#define OPLK_MEMBAR()               __asm("sync")

// Target lock
#define OPLK_LOCK_T                 UINT8

/* NOTE:
 * Nios II does not support atomic instructions, hence, pseudo atomic
 * macro is applied with locking.
 */
#define OPLK_ATOMIC_T    alt_u8
#define OPLK_ATOMIC_INIT(base) \
                        if (target_initLock(&base->lock) != 0) \
                            return kErrorNoResource
#define OPLK_ATOMIC_EXCHANGE(address, newval, oldval) \
                        target_lock(); \
                        oldval = IORD_8DIRECT(address, 0); \
                        IOWR_8DIRECT(address, 0, newval); \
                        target_unlock()

#define OPLK_MUTEX_T    alt_u8

#endif /* _INC_targetdefs_nios2_H_ */

