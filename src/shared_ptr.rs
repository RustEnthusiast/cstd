//! A reference counting smart pointer.
use crate::{
    alloc::{nstd_alloc_allocate_zeroed, nstd_alloc_deallocate},
    core::ptr::{nstd_core_ptr_new, NSTDPtr},
    NSTDAnyConst, NSTDUSize,
};

/// The size (in bytes) of [usize].
const USIZE_SIZE: usize = core::mem::size_of::<usize>();

/// A reference counting smart pointer.
#[repr(C)]
#[derive(Debug, Hash, PartialEq, Eq)]
pub struct NSTDSharedPtr {
    /// A pointer to private data about the shared object.
    pub ptr: NSTDPtr,
}
impl NSTDSharedPtr {
    /// Returns the number of pointers sharing the object.
    #[inline]
    fn ptrs(&self) -> *mut usize {
        unsafe { self.ptr.raw.add(nstd_shared_ptr_size(self)).cast() }
    }
}

/// Creates a new zero-initialized instance of a shared pointer.
///
/// # Parameters:
///
/// - `NSTDUSize element_size` - The size of the shared object.
///
/// # Returns
///
/// `NSTDSharedPtr shared_ptr` - The yet to be shared pointer.
///
/// # Panics
///
/// This operation will panic if allocating fails.
#[cfg_attr(feature = "clib", no_mangle)]
pub extern "C" fn nstd_shared_ptr_new_zeroed(element_size: NSTDUSize) -> NSTDSharedPtr {
    unsafe {
        // Allocate a region of memory for the object and the pointer count.
        let buffer_size = element_size + USIZE_SIZE;
        let raw = nstd_alloc_allocate_zeroed(buffer_size);
        assert!(!raw.is_null());
        // Set the pointer count to one.
        let ptrs = raw.add(element_size).cast::<usize>();
        *ptrs = 1;
        // Construct the pointer with `element_size`, this does not include the size of the pointer
        // count (a `usize`).
        NSTDSharedPtr {
            ptr: nstd_core_ptr_new(raw, buffer_size),
        }
    }
}

/// Shares `shared_ptr`.
///
/// # Parameters:
///
/// - `const NSTDSharedPtr *shared_ptr` - The shared object to share.
///
/// # Returns
///
/// `NSTDSharedPtr shared` - A new pointer pointing to the shared data.
#[inline]
#[cfg_attr(feature = "clib", no_mangle)]
pub extern "C" fn nstd_shared_ptr_share(shared_ptr: &NSTDSharedPtr) -> NSTDSharedPtr {
    unsafe {
        // Update the pointer count.
        let ptrs = shared_ptr.ptrs();
        *ptrs += 1;
        // Construct the new shared pointer instance.
        NSTDSharedPtr {
            ptr: nstd_core_ptr_new(shared_ptr.ptr.raw, shared_ptr.ptr.size),
        }
    }
}

/// Returns the size of the shared object.
///
/// # Parameters:
///
/// - `const NSTDSharedPtr *shared_ptr` - The shared pointer.
///
/// # Returns
///
/// `NSTDUSize size` - The size of the shared object.
#[inline]
#[cfg_attr(feature = "clib", no_mangle)]
pub extern "C" fn nstd_shared_ptr_size(shared_ptr: &NSTDSharedPtr) -> NSTDUSize {
    shared_ptr.ptr.size - USIZE_SIZE
}

/// Returns an immutable raw pointer to the shared object.
///
/// # Parameters:
///
/// - `const NSTDSharedPtr *shared_ptr` - The shared pointer.
///
/// # Returns
///
/// `NSTDAnyConst ptr` - A raw pointer to the shared object.
///
/// # Safety
///
/// The shared data must remain valid while the returned pointer is in use.
#[inline]
#[cfg_attr(feature = "clib", no_mangle)]
pub unsafe extern "C" fn nstd_shared_ptr_get_const(shared_ptr: &NSTDSharedPtr) -> NSTDAnyConst {
    shared_ptr.ptr.raw
}

/// Frees an instance of `NSTDSharedPtr`.
///
/// # Parameters:
///
/// - `NSTDSharedPtr *shared_ptr` - The shared object to free.
#[inline]
#[cfg_attr(feature = "clib", no_mangle)]
pub extern "C" fn nstd_shared_ptr_free(shared_ptr: &mut NSTDSharedPtr) {
    unsafe {
        // Update the pointer count.
        let ptrs = shared_ptr.ptrs();
        *ptrs -= 1;
        // If the pointer count is zero, free the data.
        if *ptrs == 0 {
            nstd_alloc_deallocate(&mut shared_ptr.ptr.raw, shared_ptr.ptr.size);
        }
    }
}
