#ifndef NSTD_OS_WINDOWS_WINDOWS_H
#define NSTD_OS_WINDOWS_WINDOWS_H

/// Constant that is only set if the target operating system is Windows.
#if defined(__WINDOWS__)\
    || defined(_WIN32)\
    || defined(_WIN64)\
    || defined(__WIN32__)\
    || defined(__TOS_WIN__)
#define NSTD_OS_WINDOWS
#endif

#endif
