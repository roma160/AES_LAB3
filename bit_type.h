#pragma once
#include <string>

/// <summary>
/// The memory structure:
///
///	0..0sHHHH..HHHMMMMM..MMMM
///	Direction of indexing<---
///	                     3210
///
///	where
///	0 - zero bits
///	s - sign bit
///	H - exponent bit
/// M - digits bit
///
/// Special values reference:
///	s H    M       label
///	0 00h  000000h Positive zero
///	1 00h  000000h Negative zero
///	0 FFh  000000h Positive infinity
///	1 FFh  000000h Negative infinity
///	0 FFh >000000h NaN
/// </summary>
class bit_type
{
public:
	static constexpr short digits_len = 31;
	static constexpr short exponent_len = 11;
	static constexpr short exponent_digits_len = exponent_len + digits_len;
	typedef unsigned long long mem_t;

private:
	mem_t data;

	static inline mem_t get_mask(short start, short stop);

public:
	bit_type() : data(0){}

	mem_t get_range(short stop) const;
	mem_t get_range(short start, short stop) const;

	void set_range(short stop, mem_t value);
	void set_range(short start, short stop, mem_t value);

	mem_t get_sign() const;
	mem_t get_exponent() const;
	mem_t get_digits() const;

	void set_sign(mem_t value);
	void set_exponent(mem_t value);
	void set_digits(mem_t value);

	double get_double() const;
	void set_double(double value);

	void set_max();
	void set_min();
	void set_abs_min();

	void set_infty();
	void set_minfty();
	void set_nan();


	std::string get_bit_string() const;

	bit_type to_non_normalized() const;
};

