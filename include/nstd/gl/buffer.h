#ifndef NSTD_GL_BUFFER_H
#define NSTD_GL_BUFFER_H
#include "../core/slice.h"
#include "../nstd.h"
#include "gl.h"
#include "render_pass.h"

/// Create a vertex buffer.
#define NSTD_GL_BUFFER_TYPE_VERTEX 1
/// Create a index buffer.
#define NSTD_GL_BUFFER_TYPE_INDEX (1 << 1)
/// Create a uniform buffer.
#define NSTD_GL_BUFFER_TYPE_UNIFORM (1 << 2)

/// GPU memory buffers.
typedef NSTDAnyMut NSTDGLBuffer;

/// Creates and initializes a new GPU buffer with `data`.
///
/// # Parameters:
///
/// - `const NSTDGLRenderer *renderer` - The renderer to create the buffer with.
///
/// - `const NSTDSlice *data` - The data to send to the GPU.
///
/// - `NSTDUInt8 buffer_type` - A bit mask describing what type of buffer to create.
///
/// # Panics
///
/// This operation will panic if `data`'s stride is not 1.
///
/// # Safety
///
/// `data` must be valid for reads.
NSTDAPI NSTDGLBuffer
nstd_gl_buffer_new(const NSTDGLRenderer *renderer, const NSTDSlice *data, NSTDUInt8 buffer_type);

/// Makes `buffer` an active vertex buffer for `render_pass` at `index`.
///
/// # Parameters:
///
/// - `const NSTDGLBuffer *buffer` - The buffer to bind.
///
/// - `NSTDUInt32 index` - The index (or slot) to bind the buffer to.
///
/// - `NSTDGLRenderPass *render_pass` - The render pass in use.
NSTDAPI void nstd_gl_buffer_bind_vertex(
    const NSTDGLBuffer *buffer, NSTDUInt32 index, NSTDGLRenderPass *render_pass
);

/// Makes `buffer` an active index buffer for `render_pass`.
///
/// # Parameters:
///
/// - `const NSTDGLBuffer *buffer` - The buffer to bind.
///
/// - `NSTDGLRenderPass *render_pass` - The render pass in use.
NSTDAPI void nstd_gl_buffer_bind_index(const NSTDGLBuffer *buffer, NSTDGLRenderPass *render_pass);

/// Frees a GPU buffer.
///
/// # Parameters:
///
/// - `NSTDGLBuffer buffer` - The buffer to free.
NSTDAPI void nstd_gl_buffer_free(NSTDGLBuffer buffer);

#endif