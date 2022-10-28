//! Operator overloading for types and operators that may cause overflow.
//!
//! The types of overflows that this module attempts to catch can be found
//! [here](https://doc.rust-lang.org/reference/expressions/operator-expr.html#overflow).
//!
//! Also see [this](https://github.com/RustEnthusiast/nstd/issues/22) issue for more information.
use crate::{
    NSTDFloat32, NSTDFloat64, NSTDInt, NSTDInt16, NSTDInt32, NSTDInt64, NSTDInt8, NSTDUInt,
    NSTDUInt16, NSTDUInt32, NSTDUInt64, NSTDUInt8,
};

/// Generates the increment (++) operator implementations.
macro_rules! gen_inc {
    ($name: ident, $T: ty) => {
        /// Increments `x` by 1.
        ///
        /// # Parameters:
        ///
        #[doc = concat!(" - `", stringify!($T), " x` - The value to increment.")]
        #[inline]
        #[cfg_attr(feature = "clib", no_mangle)]
        pub extern "C" fn $name(x: $T) {
            *x += 1;
        }
    };
}
/// Generates the increment (++) operator implementations for floating point numbers.
macro_rules! gen_inc_f {
    ($name: ident, $T: ty) => {
        /// Increments `x` by 1.
        ///
        /// # Parameters:
        ///
        #[doc = concat!(" - `", stringify!($T), " x` - The value to increment.")]
        #[inline]
        #[cfg_attr(feature = "clib", no_mangle)]
        pub extern "C" fn $name(x: $T) {
            *x += 1.0;
        }
    };
}
gen_inc_f!(nstd_core_ops_inc_f32, &mut NSTDFloat32);
gen_inc_f!(nstd_core_ops_inc_f64, &mut NSTDFloat64);
gen_inc!(nstd_core_ops_inc_int, &mut NSTDInt);
gen_inc!(nstd_core_ops_inc_uint, &mut NSTDUInt);
gen_inc!(nstd_core_ops_inc_i8, &mut NSTDInt8);
gen_inc!(nstd_core_ops_inc_u8, &mut NSTDUInt8);
gen_inc!(nstd_core_ops_inc_i16, &mut NSTDInt16);
gen_inc!(nstd_core_ops_inc_u16, &mut NSTDUInt16);
gen_inc!(nstd_core_ops_inc_i32, &mut NSTDInt32);
gen_inc!(nstd_core_ops_inc_u32, &mut NSTDUInt32);
gen_inc!(nstd_core_ops_inc_i64, &mut NSTDInt64);
gen_inc!(nstd_core_ops_inc_u64, &mut NSTDUInt64);

/// Generates the decrement (--) operator implementations.
macro_rules! gen_dec {
    ($name: ident, $T: ty) => {
        /// Decrements `x` by 1.
        ///
        /// # Parameters:
        ///
        #[doc = concat!(" - `", stringify!($T), " x` - The value to decrement.")]
        #[inline]
        #[cfg_attr(feature = "clib", no_mangle)]
        pub extern "C" fn $name(x: $T) {
            *x -= 1;
        }
    };
}
/// Generates the decrement (--) operator implementations for floating point numbers.
macro_rules! gen_dec_f {
    ($name: ident, $T: ty) => {
        /// Decrements `x` by 1.
        ///
        /// # Parameters:
        ///
        #[doc = concat!(" - `", stringify!($T), " x` - The value to decrement.")]
        #[inline]
        #[cfg_attr(feature = "clib", no_mangle)]
        pub extern "C" fn $name(x: $T) {
            *x -= 1.0;
        }
    };
}
gen_dec_f!(nstd_core_ops_dec_f32, &mut NSTDFloat32);
gen_dec_f!(nstd_core_ops_dec_f64, &mut NSTDFloat64);
gen_dec!(nstd_core_ops_dec_int, &mut NSTDInt);
gen_dec!(nstd_core_ops_dec_uint, &mut NSTDUInt);
gen_dec!(nstd_core_ops_dec_i8, &mut NSTDInt8);
gen_dec!(nstd_core_ops_dec_u8, &mut NSTDUInt8);
gen_dec!(nstd_core_ops_dec_i16, &mut NSTDInt16);
gen_dec!(nstd_core_ops_dec_u16, &mut NSTDUInt16);
gen_dec!(nstd_core_ops_dec_i32, &mut NSTDInt32);
gen_dec!(nstd_core_ops_dec_u32, &mut NSTDUInt32);
gen_dec!(nstd_core_ops_dec_i64, &mut NSTDInt64);
gen_dec!(nstd_core_ops_dec_u64, &mut NSTDUInt64);

