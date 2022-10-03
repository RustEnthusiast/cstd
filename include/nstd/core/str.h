#ifndef NSTD_CORE_STR_H
#define NSTD_CORE_STR_H
#include "../nstd.h"
#include "cstr.h"
#include "def.h"
#include "range.h"
#include "slice.h"

/// An immutable unowned view into a UTF-8 encoded byte string.
typedef struct {
    /// A raw pointer to the string's data.
    const NSTDByte *ptr;
    /// The number of bytes in the string.
    NSTDUInt len;
} NSTDStr;

/// Creates a new instance of an `NSTDStr` from a C string slice.
///
/// # Parameters:
///
/// - `const NSTDCStr *cstr` - The C string slice to wrap.
///
/// # Returns
///
/// `NSTDStr str` - The new `NSTDStr` instance.
///
/// # Panics
///
/// This function will panic in the following situations:
///
/// - `cstr`'s data is not valid UTF-8.
///
/// - `cstr`'s length is greater than `NSTDInt`'s max value.
///
/// # Safety
///
/// `cstr`'s data must be valid for reads of at least `cstr.len` consecutive bytes.
///
/// # Example
///
/// ```
/// use nstd_sys::core::{
///     cstr::nstd_core_cstr_from_raw,
///     str::{nstd_core_str_byte_len, nstd_core_str_from_cstr},
/// };
///
/// let s_str = "Hello, world!\0";
/// unsafe {
///     let cstr = nstd_core_cstr_from_raw(s_str.as_ptr().cast());
///     let str = nstd_core_str_from_cstr(&cstr);
///     assert!(nstd_core_str_byte_len(&str) == 13);
/// }
/// ```
NSTDAPI NSTDStr nstd_core_str_from_cstr(const NSTDCStr *cstr);

/// Creates a new instance of an `NSTDStr` from a C string slice.
///
/// # Parameters:
///
/// - `const NSTDCStr *cstr` - The C string slice to wrap.
///
/// # Returns
///
/// `NSTDStr str` - The new `NSTDStr` instance.
///
/// # Safety
///
/// This function does not check to ensure that `cstr` is valid UTF-8. `cstr`'s data must remain
/// valid while the returned string slice is in use.
///
/// # Example
///
/// ```
/// use nstd_sys::core::{
///     cstr::nstd_core_cstr_from_raw,
///     str::{nstd_core_str_byte_len, nstd_core_str_from_cstr_unchecked},
/// };
///
/// let s_str = "Goodbye, world!\0";
/// unsafe {
///     let cstr = nstd_core_cstr_from_raw(s_str.as_ptr().cast());
///     let str = nstd_core_str_from_cstr_unchecked(&cstr);
///     assert!(nstd_core_str_byte_len(&str) == 15);
/// }
/// ```
NSTDAPI NSTDStr nstd_core_str_from_cstr_unchecked(const NSTDCStr *cstr);

/// Creates a new `NSTDStr` from a raw C string.
///
/// # Parameters:
///
/// - `const NSTDChar *cstr` - The raw C string to wrap.
///
/// # Returns
///
/// `NSTDStr str` - The new string slice.
///
/// # Panics
///
/// This function will panic in the following situations:
///
/// - `cstr`'s data is not valid UTF-8.
///
/// - `cstr`'s length is greater than `NSTDInt`'s max value.
///
/// # Safety
///
/// This function makes access to raw pointer data, which can cause undefined behavior in the event
/// that `cstr`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::str::{nstd_core_str_byte_len, nstd_core_str_from_raw_cstr};
///
/// let s_str = "Where I live is where I bleed.\0";
/// unsafe {
///     let str = nstd_core_str_from_raw_cstr(s_str.as_ptr().cast());
///     assert!(nstd_core_str_byte_len(&str) == 30);
/// }
/// ```
NSTDAPI NSTDStr nstd_core_str_from_raw_cstr(const NSTDChar *cstr);

/// Creates a new `NSTDStr` from a raw C string, including the null byte.
///
/// # Parameters:
///
/// - `const NSTDChar *cstr` - The raw C string to wrap.
///
/// # Returns
///
/// `NSTDStr str` - The new string slice.
///
/// # Panics
///
/// This function will panic in the following situations:
///
/// - `cstr`'s data is not valid UTF-8.
///
/// - `cstr`'s length is greater than `NSTDInt`'s max value.
///
/// # Safety
///
/// This function makes access to raw pointer data, which can cause undefined behavior in the event
/// that `cstr`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::str::{nstd_core_str_byte_len, nstd_core_str_from_raw_cstr_with_null};
///
/// let s_str = "{Hello, world!}}}%\0";
/// unsafe {
///     let str = nstd_core_str_from_raw_cstr_with_null(s_str.as_ptr().cast());
///     assert!(nstd_core_str_byte_len(&str) == 19);
/// }
/// ```
NSTDAPI NSTDStr nstd_core_str_from_raw_cstr_with_null(const NSTDChar *cstr);

/// Creates a string slice from raw bytes.
///
/// # Parameters:
///
/// - `const NSTDSlice *bytes` - The UTF-8 encoded byte slice.
///
/// # Returns
///
/// `NSTDStr str` - The new string slice.
///
/// # Panics
///
/// This operation will panic in the following situations:
///
/// - `bytes`'s stride is not 1.
///
/// - `bytes`'s length is greater than `NSTDInt`'s max value.
///
/// - `bytes` is not valid UTF-8.
///
/// # Safety
///
/// - `bytes` must remain valid while the returned string slice is in use.
///
/// - `bytes`'s data must be valid for reads of at least `bytes.len` consecutive bytes.
///
/// # Example
///
/// ```
/// use nstd_sys::core::{
///     slice::nstd_core_slice_new,
///     str::{nstd_core_str_byte_len, nstd_core_str_from_bytes},
/// };
///
/// let s_str = "Hello, world!\0";
/// unsafe {
///     let bytes = nstd_core_slice_new(s_str.as_ptr().cast(), 1, s_str.len());
///     let str = nstd_core_str_from_bytes(&bytes);
///     assert!(nstd_core_str_byte_len(&str) == 14);
/// }
/// ```
NSTDAPI NSTDStr nstd_core_str_from_bytes(const NSTDSlice *bytes);

