# NSTD
A cross-platform, fast, and safe general purpose C library written in Rust.

The library is organized as a series of modules. The top level module `nstd` encompasses the entire
crate. Each module can have their own submodules (eg. `nstd.core.def` or `nstd::core::def` with
Rust syntax).

# Example using C
```c
// Build nstd with `cargo build --features "clib nstd_core nstd_io"`.
#include <nstd/core/str.h>
#include <nstd/io/io.h>

/// Main entry point of the program.
int main()
{
    const NSTDStr output = nstd_core_str_from_raw_cstr("Hello, 🌎!");
    nstd_io_print_line(&output);
    return 0;
}
```

# Modules
- `nstd` - A cross-platform, fast, and safe general purpose C library written in Rust.
    - `alloc` - Low level memory allocation.
    - `app` - An application event loop.
        - `data` - Application data passed to each event.
        - `display` - Provides access to physical displays.
        - `events` - Contains callback based events through function pointers.
    - `core` - Provides core functionality for `nstd`.
        - `cstr` - Unowned C string slices.
            - `raw` - Raw C string processing.
        - `cty` - Provides functions for examining and operating on character types.
        - `def` - Contains common types used throughout `nstd`.
        - `fty` - Provides functions for examining and operating on floating point types.
        - `ity` - Provides functions for examining and operating on integral types.
        - `math` - Low level math operations.
        - `mem` - Contains mostly unsafe functions for interacting with raw memory.
        - `ptr` - A sized pointer to some arbitrary type.
        - `range` - A numerical range.
        - `slice` - A view into a sequence of values in memory.
        - `str` - An unowned view into a UTF-8 encoded byte string.
    - `cstring` - A dynamically sized, null terminated, C string.
    - `fs` - Provides access to the file system.
        - `file` - A handle to an opened file.
    - `heap_ptr` - A pointer type for single value heap allocation.
    - `io` - Provides functionality for interacting with the standard I/O streams.
        - `stderr` - A handle to the standard error stream.
        - `stdin` - A handle to the standard input stream.
        - `stdout` - A handle to the standard output stream.
    - `math` - High level math operations.
    - `os` - Operating system specific functionality.
        - `windows` - OS support for Windows.
            - `alloc` - Low level memory allocation for Windows.
                - `heap` - Process heap management for Windows.
    - `shared_lib` - Access symbols from loaded shared libraries.
    - `shared_ptr` - A reference counting smart pointer.
    - `string` - Dynamically sized UTF-8 encoded byte string.
    - `vec` - A dynamically sized contiguous sequence of values.

# Platform support
`nstd.core` should support anything that rustc supports.

`nstd.os`'s child modules will only work on the operating system they target. For example,
`nstd.os.windows` will only work on Windows and `nstd.os.linux` will only work on Linux
distributions.

Other modules will work on most platforms, primarily targeting Windows, macOS,
Linux, Android, and iOS.

# Language support
This library can be accessed from any language that supports calling C code! As of now this will
need to be done manually as there are no official wrappers for the API, however whenever library
versioning occurs, the plan is to start adding official wrappers so developers from other languages
can easily use the API.

# Safety notes

- Raw pointers are unsafe to access.

- Raw pointer data is unsafe to mutate.

- Any function that may cause undefined behavior must be marked unsafe.

- Any operation that makes a direct call on a C function pointer is considered unsafe.

- The panic behavior is set to abort by default, as it is undefined behavior to unwind from Rust
code into foreign code (though this is
[subject to change](https://rust-lang.github.io/rfcs/2945-c-unwind-abi.html)).

- Reference arguments are assumed to be valid (aligned, non-null, and non-dangling), and are safe
to access.

# How to build
`nstd` lets you decide what features you want to use.

Any module that falls under the top level module has a dedicated feature flag, for example
`nstd.core` has the feature flag `nstd_core` and `nstd.alloc` has the feature flag `nstd_alloc`.

Each module may have additional features, for example `nstd.os` has the additional
`nstd_os_windows_alloc` feature for memory allocation on Windows, this allows other modules to use
the low level memory allocation API for Windows without enabling memory allocation for other
operating systems.

The `clib` feature flag is used to build `nstd` as a C library.

The `std` feature flag links the Rust standard library into the binary.

`std` and `nstd_core` are enabled by default.

Example:
```sh
cargo build --release --features "clib nstd_io nstd_string nstd_vec"
```

To build with all features:
```sh
cargo build --release --all-features
```
