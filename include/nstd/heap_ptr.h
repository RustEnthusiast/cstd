#ifndef NSTD_HEAP_PTR_H
#define NSTD_HEAP_PTR_H
#include "nstd.h"

/// A pointer type for single value heap allocation.
typedef struct {
    /// A raw pointer to the value on the heap.
    NSTDAnyMut ptr;
    /// The size of the object in bytes.
    NSTDUInt size;
} NSTDHeapPtr;

/// Creates a new initialized heap allocated object.
///
/// # Parameters:
///
/// - `NSTDUInt element_size` - The size (in bytes) of the heap object.
///
/// - `NSTDAny init` - A pointer to the object to initialize the heap object with.
///
/// # Returns
///
/// `NSTDHeapPtr hptr` - The new heap allocated object.
///
/// # Panics
///
/// This function will panic if either `element_size` is zero, or allocation fails.
///
/// # Safety
///
/// `init` must be a pointer to a value that is valid for reads of `element_size` bytes.
///
/// # Example
///
/// ```
/// use core::ptr::addr_of;
/// use nstd_sys::heap_ptr::nstd_heap_ptr_new;
///
/// const SIZE: usize = core::mem::size_of::<char>();
///
/// let v = '🦀';
/// let hptr = unsafe { nstd_heap_ptr_new(SIZE, addr_of!(v).cast()) };
/// ```
NSTDAPI NSTDHeapPtr nstd_heap_ptr_new(NSTDUInt element_size, NSTDAny init);

/// Creates a new zero-initialized heap allocated object.
///
/// # Parameters:
///
/// - `NSTDUInt element_size` - The size (in bytes) of the heap object.
///
/// # Returns
///
/// `NSTDHeapPtr hptr` - The new heap allocated object.
///
/// # Panics
///
/// This function will panic if either `element_size` is zero, or allocation fails.
///
/// # Example
///
/// ```
/// use nstd_sys::heap_ptr::{nstd_heap_ptr_get, nstd_heap_ptr_new_zeroed};
///
/// const SIZE: usize = core::mem::size_of::<u64>();
///
/// unsafe {
///     let hptr = nstd_heap_ptr_new_zeroed(SIZE);
///     assert!(*nstd_heap_ptr_get(&hptr).cast::<u64>() == 0);
/// }
/// ```
NSTDAPI NSTDHeapPtr nstd_heap_ptr_new_zeroed(NSTDUInt element_size);

/// Creates a clone of a heap allocated object.
///
/// # Parameters:
///
/// - `const NSTDHeapPtr *hptr` - The heap pointer.
///
/// # Returns
///
/// `NSTDHeapPtr cloned` - A new clone of the original heap object.
///
/// # Panics
///
/// This function will panic if allocation fails.
NSTDAPI NSTDHeapPtr nstd_heap_ptr_clone(const NSTDHeapPtr *hptr);

/// Returns the size of the heap allocated object.
///
/// # Parameters:
///
/// - `const NSTDHeapPtr *hptr` - The heap pointer.
///
/// # Returns
///
/// `NSTDUInt size` - The size of the heap allocated object.
///
/// # Example
///
/// ```
/// use nstd_sys::heap_ptr::{nstd_heap_ptr_new_zeroed, nstd_heap_ptr_size};
///
/// const SIZE: usize = core::mem::size_of::<i32>();
///
/// let hptr = unsafe { nstd_heap_ptr_new_zeroed(SIZE) };
/// assert!(nstd_heap_ptr_size(&hptr) == SIZE);
/// ```
NSTDAPI NSTDUInt nstd_heap_ptr_size(const NSTDHeapPtr *hptr);

/// Returns an immutable raw pointer to the object on the heap.
///
/// # Parameters:
///
/// - `const NSTDHeapPtr *hptr` - The heap pointer.
///
/// # Returns
///
/// `NSTDAny ptr` - A raw pointer to the object on the heap.
///
/// # Example
///
/// ```
/// use core::ptr::addr_of;
/// use nstd_sys::heap_ptr::{nstd_heap_ptr_get, nstd_heap_ptr_new};
///
/// const SIZE: usize = core::mem::size_of::<i128>();
///
/// unsafe {
///     let v = -46923i128;
///     let hptr = nstd_heap_ptr_new(SIZE, addr_of!(v).cast());
///     assert!(*nstd_heap_ptr_get(&hptr).cast::<i128>() == v);
/// }
/// ```
NSTDAPI NSTDAny nstd_heap_ptr_get(const NSTDHeapPtr *hptr);

/// Returns a raw pointer to the object on the heap.
///
/// # Parameters:
///
/// - `NSTDHeapPtr *hptr` - The heap pointer.
///
/// # Returns
///
/// `NSTDAnyMut ptr` - A raw pointer to the object on the heap.
///
/// # Example
///
/// ```
/// use core::ptr::addr_of;
/// use nstd_sys::heap_ptr::{nstd_heap_ptr_get_mut, nstd_heap_ptr_new};
///
/// const SIZE: usize = core::mem::size_of::<i128>();
///
/// unsafe {
///     let v = 32964i128;
///     let mut hptr = nstd_heap_ptr_new(SIZE, addr_of!(v).cast());
///     let hv = nstd_heap_ptr_get_mut(&mut hptr).cast::<i128>();
///     assert!(*hv == v);
///     *hv = -46923;
///     assert!(*hv != v);
/// }
/// ```
NSTDAPI NSTDAnyMut nstd_heap_ptr_get_mut(NSTDHeapPtr *hptr);

/// Frees an instance of `NSTDHeapPtr`.
///
/// # Parameters:
///
/// - `NSTDHeapPtr hptr` - A pointer to the heap object.
///
/// # Panics
///
/// This operation may panic if getting a handle to the heap fails.
NSTDAPI void nstd_heap_ptr_free(NSTDHeapPtr hptr);

#endif