/// Creates a string slice from raw bytes, without checking for UTF-8.
///
/// # Parameters:
///
/// - `const NSTDSlice *bytes` - The UTF-8 encoded byte slice.
///
/// # Returns
///
/// `NSTDStr str` - The new string slice.
///
/// # Panics
///
/// This operation will panic if `bytes`'s stride is not 1.
///
/// # Safety
///
/// - This function does not check to ensure that `bytes` are valid UTF-8.
///
/// - `bytes` must remain valid while the returned string slice is in use.
///
/// - `bytes`'s data must be valid for reads of at least `bytes.len` consecutive bytes.
///
/// # Example
///
/// ```
/// use nstd_sys::core::{
///     slice::nstd_core_slice_new,
///     str::{nstd_core_str_byte_len, nstd_core_str_from_bytes_unchecked},
/// };
///
/// let s_str = "Goodbye, world!\0";
/// unsafe {
///     let bytes = nstd_core_slice_new(s_str.as_ptr().cast(), 1, s_str.len());
///     let str = nstd_core_str_from_bytes_unchecked(&bytes);
///     assert!(nstd_core_str_byte_len(&str) == 16);
/// }
/// ```
NSTDAPI NSTDStr nstd_core_str_from_bytes_unchecked(const NSTDSlice *bytes);

/// Returns an immutable byte slice over `str`'s data.
///
/// # Parameters:
///
/// - `const NSTDStr *str` - The string slice.
///
/// # Returns
///
/// `NSTDSlice bytes` - An immutable byte slice over `str`'s data.
///
/// # Example
///
/// ```
/// use nstd_sys::core::{
///     slice::nstd_core_slice_len,
///     str::{nstd_core_str_as_bytes, nstd_core_str_byte_len, nstd_core_str_from_raw_cstr},
/// };
///
/// let s_str = "We won't be alone 🎶\0";
/// unsafe {
///     let str = nstd_core_str_from_raw_cstr(s_str.as_ptr().cast());
///     let bytes = nstd_core_str_as_bytes(&str);
///     assert!(nstd_core_str_byte_len(&str) == nstd_core_slice_len(&bytes));
/// }
/// ```
NSTDAPI NSTDSlice nstd_core_str_as_bytes(const NSTDStr *str);

/// Returns a raw pointer to a string slice's memory.
///
/// # Parameters:
///
/// - `const NSTDStr *str` - The string slice.
///
/// # Returns
///
/// `const NSTDByte *ptr` - A raw pointer to a string slice's memory.
NSTDAPI const NSTDByte *nstd_core_str_as_ptr(const NSTDStr *str);

/// Returns the number of Unicode characters in a string slice.
///
/// # Parameters:
///
/// - `const NSTDStr *str` - The string slice.
///
/// # Returns
///
/// `NSTDUInt len` - The length of the string slice.
///
/// # Panics
///
/// This operation may panic in the event that `str`'s length is greater than `NSTDInt`'s max
/// value.
///
/// # Safety
///
/// This operation can cause undefined behavior in the event that `str`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::str::{nstd_core_str_len, nstd_core_str_from_raw_cstr};
///
/// let s_str = "Hello, 🌎!\0";
/// unsafe {
///     let str = nstd_core_str_from_raw_cstr(s_str.as_ptr().cast());
///     assert!(nstd_core_str_len(&str) == 9);
/// }
/// ```
NSTDAPI NSTDUInt nstd_core_str_len(const NSTDStr *str);

/// Returns the number of bytes a string slice contains.
///
/// # Parameters:
///
/// - `const NSTDStr *str` - The string slice.
///
/// # Returns
///
/// `NSTDUInt byte_len` - The number of bytes in the string slice.
///
/// # Example
///
/// ```
/// use nstd_sys::core::str::{nstd_core_str_byte_len, nstd_core_str_from_raw_cstr_with_null};
///
/// let s_str = "Hello, 🌎!\0";
/// unsafe {
///     let str = nstd_core_str_from_raw_cstr_with_null(s_str.as_ptr().cast());
///     assert!(nstd_core_str_byte_len(&str) == s_str.len());
/// }
/// ```
NSTDAPI NSTDUInt nstd_core_str_byte_len(const NSTDStr *str);

/// Gets the `NSTDUnichar` at index `pos` in `str`.
///
/// # Note
///
/// `pos` does not refer to the byte index of the character, but the `NSTDUnichar` index instead.
///
/// # Parameters:
///
/// - `const NSTDStr *str` - The string slice to index.
///
/// - `NSTDUInt pos` - The index of the character to get.
///
/// # Returns
///
/// `NSTDUnichar chr` - The character at index `pos`, or the Unicode replacement character on
/// error.
///
/// # Panics
///
/// This operation may panic in the event that `str`'s length is greater than `NSTDInt`'s max
/// value.
///
/// # Safety
///
/// This operation can cause undefined behavior in the event that `str`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::str::{nstd_core_str_from_raw_cstr, nstd_core_str_get_char};
///
/// let s_str = "🦀🚀🦀!\0";
/// unsafe {
///     let str = nstd_core_str_from_raw_cstr(s_str.as_ptr().cast());
///     assert!(nstd_core_str_get_char(&str, 1) == '🚀'.into());
/// }
/// ```
NSTDAPI NSTDUnichar nstd_core_str_get_char(const NSTDStr *str, NSTDUInt pos);

/// Creates a substring of an existing string slice.
///
/// # Parameters:
///
/// - `const NSTDStr *str` - The string slice to create the new substring from.
///
/// - `NSTDURange range` - The bounds of the new substring (indexed by bytes).
///
/// # Returns
///
/// `NSTDStr substr` - The new substring.
///
/// # Panics
///
/// This operation can panic under the following circumstances:
///
/// - `range.start` is greater than `NSTDInt`'s max value.
///
/// - `range.start` is greater than `range.end`.
///
/// - `range.end` is greater than `str.len`.
///
/// - `range.end` - `range.start` is greater than `NSTDInt`'s max value.
///
/// - The substring bytes are not valid UTF-8.
///
/// # Safety
///
/// `str`'s data must be valid for reads of at least `str.len` consecutive bytes.
///
/// # Example
///
/// ```
/// use nstd_sys::core::{
///     range::NSTDURange,
///     str::{nstd_core_str_byte_len, nstd_core_str_from_raw_cstr, nstd_core_str_substr},
/// };
///
/// let s_str = "33marrow\0";
/// unsafe {
///     let str = nstd_core_str_from_raw_cstr(s_str.as_ptr().cast());
///     let range = NSTDURange {
///         start: 2,
///         end: nstd_core_str_byte_len(&str),
///     };
///     let marrow = nstd_core_str_substr(&str, range);
///     assert!(nstd_core_str_byte_len(&marrow) == 6);
/// }
/// ```
NSTDAPI NSTDStr nstd_core_str_substr(const NSTDStr *str, NSTDURange range);

