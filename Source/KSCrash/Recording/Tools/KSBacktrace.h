//
//  KSBacktrace.h
//
//  Created by Karl Stenerud on 2012-01-28.
//
//  Copyright (c) 2012 Karl Stenerud. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall remain in place
// in this source code.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//


/* Stack backtrace and symbolication functions.
 */


#ifndef HDR_KSBacktrace_h
#define HDR_KSBacktrace_h

#ifdef __cplusplus
extern "C" {
#endif


#include <dlfcn.h>
#include <mach/mach.h>
#include <pthread.h>


/** Generate a backtrace on the specified mach thread (async-safe).
 *
 *
 * @param thread The thread to generate a backtrace for.
 *
 * @param backtraceBuffer A buffer to hold the backtrace.
 *
 * @param maxEntries The maximum number of trace entries to generate (must not
 *                   be larger than backtraceBuffer can hold).
 *
 * @return The number of backtrace entries generated.
 */
int ksbt_backtraceThread(thread_t thread,
                         uintptr_t* backtraceBuffer,
                         int maxEntries);

/** Generate a backtrace on the currently running thread (async-safe).
 *
 * Note: This function seems to get a bit confused at times due to stack
 *       activity. Use at own risk.
 *
 * @param backtraceBuffer A buffer to hold the backtrace.
 *
 * @param maxEntries The maximum number of trace entries to generate (must not
 *                   be larger than backtraceBuffer can hold).
 *
 * @return The number of backtrace entries generated.
 */
int ksbt_backtraceSelf(uintptr_t* backtraceBuffer,
                       int maxEntries);

/** Symbolicate a backtrace (async-safe).
 *
 * This will query the linker and fill out as much information as it can about
 * a stack trace. Any entries where it could not find info will have Dl_info
 * members set to NULL.
 *
 * @param backtraceBuffer A backtrace generated by one of the bactrace_xx()
 *                       methods.
 *
 * @param symbolsBuffer A buffer to hold the symbolicated backtrace.
 *
 * @param numEntries The number of entries to examine.
 *
 * @param skippedEntries The number of entries skipped from the start of this backtrace.
 */
void ksbt_symbolicate(const uintptr_t* backtraceBuffer,
                      Dl_info* symbolsBuffer,
                      int numEntries,
                      int skippedEntries);


#ifdef __cplusplus
}
#endif

#endif // HDR_KSBacktrace_h
