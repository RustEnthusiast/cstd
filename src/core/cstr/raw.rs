//! Raw C string processing.
use crate::{core::def::NSTDChar, NSTDBool, NSTDUInt, NSTD_FALSE, NSTD_TRUE};

/// Gets the length of a null terminated C string, excluding the null byte.
///
/// # Parameters:
///
/// - `const NSTDChar *cstr` - The null terminated C string.
///
/// # Returns
///
/// `NSTDUInt len` - The length of the C string, excluding the null byte.
///
/// # Safety
///
/// This function makes access raw pointer data, which can cause undefined behavior in the event
/// that `cstr`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::cstr::raw::nstd_core_cstr_raw_len;
///
/// let cstr = b"Hello, world!\0";
/// assert!(unsafe { nstd_core_cstr_raw_len(cstr.as_ptr().cast()) } == 13);
/// ```
#[inline]
#[cfg_attr(feature = "clib", no_mangle)]
pub unsafe extern "C" fn nstd_core_cstr_raw_len(cstr: *const NSTDChar) -> NSTDUInt {
    #[cfg(not(any(target_arch = "x86", target_arch = "x86_64")))]
    {
        let mut i = 0;
        while *cstr.add(i) != 0 {
            i += 1;
        }
        i
    }
    #[cfg(any(target_arch = "x86", target_arch = "x86_64"))]
    {
        use core::arch::asm;
        let i;
        asm!(include_str!("raw/len.asm"), cstr = in(reg) cstr, i = out(reg) i);
        i
    }
}

/// Gets the length of a null terminated C string, including the null byte.
///
/// # Parameters:
///
/// - `const NSTDChar *cstr` - The null terminated C string.
///
/// # Returns
///
/// `NSTDUInt len` - The length of the C string, including the null byte.
///
/// # Safety
///
/// This function makes access raw pointer data, which can cause undefined behavior in the event
/// that `cstr`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::cstr::raw::nstd_core_cstr_raw_len_with_null;
///
/// let cstr = b"Hello, world!\0";
/// assert!(unsafe { nstd_core_cstr_raw_len_with_null(cstr.as_ptr().cast()) } == 14);
/// ```
#[inline]
#[cfg_attr(feature = "clib", no_mangle)]
pub unsafe extern "C" fn nstd_core_cstr_raw_len_with_null(cstr: *const NSTDChar) -> NSTDUInt {
    nstd_core_cstr_raw_len(cstr) + 1
}

/// Compares two C strings, returning `NSTD_TRUE` if they are lexicographically equal.
///
/// # Parameters:
///
/// - `const NSTDChar *cstr1` - The first C string.
///
/// - `const NSTDChar *cstr2` - The second C string.
///
/// # Returns
///
/// `NSTDBool is_eq` - `NSTD_TRUE` if the C strings are lexicographically equal.
///
/// # Safety
///
/// This function makes access raw pointer data, which can cause undefined behavior in the event
/// that either `cstr1` or `cstr2`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::{core::cstr::raw::nstd_core_cstr_raw_compare, NSTD_FALSE};
///
/// let cstr1 = b"Hello, world!\0".as_ptr().cast();
/// let cstr2 = b"Hello world!\0".as_ptr().cast();
///
/// assert!(unsafe { nstd_core_cstr_raw_compare(cstr1, cstr2) } == NSTD_FALSE);
/// ```
#[cfg_attr(feature = "clib", no_mangle)]
pub unsafe extern "C" fn nstd_core_cstr_raw_compare(
    mut cstr1: *const NSTDChar,
    mut cstr2: *const NSTDChar,
) -> NSTDBool {
    // If the C strings point to the same data return true.
    if cstr1 == cstr2 {
        return NSTD_TRUE;
    }
    // Otherwise compare them lexicographically.
    loop {
        if *cstr1 != *cstr2 {
            return NSTD_FALSE;
        } else if *cstr1 == 0 {
            return NSTD_TRUE;
        }
        cstr1 = cstr1.add(1);
        cstr2 = cstr2.add(1);
    }
}

/// Copies the contents of `src` to `dest`, excluding the null terminator.
///
/// # Note
///
/// If you already know how many bytes should be copied, `nstd_core_mem_copy[_overlapped]` should
/// be used instead as it can minimize execution times.
///
/// # Parameters:
///
/// - `NSTDChar *dest` - The C string buffer to copy data to.
///
/// - `const NSTDChar *src` - The C string to copy data from.
///
/// # Safety
///
/// This function reads from/writes to raw pointer data, which can cause undefined behavior in the
/// event that either `dest` or `src`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::{cstr::raw::nstd_core_cstr_raw_copy, def::NSTDChar};
///
/// let cstr = b"Hello, world!\0";
/// let mut buffer = [0u8; 14];
///
/// unsafe { nstd_core_cstr_raw_copy(buffer.as_mut_ptr().cast(), cstr.as_ptr().cast()) };
/// assert!(&buffer == cstr);
/// ```
#[inline]
#[cfg_attr(feature = "clib", no_mangle)]
pub unsafe extern "C" fn nstd_core_cstr_raw_copy(
    mut dest: *mut NSTDChar,
    mut src: *const NSTDChar,
) {
    while *src != 0 {
        *dest = *src;
        dest = dest.add(1);
        src = src.add(1);
    }
}

/// Copies the contents of `src` to `dest`, including the null terminator.
///
/// # Note
///
/// If you already know how many bytes should be copied, `nstd_core_mem_copy[_overlapped]` should
/// be used instead as it can minimize execution times.
///
/// # Parameters:
///
/// - `NSTDChar *dest` - The C string buffer to copy data to.
///
/// - `const NSTDChar *src` - The C string to copy data from.
///
/// # Safety
///
/// This function reads from/writes to raw pointer data, which can cause undefined behavior in the
/// event that either `dest` or `src`'s data is invalid.
///
/// # Example
///
/// ```
/// use nstd_sys::core::{cstr::raw::nstd_core_cstr_raw_copy_with_null, def::NSTDChar};
///
/// let cstr = b"Hello, world!\0";
/// let mut buffer = [u8::MAX; 14];
///
/// let buf_ptr = buffer.as_mut_ptr().cast();
/// unsafe { nstd_core_cstr_raw_copy_with_null(buf_ptr, cstr.as_ptr().cast()) };
/// assert!(&buffer == cstr);
/// ```
#[inline]
#[cfg_attr(feature = "clib", no_mangle)]
pub unsafe extern "C" fn nstd_core_cstr_raw_copy_with_null(
    mut dest: *mut NSTDChar,
    mut src: *const NSTDChar,
) {
    while {
        *dest = *src;
        *src != 0
    } {
        dest = dest.add(1);
        src = src.add(1);
    }
}