/// Attempts to parse a string slice as an `NSTDFloat32`.
///
/// # Parameters:
///
/// - `const NSTDStr *str` - The string slice.
///
/// - `NSTDErrorCode *errc` - Set to nonzero on error.
///
/// # Returns
///
/// `NSTDFloat32 v` - The parsed 32-bit floating-point value.
///
/// # Panics
///
/// This operation may panic in the event that `str`'s length is greater than `NSTDInt`'s
/// max value.
///
/// # Safety
///
/// This operation can cause undefined behavior in the event that `str`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::str::{nstd_core_str_from_raw_cstr, nstd_core_str_to_f32};
///
/// let str = "-420.69\0";
/// unsafe {
///     let str = nstd_core_str_from_raw_cstr(str.as_ptr().cast());
///     let mut errc = 0;
///     nstd_core_str_to_f32(&str, &mut errc);
///     assert!(errc == 0);
/// }
/// ```
NSTDAPI NSTDFloat32 nstd_core_str_to_f32(const NSTDStr *str, NSTDErrorCode *errc);
/// Attempts to parse a string slice as an `NSTDFloat64`.
///
/// # Parameters:
///
/// - `const NSTDStr *str` - The string slice.
///
/// - `NSTDErrorCode *errc` - Set to nonzero on error.
///
/// # Returns
///
/// `NSTDFloat64 v` - The parsed 64-bit floating-point value.
///
/// # Panics
///
/// This operation may panic in the event that `str`'s length is greater than `NSTDInt`'s
/// max value.
///
/// # Safety
///
/// This operation can cause undefined behavior in the event that `str`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::str::{nstd_core_str_from_raw_cstr, nstd_core_str_to_f64};
///
/// let str = "-420.69\0";
/// unsafe {
///     let str = nstd_core_str_from_raw_cstr(str.as_ptr().cast());
///     let mut errc = 0;
///     nstd_core_str_to_f64(&str, &mut errc);
///     assert!(errc == 0);
/// }
/// ```
NSTDAPI NSTDFloat64 nstd_core_str_to_f64(const NSTDStr *str, NSTDErrorCode *errc);
/// Attempts to parse a string slice as an `NSTDInt`.
///
/// # Parameters:
///
/// - `const NSTDStr *str` - The string slice.
///
/// - `NSTDErrorCode *errc` - Set to nonzero on error.
///
/// # Returns
///
/// `NSTDInt v` - The parsed arch-bit signed integral value.
///
/// # Panics
///
/// This operation may panic in the event that `str`'s length is greater than `NSTDInt`'s
/// max value.
///
/// # Safety
///
/// This operation can cause undefined behavior in the event that `str`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::str::{nstd_core_str_from_raw_cstr, nstd_core_str_to_int};
///
/// let str = "33\0";
/// unsafe {
///     let str = nstd_core_str_from_raw_cstr(str.as_ptr().cast());
///     let mut errc = 0;
///     let v = nstd_core_str_to_int(&str, &mut errc);
///     assert!(errc == 0 && v == 33);
/// }
/// ```
NSTDAPI NSTDInt nstd_core_str_to_int(const NSTDStr *str, NSTDErrorCode *errc);
/// Attempts to parse a string slice as an `NSTDUInt`.
///
/// # Parameters:
///
/// - `const NSTDStr *str` - The string slice.
///
/// - `NSTDErrorCode *errc` - Set to nonzero on error.
///
/// # Returns
///
/// `NSTDUInt v` - The parsed arch-bit unsigned integral value.
///
/// # Panics
///
/// This operation may panic in the event that `str`'s length is greater than `NSTDInt`'s
/// max value.
///
/// # Safety
///
/// This operation can cause undefined behavior in the event that `str`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::str::{nstd_core_str_from_raw_cstr, nstd_core_str_to_uint};
///
/// let str = "33\0";
/// unsafe {
///     let str = nstd_core_str_from_raw_cstr(str.as_ptr().cast());
///     let mut errc = 0;
///     let v = nstd_core_str_to_uint(&str, &mut errc);
///     assert!(errc == 0 && v == 33);
/// }
/// ```
NSTDAPI NSTDUInt nstd_core_str_to_uint(const NSTDStr *str, NSTDErrorCode *errc);
/// Attempts to parse a string slice as an `NSTDInt8`.
///
/// # Parameters:
///
/// - `const NSTDStr *str` - The string slice.
///
/// - `NSTDErrorCode *errc` - Set to nonzero on error.
///
/// # Returns
///
/// `NSTDInt8 v` - The parsed 8-bit signed integral value.
///
/// # Panics
///
/// This operation may panic in the event that `str`'s length is greater than `NSTDInt`'s
/// max value.
///
/// # Safety
///
/// This operation can cause undefined behavior in the event that `str`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::str::{nstd_core_str_from_raw_cstr, nstd_core_str_to_i8};
///
/// let str = "33\0";
/// unsafe {
///     let str = nstd_core_str_from_raw_cstr(str.as_ptr().cast());
///     let mut errc = 0;
///     let v = nstd_core_str_to_i8(&str, &mut errc);
///     assert!(errc == 0 && v == 33);
/// }
/// ```
NSTDAPI NSTDInt8 nstd_core_str_to_i8(const NSTDStr *str, NSTDErrorCode *errc);
/// Attempts to parse a string slice as an `NSTDUInt8`.
///
/// # Parameters:
///
/// - `const NSTDStr *str` - The string slice.
///
/// - `NSTDErrorCode *errc` - Set to nonzero on error.
///
/// # Returns
///
/// `NSTDUInt8 v` - The parsed 8-bit unsigned integral value.
///
/// # Panics
///
/// This operation may panic in the event that `str`'s length is greater than `NSTDInt`'s
/// max value.
///
/// # Safety
///
/// This operation can cause undefined behavior in the event that `str`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::str::{nstd_core_str_from_raw_cstr, nstd_core_str_to_u8};
///
/// let str = "33\0";
/// unsafe {
///     let str = nstd_core_str_from_raw_cstr(str.as_ptr().cast());
///     let mut errc = 0;
///     let v = nstd_core_str_to_u8(&str, &mut errc);
///     assert!(errc == 0 && v == 33);
/// }
/// ```
NSTDAPI NSTDUInt8 nstd_core_str_to_u8(const NSTDStr *str, NSTDErrorCode *errc);
/// Attempts to parse a string slice as an `NSTDInt16`.
///
/// # Parameters:
///
/// - `const NSTDStr *str` - The string slice.
///
/// - `NSTDErrorCode *errc` - Set to nonzero on error.
///
/// # Returns
///
/// `NSTDInt16 v` - The parsed 16-bit signed integral value.
///
/// # Panics
///
/// This operation may panic in the event that `str`'s length is greater than `NSTDInt`'s
/// max value.
///
/// # Safety
///
/// This operation can cause undefined behavior in the event that `str`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::str::{nstd_core_str_from_raw_cstr, nstd_core_str_to_i16};
///
/// let str = "33\0";
/// unsafe {
///     let str = nstd_core_str_from_raw_cstr(str.as_ptr().cast());
///     let mut errc = 0;
///     let v = nstd_core_str_to_i16(&str, &mut errc);
///     assert!(errc == 0 && v == 33);
/// }
/// ```
NSTDAPI NSTDInt16 nstd_core_str_to_i16(const NSTDStr *str, NSTDErrorCode *errc);
/// Attempts to parse a string slice as an `NSTDUInt16`.
///
/// # Parameters:
///
/// - `const NSTDStr *str` - The string slice.
///
/// - `NSTDErrorCode *errc` - Set to nonzero on error.
///
/// # Returns
///
/// `NSTDUInt16 v` - The parsed 16-bit unsigned integral value.
///
/// # Panics
///
/// This operation may panic in the event that `str`'s length is greater than `NSTDInt`'s
/// max value.
///
/// # Safety
///
/// This operation can cause undefined behavior in the event that `str`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::str::{nstd_core_str_from_raw_cstr, nstd_core_str_to_u16};
///
/// let str = "33\0";
/// unsafe {
///     let str = nstd_core_str_from_raw_cstr(str.as_ptr().cast());
///     let mut errc = 0;
///     let v = nstd_core_str_to_u16(&str, &mut errc);
///     assert!(errc == 0 && v == 33);
/// }
/// ```
NSTDAPI NSTDUInt16 nstd_core_str_to_u16(const NSTDStr *str, NSTDErrorCode *errc);
/// Attempts to parse a string slice as an `NSTDInt32`.
///
/// # Parameters:
///
/// - `const NSTDStr *str` - The string slice.
///
/// - `NSTDErrorCode *errc` - Set to nonzero on error.
///
/// # Returns
///
/// `NSTDInt32 v` - The parsed 32-bit signed integral value.
///
/// # Panics
///
/// This operation may panic in the event that `str`'s length is greater than `NSTDInt`'s
/// max value.
///
/// # Safety
///
/// This operation can cause undefined behavior in the event that `str`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::str::{nstd_core_str_from_raw_cstr, nstd_core_str_to_i32};
///
/// let str = "33\0";
/// unsafe {
///     let str = nstd_core_str_from_raw_cstr(str.as_ptr().cast());
///     let mut errc = 0;
///     let v = nstd_core_str_to_i32(&str, &mut errc);
///     assert!(errc == 0 && v == 33);
/// }
/// ```
NSTDAPI NSTDInt32 nstd_core_str_to_i32(const NSTDStr *str, NSTDErrorCode *errc);
/// Attempts to parse a string slice as an `NSTDUInt32`.
///
/// # Parameters:
///
/// - `const NSTDStr *str` - The string slice.
///
/// - `NSTDErrorCode *errc` - Set to nonzero on error.
///
/// # Returns
///
/// `NSTDUInt32 v` - The parsed 32-bit unsigned integral value.
///
/// # Panics
///
/// This operation may panic in the event that `str`'s length is greater than `NSTDInt`'s
/// max value.
///
/// # Safety
///
/// This operation can cause undefined behavior in the event that `str`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::str::{nstd_core_str_from_raw_cstr, nstd_core_str_to_u32};
///
/// let str = "33\0";
/// unsafe {
///     let str = nstd_core_str_from_raw_cstr(str.as_ptr().cast());
///     let mut errc = 0;
///     let v = nstd_core_str_to_u32(&str, &mut errc);
///     assert!(errc == 0 && v == 33);
/// }
/// ```
NSTDAPI NSTDUInt32 nstd_core_str_to_u32(const NSTDStr *str, NSTDErrorCode *errc);
/// Attempts to parse a string slice as an `NSTDInt64`.
///
/// # Parameters:
///
/// - `const NSTDStr *str` - The string slice.
///
/// - `NSTDErrorCode *errc` - Set to nonzero on error.
///
/// # Returns
///
/// `NSTDInt64 v` - The parsed 64-bit signed integral value.
///
/// # Panics
///
/// This operation may panic in the event that `str`'s length is greater than `NSTDInt`'s
/// max value.
///
/// # Safety
///
/// This operation can cause undefined behavior in the event that `str`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::str::{nstd_core_str_from_raw_cstr, nstd_core_str_to_i64};
///
/// let str = "33\0";
/// unsafe {
///     let str = nstd_core_str_from_raw_cstr(str.as_ptr().cast());
///     let mut errc = 0;
///     let v = nstd_core_str_to_i64(&str, &mut errc);
///     assert!(errc == 0 && v == 33);
/// }
/// ```
NSTDAPI NSTDInt64 nstd_core_str_to_i64(const NSTDStr *str, NSTDErrorCode *errc);
/// Attempts to parse a string slice as an `NSTDUInt64`.
///
/// # Parameters:
///
/// - `const NSTDStr *str` - The string slice.
///
/// - `NSTDErrorCode *errc` - Set to nonzero on error.
///
/// # Returns
///
/// `NSTDUInt64 v` - The parsed 64-bit unsigned integral value.
///
/// # Panics
///
/// This operation may panic in the event that `str`'s length is greater than `NSTDInt`'s
/// max value.
///
/// # Safety
///
/// This operation can cause undefined behavior in the event that `str`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::str::{nstd_core_str_from_raw_cstr, nstd_core_str_to_u64};
///
/// let str = "33\0";
/// unsafe {
///     let str = nstd_core_str_from_raw_cstr(str.as_ptr().cast());
///     let mut errc = 0;
///     let v = nstd_core_str_to_u64(&str, &mut errc);
///     assert!(errc == 0 && v == 33);
/// }
/// ```
NSTDAPI NSTDUInt64 nstd_core_str_to_u64(const NSTDStr *str, NSTDErrorCode *errc);

