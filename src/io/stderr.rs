//! A handle to the standard error stream.
use crate::{
    core::slice::NSTDSlice,
    io::{NSTDIOError, NSTDIOResult},
};
use nstdapi::nstdapi;
use std::io::{Stderr, StderrLock};
#[cfg(unix)]
use std::os::unix::io::AsRawFd;

/// A handle to the standard error stream.
#[nstdapi]
pub struct NSTDStderr {
    /// Rust's [Stderr].
    err: Box<Stderr>,
}

/// Constructs a new handle to the standard error stream.
///
/// # Returns
///
/// `NSTDStderr handle` - A handle to the standard error stream.
#[inline]
#[nstdapi]
pub fn nstd_io_stderr() -> NSTDStderr {
    NSTDStderr {
        err: Box::new(std::io::stderr()),
    }
}

/// Writes some data to the standard error stream, returning how many bytes were written.
///
/// # Note
///
/// This function will return an error code of `NSTD_IO_ERROR_INVALID_INPUT` if the slice's element
/// size is not 1.
///
/// # Parameters:
///
/// - `NSTDStderr *handle` - A handle to stderr.
///
/// - `const NSTDSlice *bytes` - The data to be written to stderr.
///
/// # Returns
///
/// `NSTDIOResult written` - The number of bytes written to `handle` on success, or the I/O
/// operation error code on failure.
///
/// # Safety
///
/// This function can cause undefined behavior if `bytes`'s data is invalid.
#[inline]
#[nstdapi]
pub unsafe fn nstd_io_stderr_write(handle: &mut NSTDStderr, bytes: &NSTDSlice) -> NSTDIOResult {
    #[cfg(not(unix))]
    return crate::io::stdio::write(&mut handle.err, bytes);
    #[cfg(unix)]
    return crate::os::unix::io::stdio::write(handle.err.lock().as_raw_fd(), bytes).into();
}

/// Writes an entire buffer to the standard error stream.
///
/// # Note
///
/// This function will return an error code of `NSTD_IO_ERROR_INVALID_INPUT` if the slice's element
/// size is not 1.
///
/// # Parameters:
///
/// - `NSTDStderr *handle` - A handle to stderr.
///
/// - `const NSTDSlice *bytes` - The data to be written to stderr.
///
/// # Returns
///
/// `NSTDIOError errc` - The I/O operation error code.
///
/// # Safety
///
/// This function can cause undefined behavior if `bytes`'s data is invalid.
#[inline]
#[nstdapi]
pub unsafe fn nstd_io_stderr_write_all(handle: &mut NSTDStderr, bytes: &NSTDSlice) -> NSTDIOError {
    #[cfg(not(unix))]
    return crate::io::stdio::write_all(&mut handle.err, bytes);
    #[cfg(unix)]
    return crate::os::unix::io::stdio::write_all(handle.err.lock().as_raw_fd(), bytes).into();
}

/// Flushes the standard error stream.
///
/// # Parameters:
///
/// - `NSTDStderr *handle` - A handle to stderr.
///
/// # Returns
///
/// `NSTDIOError errc` - The I/O operation error code.
#[inline]
#[nstdapi]
pub fn nstd_io_stderr_flush(handle: &mut NSTDStderr) -> NSTDIOError {
    crate::io::stdio::flush(&mut handle.err)
}

/// Frees an instance of `NSTDStderr`.
///
/// # Parameters:
///
/// - `NSTDStderr handle` - A handle to the standard error stream.
#[inline]
#[nstdapi]
#[allow(unused_variables)]
pub fn nstd_io_stderr_free(handle: NSTDStderr) {}

/// A locked handle to the standard error stream.
#[nstdapi]
pub struct NSTDStderrLock {
    /// Rust's [StderrLock].
    err: Box<StderrLock<'static>>,
}

/// Constructs a new locked handle to the standard error stream.
///
/// # Returns
///
/// `NSTDStderrLock handle` - A locked handle to the standard error stream.
#[inline]
#[nstdapi]
pub fn nstd_io_stderr_lock() -> NSTDStderrLock {
    NSTDStderrLock {
        err: Box::new(std::io::stderr().lock()),
    }
}

/// Writes some data to the standard error stream, returning how many bytes were written.
///
/// # Note
///
/// This function will return an error code of `NSTD_IO_ERROR_INVALID_INPUT` if the slice's element
/// size is not 1.
///
/// # Parameters:
///
/// - `NSTDStderrLock *handle` - A locked handle to stderr.
///
/// - `const NSTDSlice *bytes` - The data to be written to stderr.
///
/// # Returns
///
/// `NSTDIOResult written` - The number of bytes written to `handle` on success, or the I/O
/// operation error code on failure.
///
/// # Safety
///
/// This function can cause undefined behavior if `bytes`'s data is invalid.
#[inline]
#[nstdapi]
pub unsafe fn nstd_io_stderr_lock_write(
    handle: &mut NSTDStderrLock,
    bytes: &NSTDSlice,
) -> NSTDIOResult {
    #[cfg(not(unix))]
    return crate::io::stdio::write(&mut handle.err, bytes);
    #[cfg(unix)]
    return crate::os::unix::io::stdio::write(handle.err.as_raw_fd(), bytes).into();
}

/// Writes an entire buffer to the standard error stream.
///
/// # Note
///
/// This function will return an error code of `NSTD_IO_ERROR_INVALID_INPUT` if the slice's element
/// size is not 1.
///
/// # Parameters:
///
/// - `NSTDStderrLock *handle` - A locked handle to stderr.
///
/// - `const NSTDSlice *bytes` - The data to be written to stderr.
///
/// # Returns
///
/// `NSTDIOError errc` - The I/O operation error code.
///
/// # Safety
///
/// This function can cause undefined behavior if `bytes`'s data is invalid.
#[inline]
#[nstdapi]
pub unsafe fn nstd_io_stderr_lock_write_all(
    handle: &mut NSTDStderrLock,
    bytes: &NSTDSlice,
) -> NSTDIOError {
    #[cfg(not(unix))]
    return crate::io::stdio::write_all(&mut handle.err, bytes);
    #[cfg(unix)]
    return crate::os::unix::io::stdio::write_all(handle.err.as_raw_fd(), bytes).into();
}

/// Flushes the standard error stream.
///
/// # Parameters:
///
/// - `NSTDStderrLock *handle` - A locked handle to stderr.
///
/// # Returns
///
/// `NSTDIOError errc` - The I/O operation error code.
#[inline]
#[nstdapi]
pub fn nstd_io_stderr_lock_flush(handle: &mut NSTDStderrLock) -> NSTDIOError {
    crate::io::stdio::flush(&mut handle.err)
}

/// Frees and unlocks an instance of `NSTDStderrLock`.
///
/// # Parameters:
///
/// - `NSTDStderrLock handle` - A locked handle to the standard error stream.
#[inline]
#[nstdapi]
#[allow(unused_variables)]
pub fn nstd_io_stderr_unlock(handle: NSTDStderrLock) {}
