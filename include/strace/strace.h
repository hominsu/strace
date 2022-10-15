// MIT License
//
// Copyright (c) 2022 HominSu
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

//
// Created by Homin Su on 2022/10/14.
//

#ifndef STRACE_INCLUDE_STRACE_STRACE_H_
#define STRACE_INCLUDE_STRACE_STRACE_H_

// @formatter:off
#if defined(_WIN64) || defined(WIN64) || defined(_WIN32) || defined(WIN32)
  #define STRACE_PLATFORM_STRING "windows"
  #define STRACE_WINDOWS 1
  #if defined(_WIN64) || defined(WIN64)
  #define STRACE_ARCH_64 1
  #else
  #define STRACE_ARCH_32 1
  #endif
#elif defined(__linux__)
  #define STRACE_PLATFORM_STRING "linux"
  #define STRACE_LINUX 1
  #ifdef _LP64
  #define STRACE_ARCH_64 1
  #else /* _LP64 */
  #define STRACE_ARCH_32 1
  #endif /* _LP64 */
#elif defined(__APPLE__)
  #define STRACE_PLATFORM_STRING "osx"
  #define STRACE_APPLE 1
  #ifdef _LP64
  #define STRACE_ARCH_64 1
  #else /* _LP64 */
  #define STRACE_ARCH_32 1
  #endif /* _LP64 */
#endif
// @formatter:on

#ifndef STRACE_WINDOWS
#define STRACE_WINDOWS 0
#endif

#ifndef STRACE_LINUX
#define STRACE_LINUX 0
#endif

#ifndef STRACE_APPLE
#define STRACE_APPLE 0
#endif

#ifndef STRACE_ARCH_32
#define STRACE_ARCH_32 0
#endif

#ifndef STRACE_ARCH_64
#define STRACE_ARCH_64 0
#endif

#if defined(__i386__)
#define STRACE_i386 1
#else
#define STRACE_i386 0
#endif

#if defined(__X86_64__)
#define STRACE_X86_64 1
#else
#define STRACE_X86_64 0
#endif

#if defined(__x86_64__)
#define STRACE_x86_64 1
#else
#define STRACE_x86_64 0
#endif

#if defined(__ia64__)
#define STRACE_ia64 1
#else
#define STRACE_ia64 0
#endif

#if defined(__arm__)
#define STRACE_arm 1
#else
#define STRACE_arm 0
#endif

#if defined(__aarch64__)
#define STRACE_aarch64 1
#else
#define STRACE_aarch64 0
#endif

#ifndef STRACE_UNUSED
#define STRACE_UNUSED(x) (void)(x)
#endif // STRACE_UNUSED

#endif //STRACE_INCLUDE_STRACE_STRACE_H_