/// An unowned view into a UTF-8 encoded byte string.
typedef struct {
    /// A raw pointer to the string's data.
    NSTDByte *ptr;
    /// The number of bytes in the string.
    NSTDUInt len;
} NSTDStrMut;

/// Creates a new instance of an `NSTDStrMut` from a C string slice.
///
/// # Parameters:
///
/// - `NSTDCStrMut *cstr` - The C string slice to wrap.
///
/// # Returns
///
/// `NSTDStrMut str` - The new `NSTDStrMut` instance.
///
/// # Panics
///
/// This function will panic in the following situations:
///
/// - `cstr`'s data is not valid UTF-8.
///
/// - `cstr`'s length is greater than `NSTDInt`'s max value.
///
/// # Safety
///
/// `cstr`'s data must be valid for reads of at least `cstr.len` consecutive bytes.
///
/// # Example
///
/// ```
/// use nstd_sys::core::{
///     cstr::nstd_core_cstr_mut_from_raw,
///     str::{nstd_core_str_mut_byte_len, nstd_core_str_mut_from_cstr},
/// };
///
/// let mut s_str = String::from("Hello, world!\0");
/// unsafe {
///     let mut cstr = nstd_core_cstr_mut_from_raw(s_str.as_mut_ptr().cast());
///     let str = nstd_core_str_mut_from_cstr(&mut cstr);
///     assert!(nstd_core_str_mut_byte_len(&str) == 13);
/// }
/// ```
NSTDAPI NSTDStrMut nstd_core_str_mut_from_cstr(NSTDCStrMut *cstr);

