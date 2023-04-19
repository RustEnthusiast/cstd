//! Provides shared library access for Unix like systems.
use crate::{core::optional::NSTDOptional, NSTDAny, NSTDAnyMut, NSTDChar};
use nstdapi::nstdapi;

/// Represents an owned handle to a dynamically loaded library.
#[nstdapi]
pub struct NSTDUnixSharedLib {
    /// A raw handle to the shared library.
    handle: NSTDAnyMut,
}
impl Drop for NSTDUnixSharedLib {
    /// [NSTDUnixSharedLib]'s destructor.
    #[inline]
    fn drop(&mut self) {
        // SAFETY: `self` is valid.
        unsafe { nstd_os_unix_shared_lib_free(core::ptr::read(self)) };
    }
}
// SAFETY: `NSTDUnixSharedLib` owns a handle to the dynamically loaded library.
unsafe impl Send for NSTDUnixSharedLib {}
// SAFETY: `NSTDUnixSharedLib` does not undergo interior mutability.
unsafe impl Sync for NSTDUnixSharedLib {}

/// Represents an optional `NSTDUnixSharedLib`.
pub type NSTDUnixOptionalSharedLib = NSTDOptional<NSTDUnixSharedLib>;

extern "C" {
    /// Loads a dynamically loaded shared library.
    ///
    /// # Parameters:
    ///
    /// - `const NSTDChar *path` - A path to the shared library to load.
    ///
    /// # Returns
    ///
    /// `NSTDUnixOptionalSharedLib lib` - A handle to the loaded library.
    ///
    /// # Safety
    ///
    /// See <https://man7.org/linux/man-pages/man3/dlopen.3.html>.
    pub fn nstd_os_unix_shared_lib_load(path: *const NSTDChar) -> NSTDUnixOptionalSharedLib;

    /// Returns a raw handle to a dynamically loaded library.
    ///
    /// # Parameters:
    ///
    /// - `const NSTDUnixSharedLib *lib` - The shared library.
    ///
    /// # Returns
    ///
    /// `NSTDAnyMut handle` - A raw handle to the dynamically loaded library.
    pub fn nstd_os_unix_shared_lib_handle(lib: &NSTDUnixSharedLib) -> NSTDAnyMut;

    /// Returns an immutable opaque pointer to a symbol in a loaded library.
    ///
    /// # Parameters:
    ///
    /// - `const NSTDUnixSharedLib *lib` - The shared library.
    ///
    /// - `const NSTDChar *symbol` - The symbol to retrieve a pointer to.
    ///
    /// # Returns
    ///
    /// `NSTDAny ptr` - A pointer to the loaded symbol, null on error.
    ///
    /// # Safety
    ///
    /// See <https://man7.org/linux/man-pages/man3/dlsym.3.html>.
    pub fn nstd_os_unix_shared_lib_get(lib: &NSTDUnixSharedLib, symbol: *const NSTDChar)
        -> NSTDAny;

    /// Returns a mutable opaque pointer to a symbol in a loaded library.
    ///
    /// # Parameters:
    ///
    /// - `NSTDUnixSharedLib *lib` - The shared library.
    ///
    /// - `const NSTDChar *symbol` - The symbol to retrieve a pointer to.
    ///
    /// # Returns
    ///
    /// `NSTDAnyMut ptr` - A pointer to the loaded symbol, null on error.
    ///
    /// # Safety
    ///
    /// See <https://man7.org/linux/man-pages/man3/dlsym.3.html>.
    pub fn nstd_os_unix_shared_lib_get_mut(
        lib: &mut NSTDUnixSharedLib,
        symbol: *const NSTDChar,
    ) -> NSTDAnyMut;

    /// Closes and frees a loaded shared library.
    ///
    /// # Parameters:
    ///
    /// - `NSTDUnixSharedLib lib` - A handle to the loaded library to unload.
    ///
    /// # Safety
    ///
    /// See <https://man7.org/linux/man-pages/man3/dlclose.3p.html>.
    pub fn nstd_os_unix_shared_lib_free(lib: NSTDUnixSharedLib);
}
