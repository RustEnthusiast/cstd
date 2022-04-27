//! An unowned view into a UTF-8 encoded byte string.
use crate::core::{
    cstr::nstd_core_cstr_len,
    def::NSTDChar,
    slice::{nstd_core_slice_new, NSTDSlice},
};

/// An unowned view into a UTF-8 encoded byte string.
#[repr(C)]
#[derive(Clone, Copy, Debug, Hash)]
pub struct NSTDStr {
    /// A view into the UTF-8 encoded buffer.
    pub bytes: NSTDSlice,
}

/// Creates a new instance of `NSTDStr` from a UTF-8 encoded C string.
///
/// # Parameters:
///
/// - `NSTDChar *cstr` - The C string to wrap.
///
/// # Returns
///
/// `NSTDStr str` - The new `NSTDStr` instance, excluding the C string's null terminator.
#[inline]
#[cfg_attr(feature = "clib", no_mangle)]
pub extern "C" fn nstd_core_str_from_cstr(cstr: *mut NSTDChar) -> NSTDStr {
    let len = nstd_core_cstr_len(cstr);
    NSTDStr {
        bytes: nstd_core_slice_new(cstr.cast(), 1, len),
    }
}