/// Generates the negate (-) operator implementation, this is not to be confused with the
/// subtraction operator.
macro_rules! gen_neg {
    ($name: ident, $T: ty) => {
        /// Returns the negative value of `x`.
        ///
        /// # Parameters:
        ///
        #[doc = concat!(" - `", stringify!($T), " x` - The value to negate.")]
        ///
        /// # Returns
        ///
        #[doc = concat!(" `", stringify!($T), " v` - The negative value of `x`.")]
        #[inline]
        #[cfg_attr(feature = "clib", no_mangle)]
        pub extern "C" fn $name(x: $T) -> $T {
            -x
        }
    };
}
gen_neg!(nstd_core_ops_neg_f32, NSTDFloat32);
gen_neg!(nstd_core_ops_neg_f64, NSTDFloat64);
gen_neg!(nstd_core_ops_neg_int, NSTDInt);
gen_neg!(nstd_core_ops_neg_i8, NSTDInt8);
gen_neg!(nstd_core_ops_neg_i16, NSTDInt16);
gen_neg!(nstd_core_ops_neg_i32, NSTDInt32);
gen_neg!(nstd_core_ops_neg_i64, NSTDInt64);

/// Generates the addition (+) operator implementations.
macro_rules! gen_add {
    ($name: ident, $T: ty) => {
        /// Computes the addition operation of `x` + `y`.
        ///
        /// # Parameters:
        ///
        #[doc = concat!(" - `", stringify!($T), " x` - The left operand.")]
        ///
        #[doc = concat!(" - `", stringify!($T), " y` - The right operand.")]
        ///
        /// # Returns
        ///
        #[doc = concat!(" `", stringify!($T), " z` - The result of the operation.")]
        #[inline]
        #[cfg_attr(feature = "clib", no_mangle)]
        pub extern "C" fn $name(x: $T, y: $T) -> $T {
            x + y
        }
    };
}
gen_add!(nstd_core_ops_add_f32, NSTDFloat32);
gen_add!(nstd_core_ops_add_f64, NSTDFloat64);
gen_add!(nstd_core_ops_add_int, NSTDInt);
gen_add!(nstd_core_ops_add_uint, NSTDUInt);
gen_add!(nstd_core_ops_add_i8, NSTDInt8);
gen_add!(nstd_core_ops_add_u8, NSTDUInt8);
gen_add!(nstd_core_ops_add_i16, NSTDInt16);
gen_add!(nstd_core_ops_add_u16, NSTDUInt16);
gen_add!(nstd_core_ops_add_i32, NSTDInt32);
gen_add!(nstd_core_ops_add_u32, NSTDUInt32);
gen_add!(nstd_core_ops_add_i64, NSTDInt64);
gen_add!(nstd_core_ops_add_u64, NSTDUInt64);

/// Generates the subtraction (-) operator implementations.
macro_rules! gen_sub {
    ($name: ident, $T: ty) => {
        /// Computes the subtraction operation of `x` - `y`.
        ///
        /// # Parameters:
        ///
        #[doc = concat!(" - `", stringify!($T), " x` - The left operand.")]
        ///
        #[doc = concat!(" - `", stringify!($T), " y` - The right operand.")]
        ///
        /// # Returns
        ///
        #[doc = concat!(" `", stringify!($T), " z` - The result of the operation.")]
        #[inline]
        #[cfg_attr(feature = "clib", no_mangle)]
        pub extern "C" fn $name(x: $T, y: $T) -> $T {
            x - y
        }
    };
}
gen_sub!(nstd_core_ops_sub_f32, NSTDFloat32);
gen_sub!(nstd_core_ops_sub_f64, NSTDFloat64);
gen_sub!(nstd_core_ops_sub_int, NSTDInt);
gen_sub!(nstd_core_ops_sub_uint, NSTDUInt);
gen_sub!(nstd_core_ops_sub_i8, NSTDInt8);
gen_sub!(nstd_core_ops_sub_u8, NSTDUInt8);
gen_sub!(nstd_core_ops_sub_i16, NSTDInt16);
gen_sub!(nstd_core_ops_sub_u16, NSTDUInt16);
gen_sub!(nstd_core_ops_sub_i32, NSTDInt32);
gen_sub!(nstd_core_ops_sub_u32, NSTDUInt32);
gen_sub!(nstd_core_ops_sub_i64, NSTDInt64);
gen_sub!(nstd_core_ops_sub_u64, NSTDUInt64);

