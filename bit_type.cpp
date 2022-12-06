#include "bit_type.h"

bit_type::mem_t bit_type::get_mask(short start, short stop)
{
	return ((mem_t)1 << stop) - ((mem_t)1 << start);
}

bit_type::mem_t bit_type::get_range(short stop) const
{
	return get_range(0, stop);
}

bit_type::mem_t bit_type::get_range(short start, short stop) const
{
	return (data & get_mask(start, stop)) >> start;
}

void bit_type::set_range(short stop, mem_t value)
{
	set_range(0, stop, value);
}

void bit_type::set_range(short start, short stop, mem_t value)
{
	mem_t mask = get_mask(start, stop);
	data = (data & ~mask) | ((value << start) & mask);
}

bit_type::mem_t bit_type::get_sign() const
{
	return get_range(exponent_digits_len, exponent_digits_len + 1);
}

bit_type::mem_t bit_type::get_digits() const
{
	return get_range(digits_len);
}

bit_type::mem_t bit_type::get_exponent() const
{
	return get_range(digits_len, exponent_digits_len);
}

double bit_type::get_double() const
{
	mem_t digits = get_digits() & get_mask(0, 52);
	mem_t exponent = get_exponent() & get_mask(0, 11);
	mem_t sign = get_sign();

	union mem_t_to_double
	{
		mem_t input;
		double output;
	} ret{ (sign << 63) | (exponent << 52) | digits };
	return ret.output;
}