/// Creates a new instance of an `NSTDStrMut` from a C string slice.
///
/// # Parameters:
///
/// - `NSTDCStrMut *cstr` - The C string slice to wrap.
///
/// # Returns
///
/// `NSTDStrMut str` - The new `NSTDStrMut` instance.
///
/// # Safety
///
/// This function does not check to ensure that `cstr` is valid UTF-8. `cstr`'s data must remain
/// valid while the returned string slice is in use.
///
/// # Example
///
/// ```
/// use nstd_sys::core::{
///     cstr::nstd_core_cstr_mut_from_raw,
///     str::{nstd_core_str_mut_byte_len, nstd_core_str_mut_from_cstr_unchecked},
/// };
///
/// let mut s_str = String::from("Goodbye, world!\0");
/// unsafe {
///     let mut cstr = nstd_core_cstr_mut_from_raw(s_str.as_mut_ptr().cast());
///     let str = nstd_core_str_mut_from_cstr_unchecked(&mut cstr);
///     assert!(nstd_core_str_mut_byte_len(&str) == 15);
/// }
/// ```
NSTDAPI NSTDStrMut nstd_core_str_mut_from_cstr_unchecked(NSTDCStrMut *cstr);

/// Creates a new `NSTDStrMut` from a raw C string.
///
/// # Parameters:
///
/// - `NSTDChar *cstr` - The raw C string to wrap.
///
/// # Returns
///
/// `NSTDStrMut str` - The new string slice.
///
/// # Panics
///
/// This function will panic in the following situations:
///
/// - `cstr`'s data is not valid UTF-8.
///
/// - `cstr`'s length is greater than `NSTDInt`'s max value.
///
/// # Safety
///
/// This function makes access to raw pointer data, which can cause undefined behavior in the event
/// that `cstr`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::str::{nstd_core_str_mut_byte_len, nstd_core_str_mut_from_raw_cstr};
///
/// let mut s_str = String::from("Where I live is where I bleed.\0");
/// unsafe {
///     let str = nstd_core_str_mut_from_raw_cstr(s_str.as_mut_ptr().cast());
///     assert!(nstd_core_str_mut_byte_len(&str) == 30);
/// }
/// ```
NSTDAPI NSTDStrMut nstd_core_str_mut_from_raw_cstr(NSTDChar *cstr);

/// Creates a new `NSTDStrMut` from a raw C string, including the null byte.
///
/// # Parameters:
///
/// - `NSTDChar *cstr` - The raw C string to wrap.
///
/// # Returns
///
/// `NSTDStrMut str` - The new string slice.
///
/// # Panics
///
/// This function will panic in the following situations:
///
/// - `cstr`'s data is not valid UTF-8.
///
/// - `cstr`'s length is greater than `NSTDInt`'s max value.
///
/// # Safety
///
/// This function makes access to raw pointer data, which can cause undefined behavior in the event
/// that `cstr`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::str::{
///     nstd_core_str_mut_byte_len, nstd_core_str_mut_from_raw_cstr_with_null,
/// };
///
/// let mut s_str = String::from("{Hello, world!}}}%\0");
/// unsafe {
///     let str = nstd_core_str_mut_from_raw_cstr_with_null(s_str.as_mut_ptr().cast());
///     assert!(nstd_core_str_mut_byte_len(&str) == 19);
/// }
/// ```
NSTDAPI NSTDStrMut nstd_core_str_mut_from_raw_cstr_with_null(NSTDChar *cstr);

/// Creates a string slice from raw bytes.
///
/// # Parameters:
///
/// - `NSTDSliceMut *bytes` - The UTF-8 encoded byte slice.
///
/// # Returns
///
/// `NSTDStrMut str` - The new string slice.
///
/// # Panics
///
/// This operation will panic in the following situations:
///
/// - `bytes`'s stride is not 1.
///
/// - `bytes`'s length is greater than `NSTDInt`'s max value.
///
/// - `bytes` is not valid UTF-8.
///
/// # Safety
///
/// - `bytes` must remain valid while the returned string slice is in use.
///
/// - `bytes`'s data must be valid for reads of at least `bytes.len` consecutive bytes.
///
/// # Example
///
/// ```
/// use nstd_sys::core::{
///     slice::nstd_core_slice_mut_new,
///     str::{nstd_core_str_mut_byte_len, nstd_core_str_mut_from_bytes},
/// };
///
/// let mut s_str = String::from("Hello, world!\0");
/// unsafe {
///     let mut bytes = nstd_core_slice_mut_new(s_str.as_mut_ptr().cast(), 1, s_str.len());
///     let str = nstd_core_str_mut_from_bytes(&mut bytes);
///     assert!(nstd_core_str_mut_byte_len(&str) == 14);
/// }
/// ```
NSTDAPI NSTDStrMut nstd_core_str_mut_from_bytes(NSTDSliceMut *bytes);

/// Creates a string slice from raw bytes, without checking for UTF-8.
///
/// # Parameters:
///
/// - `NSTDSliceMut *bytes` - The UTF-8 encoded byte slice.
///
/// # Returns
///
/// `NSTDStrMut str` - The new string slice.
///
/// # Panics
///
/// This operation will panic if `bytes`'s stride is not 1.
///
/// # Safety
///
/// - This function does not check to ensure that `bytes` are valid UTF-8.
///
/// - `bytes` must remain valid while the returned string slice is in use.
///
/// - `bytes`'s data must be valid for reads of at least `bytes.len` consecutive bytes.
///
/// # Example
///
/// ```
/// use nstd_sys::core::{
///     slice::nstd_core_slice_mut_new,
///     str::{nstd_core_str_mut_byte_len, nstd_core_str_mut_from_bytes_unchecked},
/// };
///
/// let mut s_str = String::from("Goodbye, world!\0");
/// unsafe {
///     let mut bytes = nstd_core_slice_mut_new(s_str.as_mut_ptr().cast(), 1, s_str.len());
///     let str = nstd_core_str_mut_from_bytes_unchecked(&mut bytes);
///     assert!(nstd_core_str_mut_byte_len(&str) == 16);
/// }
/// ```
NSTDAPI NSTDStrMut nstd_core_str_mut_from_bytes_unchecked(NSTDSliceMut *bytes);

