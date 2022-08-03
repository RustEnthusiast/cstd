//! Contains common I/O operations for [Read] & [Write] with `nstd` types.
use crate::{
    core::slice::{nstd_core_slice_const_new, NSTDSliceConst, NSTDSliceMut},
    io::NSTDIOError,
    vec::{nstd_vec_extend, nstd_vec_stride, NSTDVec},
    NSTDUSize,
};
use std::io::{Read, Write};

/// Writes some `nstd` bytes to a [Write] stream.
///
/// `written` will return as the number of bytes written to the stream.
///
/// # Safety
///
/// This function can cause undefined behavior if `bytes`'s data is invalid.
pub(crate) unsafe fn write<W: Write>(
    stream: &mut W,
    bytes: &NSTDSliceConst,
    written: &mut NSTDUSize,
) -> NSTDIOError {
    // Make sure the slice's element size is 1.
    if bytes.ptr.size != 1 {
        *written = 0;
        return NSTDIOError::NSTD_IO_ERROR_INVALID_INPUT;
    }
    // Attempt to write the bytes to stdout.
    match stream.write(bytes.as_slice()) {
        Ok(w) => {
            *written = w;
            NSTDIOError::NSTD_IO_ERROR_NONE
        }
        Err(err) => {
            *written = 0;
            NSTDIOError::from_err(err.kind())
        }
    }
}

/// Writes an `nstd` byte slice to a [Write] stream.
///
/// # Safety
///
/// This function can cause undefined behavior if `bytes`'s data is invalid.
pub(crate) unsafe fn write_all<W: Write>(stream: &mut W, bytes: &NSTDSliceConst) -> NSTDIOError {
    // Make sure the slice's element size is 1.
    if bytes.ptr.size != 1 {
        return NSTDIOError::NSTD_IO_ERROR_INVALID_INPUT;
    }
    // Attempt to write the bytes to stdout.
    if let Err(err) = stream.write_all(bytes.as_slice()) {
        return NSTDIOError::from_err(err.kind());
    }
    NSTDIOError::NSTD_IO_ERROR_NONE
}

/// Flushes a [Write] stream.
#[inline]
pub(crate) fn flush<W: Write>(stream: &mut W) -> NSTDIOError {
    if let Err(err) = stream.flush() {
        return NSTDIOError::from_err(err.kind());
    }
    NSTDIOError::NSTD_IO_ERROR_NONE
}

/// Reads some data from a [Read] stream into an `nstd` byte slice.
///
/// `read` will return as the number of bytes read from the stream.
///
/// # Safety
///
/// `buffer`'s data must be valid for writes.
pub(crate) unsafe fn read<R: Read>(
    stream: &mut R,
    buffer: &mut NSTDSliceMut,
    read: &mut NSTDUSize,
) -> NSTDIOError {
    // Make sure the buffer's element size is 1.
    if buffer.ptr.size != 1 {
        *read = 0;
        return NSTDIOError::NSTD_IO_ERROR_INVALID_INPUT;
    }
    // Attempt to read bytes into the buffer.
    match stream.read(buffer.as_slice_mut()) {
        Ok(r) => {
            *read = r;
            NSTDIOError::NSTD_IO_ERROR_NONE
        }
        Err(err) => {
            *read = 0;
            NSTDIOError::from_err(err.kind())
        }
    }
}

/// Extends an [NSTDVec] with data from a [Read] stream until EOF is reached.
///
/// `read` will return as the number of bytes read from the stream.
pub(crate) fn read_all<R: Read>(
    stream: &mut R,
    buffer: &mut NSTDVec,
    read: &mut NSTDUSize,
) -> NSTDIOError {
    // Make sure the buffer's element size is 1.
    if nstd_vec_stride(buffer) != 1 {
        *read = 0;
        return NSTDIOError::NSTD_IO_ERROR_INVALID_INPUT;
    }
    // Attempt to read data into `buffer`.
    let mut buf = Vec::new();
    match stream.read_to_end(&mut buf) {
        Ok(r) => {
            let bytes = nstd_core_slice_const_new(buf.as_ptr().cast(), 1, buf.len());
            // SAFETY: `bytes` refers to `buf`'s data, which is still valid here.
            unsafe { nstd_vec_extend(buffer, &bytes) };
            *read = r;
            NSTDIOError::NSTD_IO_ERROR_NONE
        }
        Err(err) => {
            *read = 0;
            NSTDIOError::from_err(err.kind())
        }
    }
}
