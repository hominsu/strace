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

#include "get_m_context_addr.h"
#include "strace/stack_trace.h"
#include "strace/strace.h"

#include <csignal>
#include <cstdio>
#include <cstring>
#include <execinfo.h>
#include <unistd.h>

namespace strace {
inline namespace v1 {

#ifdef __cplusplus
extern "C" {
#endif

void print_stack(ucontext_t *uc) {
  const int kMaxFrames = 100;
  void *frames[kMaxFrames + 1];

  auto num_frames = backtrace(frames + 1, kMaxFrames);
  auto addr = ::strace::v1::getRaisedAddress(uc);
  if (addr != nullptr) {
    frames[0] = addr;
    backtrace_symbols_fd(frames, 1, STDERR_FILENO);
  }
  backtrace_symbols_fd(frames + 1, num_frames, STDERR_FILENO);
}

void sigHandler(int sig, siginfo_t *info, void *ucontext) {
  STRACE_UNUSED(info);

  auto *uc = (ucontext_t *) ucontext;
  auto raised_address = ::strace::v1::getRaisedAddress(uc);

  fprintf(stderr, "Crashed by signal %d (%s)\n", sig, strsignal(sig));
  if (raised_address != nullptr) {
    fprintf(stderr, "Crashed running the instruction at: %p\n", raised_address);
  }
  if (sig == SIGSEGV || sig == SIGBUS) {
    fprintf(stderr, "Accessing address: %p\n", info->si_addr);
  }
  print_stack(uc);

  std::raise(sig);
}

void InstallSignalHandlers() {
  struct sigaction act{};

  sigemptyset(&act.sa_mask);
  act.sa_flags = SA_NODEFER | SA_RESETHAND | SA_SIGINFO;
  act.sa_sigaction = sigHandler;
  sigaction(SIGILL, &act, nullptr);
  sigaction(SIGSEGV, &act, nullptr);
  sigaction(SIGBUS, &act, nullptr);
  sigaction(SIGABRT, &act, nullptr);
}

#ifdef __cplusplus
}
#endif


} // namespace v1
} // namespace strace
