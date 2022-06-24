#ifndef NSTD_CSTRING_H_INCLUDED
#define NSTD_CSTRING_H_INCLUDED
#include "core/cstr.h"
#include "core/def.h"
#include "nstd.h"
#include "vec.h"
NSTDCPPSTART

/// A dynamically sized, null terminated, C string.
typedef struct {
    /// The underlying vector of `NSTDChar`s.
    NSTDVec bytes;
} NSTDCString;

/// Creates a new empty `NSTDCString`.
///
/// # Returns
///
/// `NSTDCString cstring` - The new C string.
///
/// # Panics
///
/// This function will panic if allocating for the null byte fails.
NSTDAPI NSTDCString nstd_cstring_new();

/// Creates a new `NSTDCString` initialized with the given capacity.
///
/// # Parameters:
///
/// - `NSTDUSize cap` - The number of bytes to preallocate.
///
/// # Returns
///
/// `NSTDCString cstring` - The new C string.
///
/// # Panics
///
/// This function will panic if either `cap` is zero or allocating fails.
NSTDAPI NSTDCString nstd_cstring_new_with_cap(NSTDUSize cap);

/// Creates a deep copy of an `NSTDCString`.
///
/// # Parameters:
///
/// - `const NSTDCString *cstring` - The C string to create a deep copy of.
///
/// # Returns
///
/// `NSTDCString cloned` - A new deep copy of `cstring`.
///
/// # Panics
///
/// This function will panic if allocating for the new C string fails.
NSTDAPI NSTDCString nstd_cstring_clone(const NSTDCString *cstring);

/// Creates a C string slice containing the contents of `cstring` (excluding the null byte).
///
/// # Parameters:
///
/// - `NSTDCString *cstring` - The C string.
///
/// # Returns
///
/// `NSTDCStr cstr` - The new C string slice.
///
/// # Safety
///
/// `cstring`'s data must remain valid while the returned C string slice is in use.
NSTDAPI NSTDCStr nstd_cstring_as_cstr(NSTDCString *cstring);

/// Creates a C string slice containing the contents of `cstring` (excluding the null byte).
///
/// # Parameters:
///
/// - `const NSTDCString *cstring` - The C string.
///
/// # Returns
///
/// `NSTDCStrConst cstr` - The new C string slice.
///
/// # Safety
///
/// `cstring`'s data must remain valid while the returned C string slice is in use.
NSTDAPI NSTDCStrConst nstd_cstring_as_cstr_const(const NSTDCString *cstring);

/// Appends an `NSTDChar` to the end of an `NSTDCString`.
///
/// # Parameters:
///
/// - `NSTDCString *cstring` - The C string.
///
/// - `NSTDChar chr` - The C char to append to the C string.
///
/// # Panics
///
/// This operation panics if `chr` cannot be appended to the C string.
NSTDAPI void nstd_cstring_push(NSTDCString *cstring, NSTDChar chr);

/// Removes the last character from a C string and returns it.
///
/// # Parameters:
///
/// - `NSTDCString *cstring` - The C string.
///
/// # Returns
///
/// `NSTDChar chr` - The removed character, or null if the C string is empty.
NSTDAPI NSTDChar nstd_cstring_pop(NSTDCString *cstring);

/// Frees an instance of `NSTDCString`.
///
/// # Parameters:
///
/// - `NSTDCString *cstring` - The C string to free.
NSTDAPI void nstd_cstring_free(NSTDCString *cstring);

NSTDCPPEND
#endif