/// Creates an immutable version of a mutable string slice.
///
/// # Parameters:
///
/// - `const NSTDStrMut *str` - The mutable string slice.
///
/// # Returns
///
/// `NSTDStr str_const` - The immutable copy of `str`.
NSTDAPI NSTDStr nstd_core_str_mut_as_const(const NSTDStrMut *str);

/// Returns an immutable byte slice over `str`'s data.
///
/// # Parameters:
///
/// - `const NSTDStrMut *str` - The string slice.
///
/// # Returns
///
/// `NSTDSlice bytes` - An immutable byte slice over `str`'s data.
///
/// # Example
///
/// ```
/// use nstd_sys::core::{
///     slice::nstd_core_slice_len,
///     str::{
///         nstd_core_str_mut_as_bytes, nstd_core_str_mut_byte_len, nstd_core_str_mut_from_raw_cstr,
///     },
/// };
///
/// let mut s_str = String::from("We won't be alone 🎶\0");
/// unsafe {
///     let mut str = nstd_core_str_mut_from_raw_cstr(s_str.as_mut_ptr().cast());
///     let bytes = nstd_core_str_mut_as_bytes(&str);
///     assert!(nstd_core_str_mut_byte_len(&str) == nstd_core_slice_len(&bytes));
/// }
/// ```
NSTDAPI NSTDSlice nstd_core_str_mut_as_bytes(const NSTDStrMut *str);

/// Returns an immutable raw pointer to a string slice's memory.
///
/// # Parameters:
///
/// - `const NSTDStrMut *str` - The string slice.
///
/// # Returns
///
/// `const NSTDByte *ptr` - A raw pointer to a string slice's memory.
NSTDAPI const NSTDByte *nstd_core_str_mut_as_ptr(const NSTDStrMut *str);

/// Returns the number of Unicode characters in a string slice.
///
/// # Parameters:
///
/// - `const NSTDStrMut *str` - The string slice.
///
/// # Returns
///
/// `NSTDUInt len` - The length of the string slice.
///
/// # Panics
///
/// This operation may panic in the event that `str`'s length is greater than `NSTDInt`'s max
/// value.
///
/// # Safety
///
/// This operation can cause undefined behavior in the event that `str`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::str::{nstd_core_str_mut_len, nstd_core_str_mut_from_raw_cstr};
///
/// let mut s_str = String::from("Hello, 🌎!\0");
/// unsafe {
///     let str = nstd_core_str_mut_from_raw_cstr(s_str.as_mut_ptr().cast());
///     assert!(nstd_core_str_mut_len(&str) == 9);
/// }
/// ```
NSTDAPI NSTDUInt nstd_core_str_mut_len(const NSTDStrMut *str);

/// Returns the number of bytes a string slice contains.
///
/// # Parameters:
///
/// - `const NSTDStrMut *str` - The string slice.
///
/// # Returns
///
/// `NSTDUInt byte_len` - The number of bytes in the string slice.
///
/// # Example
///
/// ```
/// use nstd_sys::core::str::{
///     nstd_core_str_mut_byte_len, nstd_core_str_mut_from_raw_cstr_with_null,
/// };
///
/// let mut s_str = String::from("Hello, 🌎!\0");
/// unsafe {
///     let str = nstd_core_str_mut_from_raw_cstr_with_null(s_str.as_mut_ptr().cast());
///     assert!(nstd_core_str_mut_byte_len(&str) == s_str.len());
/// }
/// ```
NSTDAPI NSTDUInt nstd_core_str_mut_byte_len(const NSTDStrMut *str);

/// Gets the `NSTDUnichar` at index `pos` in `str`.
///
/// # Note
///
/// `pos` does not refer to the byte index of the character, but the `NSTDUnichar` index instead.
///
/// # Parameters:
///
/// - `const NSTDStrMut *str` - The string slice to index.
///
/// - `NSTDUInt pos` - The index of the character to get.
///
/// # Returns
///
/// `NSTDUnichar chr` - The character at index `pos`, or the Unicode replacement character on
/// error.
///
/// # Panics
///
/// This operation may panic in the event that `str`'s length is greater than `NSTDInt`'s max
/// value.
///
/// # Safety
///
/// This operation can cause undefined behavior in the event that `str`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::str::{nstd_core_str_mut_from_raw_cstr, nstd_core_str_mut_get_char};
///
/// let mut s_str = String::from("🦀🚀🦀!\0");
/// unsafe {
///     let str = nstd_core_str_mut_from_raw_cstr(s_str.as_mut_ptr().cast());
///     assert!(nstd_core_str_mut_get_char(&str, 1) == '🚀'.into());
/// }
/// ```
NSTDAPI NSTDUnichar nstd_core_str_mut_get_char(const NSTDStrMut *str, NSTDUInt pos);

/// Creates a substring of an existing string slice.
///
/// # Parameters:
///
/// - `NSTDStrMut *str` - The string slice to create the new substring from.
///
/// - `NSTDURange range` - The bounds of the new substring (indexed by bytes).
///
/// # Returns
///
/// `NSTDStrMut substr` - The new substring.
///
/// # Panics
///
/// This operation can panic under the following circumstances:
///
/// - `range.start` is greater than `NSTDInt`'s max value.
///
/// - `range.start` is greater than `range.end`.
///
/// - `range.end` is greater than `str.len`.
///
/// - `range.end` - `range.start` is greater than `NSTDInt`'s max value.
///
/// - The substring bytes are not valid UTF-8.
///
/// # Safety
///
/// `str`'s data must be valid for reads of at least `str.len` consecutive bytes.
///
/// # Example
///
/// ```
/// use nstd_sys::core::{
///     range::NSTDURange,
///     str::{
///         nstd_core_str_mut_byte_len, nstd_core_str_mut_from_raw_cstr, nstd_core_str_mut_substr,
///     },
/// };
///
/// let mut s_str = String::from("33marrow\0");
/// unsafe {
///     let mut str = nstd_core_str_mut_from_raw_cstr(s_str.as_mut_ptr().cast());
///     let range = NSTDURange {
///         start: 2,
///         end: nstd_core_str_mut_byte_len(&str),
///     };
///     let marrow = nstd_core_str_mut_substr(&mut str, range);
///     assert!(nstd_core_str_mut_byte_len(&marrow) == 6);
/// }
/// ```
NSTDAPI NSTDStrMut nstd_core_str_mut_substr(NSTDStrMut *str, NSTDURange range);

