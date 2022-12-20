//! A handle to an opened file.
use crate::{
    core::{
        result::NSTDResult,
        slice::{NSTDSlice, NSTDSliceMut},
        str::NSTDStr,
    },
    io::NSTDIOError,
    string::NSTDString,
    vec::NSTDVec,
    NSTDUInt, NSTDUInt8,
};
use std::fs::File;
#[cfg(target_family = "unix")]
use std::os::unix::io::AsRawFd;

/// Creates the file upon opening if it does not already exist.
///
/// Either of the `NSTD_FILE_WRITE` or `NSTD_FILE_APPEND` options must also be toggled for the file
/// to be created.
pub const NSTD_FILE_CREATE: NSTDUInt8 = 1;

/// Open a file in read mode.
pub const NSTD_FILE_READ: NSTDUInt8 = 1 << 1;

/// Open a file in write mode.
pub const NSTD_FILE_WRITE: NSTDUInt8 = 1 << 2;

/// Open a file in writing mode without overwriting saved data.
pub const NSTD_FILE_APPEND: NSTDUInt8 = 1 << 3;

/// Open a file in truncate mode, this will set the file's length to 0 upon opening.
pub const NSTD_FILE_TRUNC: NSTDUInt8 = 1 << 4;

/// A handle to an opened file.
pub type NSTDFile = Box<File>;

/// A result type yielding an `NSTDFile` on success.
pub type NSTDFileResult = NSTDResult<NSTDFile, NSTDIOError>;

/// Opens file on the filesystem and returns a handle to it.
///
/// # Parameters:
///
/// - `const NSTDStr *name` - The name of the file to create.
///
/// - `NSTDUInt8 mask` - A bit mask for toggling the file's different open options.
///
/// # Returns
///
/// `NSTDFileResult file` - A handle to the opened file, or the IO error on failure.
///
/// # Panics
///
/// Panics if `name`'s length in bytes exceeds `NSTDInt`'s max value.
///
/// # Safety
///
/// This operation can cause undefined behavior if `name`'s data is invalid.
#[cfg_attr(feature = "clib", no_mangle)]
pub unsafe extern "C" fn nstd_fs_file_open(name: &NSTDStr, mask: NSTDUInt8) -> NSTDFileResult {
    // Attempt to create/open the file in write mode.
    match File::options()
        .create((mask & NSTD_FILE_CREATE) != 0)
        .read((mask & NSTD_FILE_READ) != 0)
        .write((mask & NSTD_FILE_WRITE) != 0)
        .append((mask & NSTD_FILE_APPEND) != 0)
        .truncate((mask & NSTD_FILE_TRUNC) != 0)
        .open(name.as_str())
    {
        Ok(f) => NSTDResult::Ok(Box::new(f)),
        Err(err) => NSTDResult::Err(NSTDIOError::from_err(err.kind())),
    }
}

/// Writes some data to a file & returns how many bytes were written.
///
/// # Parameters:
///
/// - `NSTDFile *file` - A handle to an open file.
///
/// - `const NSTDSlice *bytes` - The data to write to the file.
///
/// - `NSTDUInt *written` - Returns as the number of bytes written to the file.
///
/// # Returns
///
/// `NSTDIOError errc` - The I/O operation error code.
///
/// # Safety
///
/// This function's caller must guarantee validity of `bytes`.
#[inline]
#[cfg_attr(feature = "clib", no_mangle)]
pub unsafe extern "C" fn nstd_fs_file_write(
    file: &mut NSTDFile,
    bytes: &NSTDSlice,
    written: &mut NSTDUInt,
) -> NSTDIOError {
    #[cfg(not(target_family = "unix"))]
    {
        let (err, w) = crate::io::stdio::write(file, bytes);
        *written = w;
        err
    }
    #[cfg(target_family = "unix")]
    {
        let (err, w) = crate::os::unix::io::stdio::write(file.as_raw_fd(), bytes);
        *written = w;
        err.into()
    }
}

/// Writes a whole buffer to a file.
///
/// # Parameters:
///
/// - `NSTDFile *file` - A handle to an open file.
///
/// - `const NSTDSlice *bytes` - The data to write to the file.
///
/// # Returns
///
/// `NSTDIOError errc` - The I/O operation error code.
///
/// # Safety
///
/// This function's caller must guarantee validity of `bytes`.
#[inline]
#[cfg_attr(feature = "clib", no_mangle)]
pub unsafe extern "C" fn nstd_fs_file_write_all(
    file: &mut NSTDFile,
    bytes: &NSTDSlice,
) -> NSTDIOError {
    #[cfg(not(target_family = "unix"))]
    return crate::io::stdio::write_all(file, bytes);
    #[cfg(target_family = "unix")]
    return crate::os::unix::io::stdio::write_all(file.as_raw_fd(), bytes).into();
}

/// Flushes a file stream.
///
/// # Parameters:
///
/// - `NSTDFile *file` - The file stream.
///
/// # Returns
///
/// `NSTDIOError errc` - The I/O operation error code.
#[inline]
#[cfg_attr(feature = "clib", no_mangle)]
pub extern "C" fn nstd_fs_file_flush(file: &mut NSTDFile) -> NSTDIOError {
    crate::io::stdio::flush(file)
}

