# Cracked Compiler

A compact C++ compiler for the Cracked language (.ced files). This repository contains the compiler sources, unit tests and CI configuration used by maintainers and contributors.

---

## Requirements:
- CMake (>= 3.20)
- A C++17-capable toolchain (MSVC on Windows, GCC/Clang on Linux/macOS)

## Quick start

From the project root (recommended out-of-source build):

* Create build directory and configure
```bash
cmake -S . -B build
```

* Build the compiler
```bash
cmake --build build
```

* Run the compiler
```bash
# Windows:
build/Debug/cracked_compiler.exe

# Linux / macOS
./build/cracked_compiler
```

---

## Unit tests (GoogleTest)

* Build the test target:

```bash
cmake --build build --target utest_lexer
```

* Run tests

```bash
ctest --test-dir build --output-on-failure
```

---

```
cracked
    ├── include                           <-- Public header files
    ├── src                               <-- Implementation files
    ├── test                              <-- Example `.ced` files used for manual testing
    ├── utest                             <-- GoogleTest unit tests and CMake test config
    └── CMakeLists.txt                    <-- Top-level CMake configuration
```