/// Generates the multiplication (*) operator implementations.
macro_rules! gen_mul {
    ($name: ident, $T: ty) => {
        /// Computes the multiplication operation of `x` * `y`.
        ///
        /// # Parameters:
        ///
        #[doc = concat!(" - `", stringify!($T), " x` - The left operand.")]
        ///
        #[doc = concat!(" - `", stringify!($T), " y` - The right operand.")]
        ///
        /// # Returns
        ///
        #[doc = concat!(" `", stringify!($T), " z` - The result of the operation.")]
        #[inline]
        #[cfg_attr(feature = "clib", no_mangle)]
        pub extern "C" fn $name(x: $T, y: $T) -> $T {
            x * y
        }
    };
}
gen_mul!(nstd_core_ops_mul_f32, NSTDFloat32);
gen_mul!(nstd_core_ops_mul_f64, NSTDFloat64);
gen_mul!(nstd_core_ops_mul_int, NSTDInt);
gen_mul!(nstd_core_ops_mul_uint, NSTDUInt);
gen_mul!(nstd_core_ops_mul_i8, NSTDInt8);
gen_mul!(nstd_core_ops_mul_u8, NSTDUInt8);
gen_mul!(nstd_core_ops_mul_i16, NSTDInt16);
gen_mul!(nstd_core_ops_mul_u16, NSTDUInt16);
gen_mul!(nstd_core_ops_mul_i32, NSTDInt32);
gen_mul!(nstd_core_ops_mul_u32, NSTDUInt32);
gen_mul!(nstd_core_ops_mul_i64, NSTDInt64);
gen_mul!(nstd_core_ops_mul_u64, NSTDUInt64);

/// Generates the division (/) operator implementations.
macro_rules! gen_div {
    ($name: ident, $T: ty) => {
        /// Computes the division operation of `x` / `y`.
        ///
        /// # Parameters:
        ///
        #[doc = concat!(" - `", stringify!($T), " x` - The left operand.")]
        ///
        #[doc = concat!(" - `", stringify!($T), " y` - The right operand.")]
        ///
        /// # Returns
        ///
        #[doc = concat!(" `", stringify!($T), " z` - The result of the operation.")]
        #[inline]
        #[cfg_attr(feature = "clib", no_mangle)]
        pub extern "C" fn $name(x: $T, y: $T) -> $T {
            x / y
        }
    };
}
gen_div!(nstd_core_ops_div_f32, NSTDFloat32);
gen_div!(nstd_core_ops_div_f64, NSTDFloat64);
gen_div!(nstd_core_ops_div_int, NSTDInt);
gen_div!(nstd_core_ops_div_uint, NSTDUInt);
gen_div!(nstd_core_ops_div_i8, NSTDInt8);
gen_div!(nstd_core_ops_div_u8, NSTDUInt8);
gen_div!(nstd_core_ops_div_i16, NSTDInt16);
gen_div!(nstd_core_ops_div_u16, NSTDUInt16);
gen_div!(nstd_core_ops_div_i32, NSTDInt32);
gen_div!(nstd_core_ops_div_u32, NSTDUInt32);
gen_div!(nstd_core_ops_div_i64, NSTDInt64);
gen_div!(nstd_core_ops_div_u64, NSTDUInt64);