/// Reads some data from an open file into a buffer.
///
/// # Parameters:
///
/// - `NSTDFile *file` - A handle to the opened file.
///
/// - `NSTDSliceMut *buffer` - The buffer to start filling with data from the file.
///
/// - `NSTDUInt *read` - Returns as the number of bytes read from the file.
///
/// # Returns
///
/// `NSTDIOError errc` - The I/O operation error code.
///
/// # Safety
///
/// `buffer`'s data must be valid for writes.
#[inline]
#[cfg_attr(feature = "clib", no_mangle)]
pub unsafe extern "C" fn nstd_fs_file_read(
    file: &mut NSTDFile,
    buffer: &mut NSTDSliceMut,
    read: &mut NSTDUInt,
) -> NSTDIOError {
    #[cfg(not(target_family = "unix"))]
    {
        let (err, r) = crate::io::stdio::read(file, buffer);
        *read = r;
        err
    }
    #[cfg(target_family = "unix")]
    {
        let (err, r) = crate::os::unix::io::stdio::read(file.as_raw_fd(), buffer);
        *read = r;
        err.into()
    }
}

/// Continuously reads data from `file` into a buffer until EOF is reached.
///
/// # Note
///
/// If extending the buffer fails, an error code of `NSTD_IO_ERROR_OUT_OF_MEMORY` will be returned.
/// This does not mean `read` will return as 0 in this case.
///
/// # Parameters:
///
/// - `NSTDFile *file` - A handle to the file.
///
/// - `NSTDVec *buffer` - The buffer to be extended with data from the file.
///
/// - `NSTDUInt *read` - Returns as the number of bytes read from the file.
///
/// # Returns
///
/// `NSTDIOError errc` - The I/O operation error code.
#[inline]
#[cfg_attr(feature = "clib", no_mangle)]
pub extern "C" fn nstd_fs_file_read_all(
    file: &mut NSTDFile,
    buffer: &mut NSTDVec,
    read: &mut NSTDUInt,
) -> NSTDIOError {
    #[cfg(not(target_family = "unix"))]
    {
        let (err, r) = crate::io::stdio::read_all(file, buffer);
        *read = r;
        err
    }
    #[cfg(target_family = "unix")]
    {
        // SAFETY: `file` owns the file descriptor.
        let (err, r) = unsafe { crate::os::unix::io::stdio::read_all(file.as_raw_fd(), buffer) };
        *read = r;
        err.into()
    }
}

/// Continuously reads UTF-8 data from `file` into a string buffer until EOF is reached.
///
/// # Note
///
/// If extending the buffer fails, an error code of `NSTD_IO_ERROR_OUT_OF_MEMORY` will be returned.
/// This does not mean `read` will return as 0 in this case.
///
/// # Parameters:
///
/// - `NSTDFile *file` - A handle to the file.
///
/// - `NSTDString *buffer` - The buffer to be extended with data from the file.
///
/// - `NSTDUInt *read` - Returns as the number of bytes read from the file.
///
/// # Returns
///
/// `NSTDIOError errc` - The I/O operation error code.
///
/// # Panics
///
/// This function will panic if `buffer`'s length in bytes exceeds `NSTDInt`'s max value.
#[inline]
#[cfg_attr(feature = "clib", no_mangle)]
pub extern "C" fn nstd_fs_file_read_to_string(
    file: &mut NSTDFile,
    buffer: &mut NSTDString,
    read: &mut NSTDUInt,
) -> NSTDIOError {
    #[cfg(not(target_family = "unix"))]
    {
        let (err, r) = crate::io::stdio::read_to_string(file, buffer);
        *read = r;
        err
    }
    #[cfg(target_family = "unix")]
    {
        // SAFETY: `file` owns the file descriptor.
        unsafe {
            let (err, r) = crate::os::unix::io::stdio::read_to_string(file.as_raw_fd(), buffer);
            *read = r;
            err.into()
        }
    }
}

/// Reads enough data from `file` to fill the entirety of `buffer`.
///
/// # Note
///
/// This function will return an error code of `NSTD_IO_ERROR_INVALID_INPUT` if the buffer's
/// element size is not 1.
///
/// # Parameters:
///
/// - `NSTDFile *file` - A handle to the file.
///
/// - `NSTDSliceMut *buffer` - The buffer to fill with data from the file.
///
/// # Returns
///
/// `NSTDIOError errc` - The I/O operation error code.
///
/// # Safety
///
/// `buffer` must be valid for writes.
#[inline]
#[cfg_attr(feature = "clib", no_mangle)]
pub unsafe extern "C" fn nstd_fs_file_read_exact(
    file: &mut NSTDFile,
    buffer: &mut NSTDSliceMut,
) -> NSTDIOError {
    #[cfg(not(target_family = "unix"))]
    return crate::io::stdio::read_exact(file, buffer);
    #[cfg(target_family = "unix")]
    return crate::os::unix::io::stdio::read_exact(file.as_raw_fd(), buffer).into();
}

/// Closes a file handle.
///
/// # Parameters:
///
/// - `NSTDFile file` - The file handle to close.
#[inline]
#[cfg_attr(feature = "clib", no_mangle)]
#[allow(unused_variables)]
pub extern "C" fn nstd_fs_file_close(file: NSTDFile) {}