/// Attempts to parse a string slice as an `NSTDFloat32`.
///
/// # Parameters:
///
/// - `const NSTDStrMut *str` - The string slice.
///
/// - `NSTDErrorCode *errc` - Set to nonzero on error.
///
/// # Returns
///
/// `NSTDFloat32 v` - The parsed 32-bit floating-point value.
///
/// # Panics
///
/// This operation may panic in the event that `str`'s length is greater than `NSTDInt`'s
/// max value.
///
/// # Safety
///
/// This operation can cause undefined behavior in the event that `str`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::str::{nstd_core_str_mut_from_raw_cstr, nstd_core_str_mut_to_f32};
///
/// let mut str = String::from("-420.69\0");
/// unsafe {
///     let str = nstd_core_str_mut_from_raw_cstr(str.as_mut_ptr().cast());
///     let mut errc = 0;
///     nstd_core_str_mut_to_f32(&str, &mut errc);
///     assert!(errc == 0);
/// }
/// ```
NSTDAPI NSTDFloat32 nstd_core_str_mut_to_f32(const NSTDStrMut *str, NSTDErrorCode *errc);
/// Attempts to parse a string slice as an `NSTDFloat64`.
///
/// # Parameters:
///
/// - `const NSTDStrMut *str` - The string slice.
///
/// - `NSTDErrorCode *errc` - Set to nonzero on error.
///
/// # Returns
///
/// `NSTDFloat64 v` - The parsed 64-bit floating-point value.
///
/// # Panics
///
/// This operation may panic in the event that `str`'s length is greater than `NSTDInt`'s
/// max value.
///
/// # Safety
///
/// This operation can cause undefined behavior in the event that `str`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::str::{nstd_core_str_mut_from_raw_cstr, nstd_core_str_mut_to_f64};
///
/// let mut str = String::from("-420.69\0");
/// unsafe {
///     let str = nstd_core_str_mut_from_raw_cstr(str.as_mut_ptr().cast());
///     let mut errc = 0;
///     nstd_core_str_mut_to_f64(&str, &mut errc);
///     assert!(errc == 0);
/// }
/// ```
NSTDAPI NSTDFloat64 nstd_core_str_mut_to_f64(const NSTDStrMut *str, NSTDErrorCode *errc);
/// Attempts to parse a string slice as an `NSTDInt`.
///
/// # Parameters:
///
/// - `const NSTDStrMut *str` - The string slice.
///
/// - `NSTDErrorCode *errc` - Set to nonzero on error.
///
/// # Returns
///
/// `NSTDInt v` - The parsed arch-bit signed integral value.
///
/// # Panics
///
/// This operation may panic in the event that `str`'s length is greater than `NSTDInt`'s
/// max value.
///
/// # Safety
///
/// This operation can cause undefined behavior in the event that `str`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::str::{nstd_core_str_mut_from_raw_cstr, nstd_core_str_mut_to_int};
///
/// let mut str = String::from("33\0");
/// unsafe {
///     let str = nstd_core_str_mut_from_raw_cstr(str.as_mut_ptr().cast());
///     let mut errc = 0;
///     let v = nstd_core_str_mut_to_int(&str, &mut errc);
///     assert!(errc == 0 && v == 33);
/// }
/// ```
NSTDAPI NSTDInt nstd_core_str_mut_to_int(const NSTDStrMut *str, NSTDErrorCode *errc);
/// Attempts to parse a string slice as an `NSTDUInt`.
///
/// # Parameters:
///
/// - `const NSTDStrMut *str` - The string slice.
///
/// - `NSTDErrorCode *errc` - Set to nonzero on error.
///
/// # Returns
///
/// `NSTDUInt v` - The parsed arch-bit unsigned integral value.
///
/// # Panics
///
/// This operation may panic in the event that `str`'s length is greater than `NSTDInt`'s
/// max value.
///
/// # Safety
///
/// This operation can cause undefined behavior in the event that `str`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::str::{nstd_core_str_mut_from_raw_cstr, nstd_core_str_mut_to_uint};
///
/// let mut str = String::from("33\0");
/// unsafe {
///     let str = nstd_core_str_mut_from_raw_cstr(str.as_mut_ptr().cast());
///     let mut errc = 0;
///     let v = nstd_core_str_mut_to_uint(&str, &mut errc);
///     assert!(errc == 0 && v == 33);
/// }
/// ```
NSTDAPI NSTDUInt nstd_core_str_mut_to_uint(const NSTDStrMut *str, NSTDErrorCode *errc);
/// Attempts to parse a string slice as an `NSTDInt8`.
///
/// # Parameters:
///
/// - `const NSTDStrMut *str` - The string slice.
///
/// - `NSTDErrorCode *errc` - Set to nonzero on error.
///
/// # Returns
///
/// `NSTDInt8 v` - The parsed 8-bit signed integral value.
///
/// # Panics
///
/// This operation may panic in the event that `str`'s length is greater than `NSTDInt`'s
/// max value.
///
/// # Safety
///
/// This operation can cause undefined behavior in the event that `str`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::str::{nstd_core_str_mut_from_raw_cstr, nstd_core_str_mut_to_i8};
///
/// let mut str = String::from("33\0");
/// unsafe {
///     let str = nstd_core_str_mut_from_raw_cstr(str.as_mut_ptr().cast());
///     let mut errc = 0;
///     let v = nstd_core_str_mut_to_i8(&str, &mut errc);
///     assert!(errc == 0 && v == 33);
/// }
/// ```
NSTDAPI NSTDInt8 nstd_core_str_mut_to_i8(const NSTDStrMut *str, NSTDErrorCode *errc);
/// Attempts to parse a string slice as an `NSTDUInt8`.
///
/// # Parameters:
///
/// - `const NSTDStrMut *str` - The string slice.
///
/// - `NSTDErrorCode *errc` - Set to nonzero on error.
///
/// # Returns
///
/// `NSTDUInt8 v` - The parsed 8-bit unsigned integral value.
///
/// # Panics
///
/// This operation may panic in the event that `str`'s length is greater than `NSTDInt`'s
/// max value.
///
/// # Safety
///
/// This operation can cause undefined behavior in the event that `str`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::str::{nstd_core_str_mut_from_raw_cstr, nstd_core_str_mut_to_u8};
///
/// let mut str = String::from("33\0");
/// unsafe {
///     let str = nstd_core_str_mut_from_raw_cstr(str.as_mut_ptr().cast());
///     let mut errc = 0;
///     let v = nstd_core_str_mut_to_u8(&str, &mut errc);
///     assert!(errc == 0 && v == 33);
/// }
/// ```
NSTDAPI NSTDUInt8 nstd_core_str_mut_to_u8(const NSTDStrMut *str, NSTDErrorCode *errc);
/// Attempts to parse a string slice as an `NSTDInt16`.
///
/// # Parameters:
///
/// - `const NSTDStrMut *str` - The string slice.
///
/// - `NSTDErrorCode *errc` - Set to nonzero on error.
///
/// # Returns
///
/// `NSTDInt16 v` - The parsed 16-bit signed integral value.
///
/// # Panics
///
/// This operation may panic in the event that `str`'s length is greater than `NSTDInt`'s
/// max value.
///
/// # Safety
///
/// This operation can cause undefined behavior in the event that `str`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::str::{nstd_core_str_mut_from_raw_cstr, nstd_core_str_mut_to_i16};
///
/// let mut str = String::from("33\0");
/// unsafe {
///     let str = nstd_core_str_mut_from_raw_cstr(str.as_mut_ptr().cast());
///     let mut errc = 0;
///     let v = nstd_core_str_mut_to_i16(&str, &mut errc);
///     assert!(errc == 0 && v == 33);
/// }
/// ```
NSTDAPI NSTDInt16 nstd_core_str_mut_to_i16(const NSTDStrMut *str, NSTDErrorCode *errc);
/// Attempts to parse a string slice as an `NSTDUInt16`.
///
/// # Parameters:
///
/// - `const NSTDStrMut *str` - The string slice.
///
/// - `NSTDErrorCode *errc` - Set to nonzero on error.
///
/// # Returns
///
/// `NSTDUInt16 v` - The parsed 16-bit unsigned integral value.
///
/// # Panics
///
/// This operation may panic in the event that `str`'s length is greater than `NSTDInt`'s
/// max value.
///
/// # Safety
///
/// This operation can cause undefined behavior in the event that `str`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::str::{nstd_core_str_mut_from_raw_cstr, nstd_core_str_mut_to_u16};
///
/// let mut str = String::from("33\0");
/// unsafe {
///     let str = nstd_core_str_mut_from_raw_cstr(str.as_mut_ptr().cast());
///     let mut errc = 0;
///     let v = nstd_core_str_mut_to_u16(&str, &mut errc);
///     assert!(errc == 0 && v == 33);
/// }
/// ```
NSTDAPI NSTDUInt16 nstd_core_str_mut_to_u16(const NSTDStrMut *str, NSTDErrorCode *errc);
/// Attempts to parse a string slice as an `NSTDInt32`.
///
/// # Parameters:
///
/// - `const NSTDStrMut *str` - The string slice.
///
/// - `NSTDErrorCode *errc` - Set to nonzero on error.
///
/// # Returns
///
/// `NSTDInt32 v` - The parsed 32-bit signed integral value.
///
/// # Panics
///
/// This operation may panic in the event that `str`'s length is greater than `NSTDInt`'s
/// max value.
///
/// # Safety
///
/// This operation can cause undefined behavior in the event that `str`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::str::{nstd_core_str_mut_from_raw_cstr, nstd_core_str_mut_to_i32};
///
/// let mut str = String::from("33\0");
/// unsafe {
///     let str = nstd_core_str_mut_from_raw_cstr(str.as_mut_ptr().cast());
///     let mut errc = 0;
///     let v = nstd_core_str_mut_to_i32(&str, &mut errc);
///     assert!(errc == 0 && v == 33);
/// }
/// ```
NSTDAPI NSTDInt32 nstd_core_str_mut_to_i32(const NSTDStrMut *str, NSTDErrorCode *errc);
/// Attempts to parse a string slice as an `NSTDUInt32`.
///
/// # Parameters:
///
/// - `const NSTDStrMut *str` - The string slice.
///
/// - `NSTDErrorCode *errc` - Set to nonzero on error.
///
/// # Returns
///
/// `NSTDUInt32 v` - The parsed 32-bit unsigned integral value.
///
/// # Panics
///
/// This operation may panic in the event that `str`'s length is greater than `NSTDInt`'s
/// max value.
///
/// # Safety
///
/// This operation can cause undefined behavior in the event that `str`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::str::{nstd_core_str_mut_from_raw_cstr, nstd_core_str_mut_to_u32};
///
/// let mut str = String::from("33\0");
/// unsafe {
///     let str = nstd_core_str_mut_from_raw_cstr(str.as_mut_ptr().cast());
///     let mut errc = 0;
///     let v = nstd_core_str_mut_to_u32(&str, &mut errc);
///     assert!(errc == 0 && v == 33);
/// }
/// ```
NSTDAPI NSTDUInt32 nstd_core_str_mut_to_u32(const NSTDStrMut *str, NSTDErrorCode *errc);
/// Attempts to parse a string slice as an `NSTDInt64`.
///
/// # Parameters:
///
/// - `const NSTDStrMut *str` - The string slice.
///
/// - `NSTDErrorCode *errc` - Set to nonzero on error.
///
/// # Returns
///
/// `NSTDInt64 v` - The parsed 64-bit signed integral value.
///
/// # Panics
///
/// This operation may panic in the event that `str`'s length is greater than `NSTDInt`'s
/// max value.
///
/// # Safety
///
/// This operation can cause undefined behavior in the event that `str`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::str::{nstd_core_str_mut_from_raw_cstr, nstd_core_str_mut_to_i64};
///
/// let mut str = String::from("33\0");
/// unsafe {
///     let str = nstd_core_str_mut_from_raw_cstr(str.as_mut_ptr().cast());
///     let mut errc = 0;
///     let v = nstd_core_str_mut_to_i64(&str, &mut errc);
///     assert!(errc == 0 && v == 33);
/// }
/// ```
NSTDAPI NSTDInt64 nstd_core_str_mut_to_i64(const NSTDStrMut *str, NSTDErrorCode *errc);
/// Attempts to parse a string slice as an `NSTDUInt64`.
///
/// # Parameters:
///
/// - `const NSTDStrMut *str` - The string slice.
///
/// - `NSTDErrorCode *errc` - Set to nonzero on error.
///
/// # Returns
///
/// `NSTDUInt64 v` - The parsed 64-bit unsigned integral value.
///
/// # Panics
///
/// This operation may panic in the event that `str`'s length is greater than `NSTDInt`'s
/// max value.
///
/// # Safety
///
/// This operation can cause undefined behavior in the event that `str`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::str::{nstd_core_str_mut_from_raw_cstr, nstd_core_str_mut_to_u64};
///
/// let mut str = String::from("33\0");
/// unsafe {
///     let str = nstd_core_str_mut_from_raw_cstr(str.as_mut_ptr().cast());
///     let mut errc = 0;
///     let v = nstd_core_str_mut_to_u64(&str, &mut errc);
///     assert!(errc == 0 && v == 33);
/// }
/// ```
NSTDAPI NSTDUInt64 nstd_core_str_mut_to_u64(const NSTDStrMut *str, NSTDErrorCode *errc);

#endif
