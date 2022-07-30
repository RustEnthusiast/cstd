//! Provides functionality for interacting with the standard I/O streams.
use crate::{
    core::{
        cstr::{nstd_core_cstr_const_as_ptr, nstd_core_cstr_const_len, NSTDCStrConst},
        def::NSTDErrorCode,
    },
    string::{nstd_string_new, nstd_string_pop, NSTDString},
};
use std::io::{prelude::*, BufReader};

/// Writes a C string slice to stdout.
///
/// # Parameters:
///
/// - `const NSTDCStrConst *output` - The C string slice to write to stdout.
///
/// # Returns
///
/// `NSTDErrorCode errc` - Nonzero on error.
///
/// # Possible errors
///
/// - `1` - Writing `output`'s bytes to stdout failed.
///
/// - `2` - Flushing stdout failed.
///
/// # Safety
///
/// The provided C string slice's data must be valid, else this function can cause garbage bytes to
/// be written to stdout.
#[cfg_attr(feature = "clib", no_mangle)]
pub unsafe extern "C" fn nstd_io_print(output: &NSTDCStrConst) -> NSTDErrorCode {
    let ptr = nstd_core_cstr_const_as_ptr(output).cast();
    let len = nstd_core_cstr_const_len(output);
    let bytes = std::slice::from_raw_parts(ptr, len);
    let mut stdout = std::io::stdout();
    if let Err(_) = stdout.write_all(bytes) {
        return 1;
    } else if let Err(_) = stdout.flush() {
        return 2;
    }
    0
}

/// Reads a line of UTF-8 input from stdin and returns it, discarding the newline.
///
/// # Returns
///
/// `NSTDString input` - The input from stdin, or an empty string on error.
#[inline]
#[cfg_attr(feature = "clib", no_mangle)]
pub extern "C" fn nstd_io_read() -> NSTDString {
    let mut input = nstd_io_read_line();
    nstd_string_pop(&mut input);
    input
}

/// Reads a line of UTF-8 input from stdin and returns it.
///
/// # Returns
///
/// `NSTDString input` - The input from stdin, or an empty string on error.
#[cfg_attr(feature = "clib", no_mangle)]
pub extern "C" fn nstd_io_read_line() -> NSTDString {
    let mut buffer = String::new();
    if let Err(_) = BufReader::new(std::io::stdin()).read_line(&mut buffer) {
        return nstd_string_new();
    }
    NSTDString::from(buffer.as_str())
}
