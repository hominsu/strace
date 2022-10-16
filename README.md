<!-- PROJECT LOGO -->
<br/>
<div align="center">
<!--   <a href="https://github.com/hominsu/strace">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a> -->

<h3 align="center">strace</h3>

  <p align="center">
    Get the process call stack before coredump is generated
    <br/>
    <a href="https://me.hauhau.cn/projects/strace/"><strong>Explore the docs »</strong></a>
    <br/>
    <br/>
    <a href="https://github.com/hominsu/strace">View Demo</a>
    ·
    <a href="https://github.com/hominsu/strace/issues">Report Bug</a>
    ·
    <a href="https://github.com/hominsu/strace/issues">Request Feature</a>
  </p>
</div>

##### Translate to: [简体中文](README_zh.md)

## Description

strace supports both C and C++, and it can runs on Linux and OSX, supports i386, amd64, arm and other platforms.

## Install

### clone the strace repo

```bash
git clone https://github.com/hominsu/strace.git
```

### Build and install

The following commands build and locally install strace:

```bash
cd strace
mkdir -p cmake/build
pushd cmake/build
cmake ../..
make -j
make install
popd
```

#### Build with example

The example code is part of the `strace` repo source, which you cloned as part of the steps of the previous section, just add a cmake option:

```bash
cmake -DNEUJSON_BUILD_EXAMPLES=ON ../..
```

## Uninstall

The following commands uninstall strace:

```bash
pushd cmake/build
make uninstall
popd
```

## Usage at a glance

##### C:

```c
#include "strace/stack_trace.h"

#include <signal.h>
#include <stdio.h>

void foo() __attribute__((noinline));
void bar() __attribute__((noinline));

void foo() {
  bar();
}

void bar() {
  int *p = (int *) -1;
  printf("%d\n", *p);
}

int main(int argc, char *argv[]) {
  (void) argc;
  (void) argv;

  int sigs[] = {SIGILL, SIGSEGV, SIGBUS, SIGABRT};
  InstallSignalHandlers(sigs, sizeof(sigs) / sizeof(int));

  foo();

  return 0;
}
```

Output:

```bash
Crashed by signal 11 (Segmentation fault: 11)
Crashed running the instruction at: 0x102463ef0
Accessing address: 0xffffffffffffffff
0   stack_trace_cc                      0x0000000102463ef0 bar + 16
0   libstrace.dylib                     0x000000010257be20 sigHandler + 188
1   libsystem_platform.dylib            0x00000001982f74a4 _sigtramp + 56
2   stack_trace_cc                      0x0000000102463f4c main + 60
3   stack_trace_cc                      0x0000000102463f4c main + 60
4   dyld                                0x00000001026a508c start + 520
```

##### C++:

```cpp
#include "strace/stack_trace.h"

#include <csignal>
#include <cstdio>

class bar {
 private:
  int *p = (int *) -1;

 public:
  __attribute__((noinline)) void print_in_bar() {
    printf("%d\n", *p);
  }
};

class foo : public bar {
 public:
  __attribute__((noinline)) void print_in_foo() {
    print_in_bar();
  }
};

int main(int argc, char *argv[]) {
  (void) argc;
  (void) argv;

  int sigs[] = {SIGILL, SIGSEGV, SIGBUS, SIGABRT};
  strace::InstallSignalHandlers(sigs, sizeof(sigs) / sizeof(int));

  foo().print_in_foo();

  return 0;
}
```

Output:

```bash
Crashed by signal 11 (Segmentation fault: 11)
Crashed running the instruction at: 0x104237f4c
Accessing address: 0xffffffffffffffff
0   stack_trace_cxx                     0x0000000104237f4c _ZN3bar12print_in_barEv + 16
0   libstrace.dylib                     0x000000010434fe20 sigHandler + 188
1   libsystem_platform.dylib            0x00000001982f74a4 _sigtramp + 56
2   stack_trace_cxx                     0x0000000104237f0c main + 72
3   stack_trace_cxx                     0x0000000104237f0c main + 72
4   dyld                                0x000000010457908c start + 520
```

