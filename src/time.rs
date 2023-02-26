//! Time utilities.
use crate::{
    core::{
        optional::{gen_optional, NSTDOptional},
        time::{
            nstd_core_time_duration_get, nstd_core_time_duration_nanoseconds,
            nstd_core_time_duration_new, nstd_core_time_duration_seconds, NSTDDuration,
        },
    },
    NSTDFloat64, NSTDInt64, NSTDUInt32,
};
use nstdapi::nstdapi;
use std::time::{SystemTime, UNIX_EPOCH};

/// A structure representing system time since January 1st 1970.
#[nstdapi]
#[derive(Clone, Copy, PartialEq)]
pub struct NSTDTime {
    /// The time span since January 1st 1970.
    duration: NSTDDuration,
}
impl From<SystemTime> for NSTDTime {
    /// Converts a [SystemTime] into an [NSTDTime] object.
    fn from(value: SystemTime) -> Self {
        match value.duration_since(UNIX_EPOCH) {
            Ok(dur) => NSTDTime {
                duration: nstd_core_time_duration_new(dur.as_secs_f64()),
            },
            Err(dur) => NSTDTime {
                duration: nstd_core_time_duration_new(-dur.duration().as_secs_f64()),
            },
        }
    }
}
gen_optional!(NSTDOptionalTime, NSTDTime);

/// Returns the current system time as an `NSTDTime` object.
///
/// # Returns
///
/// `NSTDTime time` - The current time.
#[inline]
#[nstdapi]
pub fn nstd_time_now() -> NSTDTime {
    NSTDTime::from(SystemTime::now())
}

/// Returns the number of seconds stored in an `NSTDTime` object as an `NSTDFloat64`.
///
/// # Parameters:
///
/// - `const NSTDTime *time` - The time object.
///
/// # Returns
///
/// `NSTDFloat64 seconds` - The number of seconds in a time object represented as an
/// `NSTDFloat64`.
#[inline]
#[nstdapi]
pub fn nstd_time_get(time: &NSTDTime) -> NSTDFloat64 {
    nstd_core_time_duration_get(&time.duration)
}

/// Returns the number of seconds in an `NSTDTime` object.
///
/// # Parameters:
///
/// - `const NSTDTime *time` - The time object.
///
/// # Returns
///
/// `NSTDInt64 seconds` - The number of seconds held in `time`.
#[inline]
#[nstdapi]
pub fn nstd_time_seconds(time: &NSTDTime) -> NSTDInt64 {
    nstd_core_time_duration_seconds(&time.duration)
}

/// Returns the number of nanoseconds in an `NSTDTime` object.
///
/// # Parameters:
///
/// - `const NSTDTime *time` - The time object.
///
/// # Returns
///
/// `NSTDUInt32 nanoseconds` - The number of nanoseconds held in `time`.
#[inline]
#[nstdapi]
pub fn nstd_time_nanoseconds(time: &NSTDTime) -> NSTDUInt32 {
    nstd_core_time_duration_nanoseconds(&time.duration)
}

/// Computes the addition of an `NSTDTime` object and an `NSTDDuration`.
///
/// # Parameters:
///
/// - `const NSTDTime *time` - The time object
///
/// - `const NSTDDuration *duration` - The duration to add.
///
/// # Returns
///
/// `NSTDTime time` - The result of the addition.
#[inline]
#[nstdapi]
pub fn nstd_time_add(time: &NSTDTime, duration: &NSTDDuration) -> NSTDTime {
    let secs = nstd_core_time_duration_get(&time.duration) + nstd_core_time_duration_get(duration);
    NSTDTime {
        duration: nstd_core_time_duration_new(secs),
    }
}

/// Computes the subtraction between an `NSTDTime` object and an `NSTDDuration`.
///
/// # Parameters:
///
/// - `const NSTDTime *time` - The time object
///
/// - `const NSTDDuration *duration` - The duration to subtract.
///
/// # Returns
///
/// `NSTDTime time` - The result of the subtraction.
#[inline]
#[nstdapi]
pub fn nstd_time_sub(time: &NSTDTime, duration: &NSTDDuration) -> NSTDTime {
    let secs = nstd_core_time_duration_get(&time.duration) - nstd_core_time_duration_get(duration);
    NSTDTime {
        duration: nstd_core_time_duration_new(secs),
    }
}
