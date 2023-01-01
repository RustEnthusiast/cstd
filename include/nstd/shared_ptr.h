#ifndef NSTD_SHARED_PTR_H
#define NSTD_SHARED_PTR_H
#include "core/optional.h"
#include "nstd.h"

/// A reference counting smart pointer.
typedef struct {
    /// A raw pointer to private data about the shared object.
    NSTDAnyMut ptr;
    /// The size of the shared pointer's memory buffer.
    NSTDUInt size;
} NSTDSharedPtr;

/// Represents an optional value of type `NSTDSharedPtr`.
NSTDOptional(NSTDSharedPtr) NSTDOptionalSharedPtr;

/// Creates a new initialized instance of a shared pointer.
///
/// # Parameters:
///
/// - `NSTDUInt element_size` - The size of the shared object.
///
/// - `NSTDAny init` - A pointer to the object to initialize the shared pointer with.
///
/// # Returns
///
/// `NSTDSharedPtr shared_ptr` - The new shared pointer.
///
/// # Panics
///
/// This operation will panic if either `element_size` is greater than `NSTDInt`'s max value or
/// allocating fails.
///
/// # Safety
///
/// `init` must be a pointer to a value that is valid for reads of `element_size` bytes.
NSTDAPI NSTDSharedPtr nstd_shared_ptr_new(NSTDUInt element_size, NSTDAny init);

/// Creates a new zero-initialized instance of a shared pointer.
///
/// # Parameters:
///
/// - `NSTDUInt element_size` - The size of the shared object.
///
/// # Returns
///
/// `NSTDSharedPtr shared_ptr` - The yet to be shared pointer.
///
/// # Panics
///
/// This operation will panic if either `element_size` is greater than `NSTDInt`'s max value or
/// allocating fails.
///
/// # Safety
///
/// The data to be stored in the shared pointer must be safely representable by an all-zero byte
/// pattern.
NSTDAPI NSTDSharedPtr nstd_shared_ptr_new_zeroed(NSTDUInt element_size);

/// Shares `shared_ptr`.
///
/// # Parameters:
///
/// - `const NSTDSharedPtr *shared_ptr` - The shared object to share.
///
/// # Returns
///
/// `NSTDSharedPtr shared` - A new pointer pointing to the shared data.
NSTDAPI NSTDSharedPtr nstd_shared_ptr_share(const NSTDSharedPtr *shared_ptr);

/// Returns the number of pointers that share `shared_ptr`'s data.
///
/// # Parameters:
///
/// - `const NSTDSharedPtr *shared_ptr` - An instance of a shared pointer.
///
/// # Returns
///
/// `NSTDUInt owners` - The number of pointers that share `shared_ptr`'s data.
NSTDAPI NSTDUInt nstd_shared_ptr_owners(const NSTDSharedPtr *shared_ptr);

/// Returns the size of the shared object.
///
/// # Parameters:
///
/// - `const NSTDSharedPtr *shared_ptr` - The shared pointer.
///
/// # Returns
///
/// `NSTDUInt size` - The size of the shared object.
NSTDAPI NSTDUInt nstd_shared_ptr_size(const NSTDSharedPtr *shared_ptr);

/// Returns an immutable raw pointer to the shared object.
///
/// # Parameters:
///
/// - `const NSTDSharedPtr *shared_ptr` - The shared pointer.
///
/// # Returns
///
/// `NSTDAny ptr` - A raw pointer to the shared object.
NSTDAPI NSTDAny nstd_shared_ptr_get(const NSTDSharedPtr *shared_ptr);

/// Frees an instance of `NSTDSharedPtr`.
///
/// # Parameters:
///
/// - `NSTDSharedPtr shared_ptr` - The shared object to free.
///
/// # Panics
///
/// Panics if there are no more shared pointers referencing the shared data and freeing the heap
/// memory fails.
NSTDAPI void nstd_shared_ptr_free(NSTDSharedPtr shared_ptr);

#endif