/// Generates the remainder (%) operator implementations.
macro_rules! gen_rem {
    ($name: ident, $T: ty) => {
        /// Computes the remainder of `x` / `y`.
        ///
        /// # Parameters:
        ///
        #[doc = concat!(" - `", stringify!($T), " x` - The left operand.")]
        ///
        #[doc = concat!(" - `", stringify!($T), " y` - The right operand.")]
        ///
        /// # Returns
        ///
        #[doc = concat!(" `", stringify!($T), " z` - The result of the operation.")]
        #[inline]
        #[cfg_attr(feature = "clib", no_mangle)]
        pub extern "C" fn $name(x: $T, y: $T) -> $T {
            x % y
        }
    };
}
gen_rem!(nstd_core_ops_rem_f32, NSTDFloat32);
gen_rem!(nstd_core_ops_rem_f64, NSTDFloat64);
gen_rem!(nstd_core_ops_rem_int, NSTDInt);
gen_rem!(nstd_core_ops_rem_uint, NSTDUInt);
gen_rem!(nstd_core_ops_rem_i8, NSTDInt8);
gen_rem!(nstd_core_ops_rem_u8, NSTDUInt8);
gen_rem!(nstd_core_ops_rem_i16, NSTDInt16);
gen_rem!(nstd_core_ops_rem_u16, NSTDUInt16);
gen_rem!(nstd_core_ops_rem_i32, NSTDInt32);
gen_rem!(nstd_core_ops_rem_u32, NSTDUInt32);
gen_rem!(nstd_core_ops_rem_i64, NSTDInt64);
gen_rem!(nstd_core_ops_rem_u64, NSTDUInt64);

/// Generates the shift left (<<) operator implementations.
macro_rules! gen_shl {
    ($name: ident, $T: ty) => {
        /// Shifts value `x` `y` bits to the left.
        ///
        /// # Parameters:
        ///
        #[doc = concat!(" - `", stringify!($T), " x` - The value to shift.")]
        ///
        #[doc = concat!(" - `", stringify!($T), " y` - The number of bits to shift.")]
        ///
        /// # Returns
        ///
        #[doc = concat!(" `", stringify!($T), " z` - The result of the operation.")]
        #[inline]
        #[cfg_attr(feature = "clib", no_mangle)]
        pub extern "C" fn $name(x: $T, y: $T) -> $T {
            x << y
        }
    };
}
gen_shl!(nstd_core_ops_shl_int, NSTDInt);
gen_shl!(nstd_core_ops_shl_uint, NSTDUInt);
gen_shl!(nstd_core_ops_shl_i8, NSTDInt8);
gen_shl!(nstd_core_ops_shl_u8, NSTDUInt8);
gen_shl!(nstd_core_ops_shl_i16, NSTDInt16);
gen_shl!(nstd_core_ops_shl_u16, NSTDUInt16);
gen_shl!(nstd_core_ops_shl_i32, NSTDInt32);
gen_shl!(nstd_core_ops_shl_u32, NSTDUInt32);
gen_shl!(nstd_core_ops_shl_i64, NSTDInt64);
gen_shl!(nstd_core_ops_shl_u64, NSTDUInt64);

/// Generates the shift right (>>) operator implementations.
macro_rules! gen_shr {
    ($name: ident, $T: ty) => {
        /// Shifts value `x` `y` bits to the right.
        ///
        /// # Parameters:
        ///
        #[doc = concat!(" - `", stringify!($T), " x` - The value to shift.")]
        ///
        #[doc = concat!(" - `", stringify!($T), " y` - The number of bits to shift.")]
        ///
        /// # Returns
        ///
        #[doc = concat!(" `", stringify!($T), " z` - The result of the operation.")]
        #[inline]
        #[cfg_attr(feature = "clib", no_mangle)]
        pub extern "C" fn $name(x: $T, y: $T) -> $T {
            x >> y
        }
    };
}
gen_shr!(nstd_core_ops_shr_int, NSTDInt);
gen_shr!(nstd_core_ops_shr_uint, NSTDUInt);
gen_shr!(nstd_core_ops_shr_i8, NSTDInt8);
gen_shr!(nstd_core_ops_shr_u8, NSTDUInt8);
gen_shr!(nstd_core_ops_shr_i16, NSTDInt16);
gen_shr!(nstd_core_ops_shr_u16, NSTDUInt16);
gen_shr!(nstd_core_ops_shr_i32, NSTDInt32);
gen_shr!(nstd_core_ops_shr_u32, NSTDUInt32);
gen_shr!(nstd_core_ops_shr_i64, NSTDInt64);
gen_shr!(nstd_core_ops_shr_u64, NSTDUInt64);
