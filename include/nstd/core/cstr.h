#ifndef NSTD_CORE_CSTR_H_INCLUDED
#define NSTD_CORE_CSTR_H_INCLUDED
#include "../nstd.h"
#include "def.h"
#include "slice.h"
NSTDCPPSTART

/// Creates a byte slice over a C string, excluding the null terminator.
///
/// # Parameters:
///
/// - `NSTDChar *cstr` - The C string to create a slice for.
///
/// # Returns
///
/// `NSTDSlice slice` - The new byte slice over the C string (without the null byte at the end).
NSTDAPI NSTDSlice nstd_core_cstr_as_slice(NSTDChar *cstr);

/// Creates a byte slice over a C string, including the null terminator.
///
/// # Parameters:
///
/// - `NSTDChar *cstr` - The C string to create a slice for.
///
/// # Returns
///
/// `NSTDSlice slice` - The new byte slice over the C string (including the null byte at the end).
NSTDAPI NSTDSlice nstd_core_cstr_as_slice_with_null(NSTDChar *cstr);

/// Gets the length of a null terminated C string, excluding the null byte.
///
/// # Parameters:
///
/// - `const NSTDChar *cstr` - The null terminated C string.
///
/// # Returns
///
/// `NSTDUSize len` - The length of the C string, excluding the null byte.
///
/// # Safety
///
/// The C string's buffer may not be large enough to contain the null byte, resulting in an
/// incorrect length.
NSTDAPI NSTDUSize nstd_core_cstr_len(const NSTDChar *cstr);

/// Gets the length of a null terminated C string, including the null byte.
///
/// # Parameters:
///
/// - `const NSTDChar *cstr` - The null terminated C string.
///
/// # Returns
///
/// `NSTDUSize len` - The length of the C string, including the null byte.
///
/// # Safety
///
/// The C string's buffer may not be large enough to contain the null byte, resulting in an
/// incorrect length.
NSTDAPI NSTDUSize nstd_core_cstr_len_with_null(const NSTDChar *cstr);

/// Compares two C strings, returning `NSTD_BOOL_TRUE` if they are lexicographically equal.
///
/// # Parameters:
///
/// - `const NSTDChar *cstr1` - The first C string.
///
/// - `const NSTDChar *cstr2` - The second C string.
///
/// # Returns
///
/// `NSTDBool is_eq` - `NSTD_BOOL_TRUE` if the C strings are lexicographically equal.
///
/// # Safety
///
/// This function is unsafe because the C string's null byte may be outside of it's memory buffer.
NSTDAPI NSTDBool nstd_core_cstr_compare(const NSTDChar *cstr1, const NSTDChar *cstr2);

/// Copies the contents of `src` to `dest`, excluding the null terminator.
///
/// # Note
///
/// If you already know how many bytes should be copied, `nstd_core_mem_copy[_overlapped]` should
/// be used instead.
///
/// # Parameters:
///
/// - `NSTDChar *dest` - The C string buffer to copy data to.
///
/// - `const NSTDChar *src` - The C string to copy data from.
///
/// # Safety
///
/// This operation is highly unsafe because it cannot guarantee that it won't write past the end of
/// `dest`'s memory buffer.
NSTDAPI void nstd_core_cstr_copy(NSTDChar *dest, const NSTDChar *src);

/// Copies the contents of `src` to `dest`, including the null terminator.
///
/// # Note
///
/// If you already know how many bytes should be copied, `nstd_core_mem_copy[_overlapped]` should
/// be used instead.
///
/// # Parameters:
///
/// - `NSTDChar *dest` - The C string buffer to copy data to.
///
/// - `const NSTDChar *src` - The C string to copy data from.
///
/// # Safety
///
/// This operation is highly unsafe because it cannot guarantee that it won't write past the end of
/// `dest`'s memory buffer.
NSTDAPI void nstd_core_cstr_copy_with_null(NSTDChar *dest, const NSTDChar *src);

NSTDCPPEND
#endif
