#ifndef NSTD_WINDOW_H
#define NSTD_WINDOW_H
#include "app/events.h"
#include "core/def.h"
#include "core/optional.h"
#include "core/str.h"
#include "image.h"
#include "nstd.h"

/// An `nstd` application window.
typedef struct {
    /// The inner window.
    NSTDAnyMut window;
} NSTDWindow;

/// Represents an optional value of type `NSTDWindow`.
NSTDOptional(NSTDWindow) NSTDOptionalWindow;

/// Describes the position of a window.
typedef struct {
    /// The position of the window from the left of the screen.
    NSTDInt32 x;
    /// The position of the window from the top of the screen.
    NSTDInt32 y;
} NSTDWindowPosition;

/// Represents an optional value of type `NSTDWindowPosition`.
NSTDOptional(NSTDWindowPosition) NSTDOptionalWindowPosition;

/// Describes the size of a window.
typedef struct {
    /// The width of the window.
    NSTDUInt32 width;
    /// The height of the window.
    NSTDUInt32 height;
} NSTDWindowSize;

/// Represents an optional value of type `NSTDWindowSize`.
NSTDOptional(NSTDWindowSize) NSTDOptionalWindowSize;

/// Describes the behavior of cursor grabbing.
typedef enum {
    /// The cursor should not be locked or confined.
    NSTD_CURSOR_GRAB_MODE_NONE,
    /// The cursor will be confined to the window area.
    NSTD_CURSOR_GRAB_MODE_CONFINED,
    /// The cursor will be locked to a certain position inside the window area.
    NSTD_CURSOR_GRAB_MODE_LOCKED
} NSTDCursorGrabMode;

/// Creates a new window attached to `app`'s event loop.
///
/// # Parameters:
///
/// - `NSTDAppHandle app` - A handle to an `nstd` application.
///
/// # Returns
///
/// `NSTDOptionalWindow window` - A handle to the newly created window, or an uninitialized "none"
/// variant on error.
NSTDAPI NSTDOptionalWindow nstd_window_new(NSTDAppHandle app);

/// Returns a window's unique identifier.
///
/// # Parameters:
///
/// - `const NSTDWindow *window` - The window.
///
/// # Returns
///
/// `NSTDWindowID window_id` - The window's unique identifier.
NSTDAPI NSTDWindowID nstd_window_id(const NSTDWindow *window);

/// Sets the title of a window.
///
/// # Parameters:
///
/// - `const NSTDWindow *window` - The window.
///
/// - `const NSTDStr *title` - The new title of the window.
///
/// # Safety
///
/// This function can cause undefined behavior if `title`'s data is invalid.
NSTDAPI void nstd_window_set_title(const NSTDWindow *window, const NSTDStr *title);

/// Sets a window's icon to an RGBA image.
///
/// # Parameters:
///
/// - `const NSTDWindow *window` - The window.
///
/// - `const NSTDImage *icon` - The image to set as the window icon.
NSTDAPI void nstd_window_set_icon(const NSTDWindow *window, const NSTDImage *icon);

/// Sets the position of a window.
///
/// # Parameters:
///
/// - `const NSTDWindow *window` - The window.
///
/// - `NSTDWindowPosition pos` - The position of the window.
NSTDAPI void nstd_window_set_outer_position(const NSTDWindow *window, NSTDWindowPosition pos);

/// Gets the position of a window.
///
/// Returns an uninitialized "none" variant on unsupported platforms.
///
/// # Parameters:
///
/// - `const NSTDWindow *window` - The window.
///
/// # Returns
///
/// `NSTDOptionalWindowPosition pos` - The position of the window.
NSTDAPI NSTDOptionalWindowPosition nstd_window_get_outer_position(const NSTDWindow *window);

