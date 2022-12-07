#include "bit_type.h"
#include <sstream>
#include <algorithm>

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

void bit_type::set_sign(mem_t value)
{
	set_range(exponent_digits_len, exponent_digits_len + 1, value);
}

void bit_type::set_exponent(mem_t value)
{
	set_range(digits_len, exponent_digits_len, value);
}

void bit_type::set_digits(mem_t value)
{
	set_range(digits_len, value);
}

bit_type::mem_t bit_type::get_exponent() const
{
	return get_range(digits_len, exponent_digits_len);
}


union mem_t_to_double
{
	bit_type::mem_t bits;
	double floating;
};

double bit_type::get_double() const
{
	mem_t digits = get_digits() & get_mask(0, 52); // 52
	mem_t exponent = get_exponent() & get_mask(0, 11); // 11
	mem_t sign = get_sign(); // 1

	// TODO: in case, exponent size changes, we need to shift sign bit

	mem_t_to_double ret{ (sign << 63) | (exponent << 52) | (digits << (52 - digits_len)) };
	return ret.floating;
}

void bit_type::set_double(double value)
{
	mem_t_to_double buff{};
	buff.floating = value;

	// TODO: this thing is adjusted only to the variant's exponent size
	set_range(digits_len, exponent_digits_len + 1, buff.bits >> 52);
	set_range(digits_len, (buff.bits & get_mask(0, 52)) >> (52 - digits_len));
}

void bit_type::set_double_from_str(std::string str)
{ set_double(std::stod(str)); }

void bit_type::set_max()
{
	set_digits((1 << digits_len) - 1);
	set_exponent((1 << exponent_len) - 2);
	set_digits(0);
}

void bit_type::set_min()
{
	set_digits((1 << digits_len) - 1);
	set_exponent((1 << exponent_len) - 2);
	set_sign(1);
}

void bit_type::set_abs_min()
{
	set_digits(1);
	set_exponent(0);
	set_sign(0);
}

void bit_type::set_infty()
{
	set_digits(0);
	set_exponent((1 << exponent_len) - 1);
	set_sign(0);
}

void bit_type::set_minfty()
{
	set_digits(0);
	set_exponent((1 << exponent_len) - 1);
	set_sign(1);
}

void bit_type::set_nan()
{
	set_digits(1);
	set_exponent((1 << exponent_len) - 1);
	set_sign(0);
}

std::string to_bite_string(bit_type::mem_t n, short length)
{
	std::stringstream s;
	for (short i = 0; i < length; i++)
	{
		s << n % 2;
		n >>= 1;
	}
	std::string ret = s.str();
	std::reverse(ret.begin(), ret.end());
	return ret;
}

std::string bit_type::get_bit_string() const
{
	return to_bite_string(data, exponent_digits_len + 1);
}

bit_type bit_type::to_non_normalized() const
{
	bit_type ret = *this;
	ret.set_digits((1 << (digits_len - 1)) + (get_digits() >> 1));
	ret.set_exponent(((unsigned) get_exponent()) + 1);
	return ret;
}