/// Gets the position of a window's client area on the display.
///
/// Returns an uninitialized "none" variant on unsupported platforms.
///
/// # Parameters:
///
/// - `const NSTDWindow *window` - The window.
///
/// # Returns
///
/// `NSTDOptionalWindowPosition pos` - The position of the window's client area.
NSTDAPI NSTDOptionalWindowPosition nstd_window_get_inner_position(const NSTDWindow *window);

/// Sets the size of a window's client area.
///
/// # Parameters:
///
/// - `const NSTDWindow *window` - The window.
///
/// - `NSTDWindowSize size` - The new size of the window.
NSTDAPI void nstd_window_set_inner_size(const NSTDWindow *window, NSTDWindowSize size);

/// Gets the size of a window's client area.
///
/// # Parameters:
///
/// - `const NSTDWindow *window` - The window.
///
/// # Returns
///
/// `NSTDWindowSize size` - The size of the window.
NSTDAPI NSTDWindowSize nstd_window_get_inner_size(const NSTDWindow *window);

/// Gets the full size of a window.
///
/// # Parameters:
///
/// - `const NSTDWindow *window` - The window.
///
/// # Returns
///
/// `NSTDWindowSize size` - The size of the window.
NSTDAPI NSTDWindowSize nstd_window_get_outer_size(const NSTDWindow *window);

/// Sets a window's minimum size.
///
/// # Parameters:
///
/// - `const NSTDWindow *window` - The window.
///
/// - `NSTDOptionalWindowSize size` - The minimum window size, pass none to disable clamping.
NSTDAPI void nstd_window_set_min_size(const NSTDWindow *window, NSTDOptionalWindowSize size);

/// Sets a window's maximum size.
///
/// # Parameters:
///
/// - `const NSTDWindow *window` - The window.
///
/// - `NSTDOptionalWindowSize size` - The maximum window size, pass none to disable clamping.
NSTDAPI void nstd_window_set_max_size(const NSTDWindow *window, NSTDOptionalWindowSize size);

/// Returns the scale factor of a window.
///
/// # Parameter:
///
/// - `const NSTDWindow *window` - The window.
///
/// # Returns
///
/// `NSTDFloat64 scale_factor` - The window's scale factor.
NSTDAPI NSTDFloat64 nstd_window_scale_factor(const NSTDWindow *window);

/// Sets whether or not a window is resizable.
///
/// # Parameters:
///
/// - `const NSTDWindow *window` - The window.
///
/// - `NSTDBool resizable` - True if the window should be resizable.
NSTDAPI void nstd_window_set_resizable(const NSTDWindow *window, NSTDBool resizable);

/// Checks if a window is resizable.
///
/// # Parameters:
///
/// - `const NSTDWindow *window` - The window.
///
/// # Returns
///
/// `NSTDBool is_resizable` - Returns true if the window is resizable.
NSTDAPI NSTDBool nstd_window_is_resizable(const NSTDWindow *window);

/// Sets the grabbing mode of the system cursor.
///
/// # Parameters:
///
/// - `const NSTDWindow *window` - The window.
///
/// - `NSTDCursorGrabMode mode` - The cursor grabbing mode.
///
/// # Returns
///
/// `NSTDErrorCode errc` - Nonzero on error.
///
/// # Errors
///
/// - `1` - The operating system is not currently supported.
///
/// - `2` - An operating system library function failed.
NSTDAPI NSTDErrorCode
nstd_window_set_cursor_grab_mode(const NSTDWindow *window, NSTDCursorGrabMode mode);

/// Sets whether or not the system cursor is visible.
///
/// # Parameters:
///
/// - `const NSTDWindow *window` - The window.
///
/// - `NSTDBool visible` - Determines whether or not the cursor should be visible.
NSTDAPI void nstd_window_set_cursor_visible(const NSTDWindow *window, NSTDBool visible);

/// Permanently closes & frees a window and it's data.
///
/// # Parameters:
///
/// - `NSTDWindow window` - The window to close.
NSTDAPI void nstd_window_close(NSTDWindow window);

#endif
