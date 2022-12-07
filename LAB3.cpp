#include <iostream>
#include "bit_type.h"

using namespace std;

int main()
{
    bit_type min_abs, min, max, one, inf, zero;
    min_abs.set_digits(0);
    min_abs.set_exponent(1);
    min.set_digits((1<<31) - 1);
    min.set_exponent((1<<11) - 2);
    min.set_sign(1);
    max.set_digits((1 << 31) - 1);
    max.set_exponent((1 << 11) - 2);
    cout << min_abs.get_double() << " " << min_abs.get_bit_string()<<"\n";
    cout << min.get_double() << " " << min.get_bit_string() << "\n";
    cout << max.get_double() << " " << max.get_bit_string() << "\n";

    bit_type non_norm;
    non_norm.set_double(1);
    cout << non_norm.get_bit_string() << " ";
    non_norm = non_norm.to_non_normalized();
    cout << non_norm.get_bit_string() << "\n";

    zero.set_double(0);
    cout << zero.get_bit_string() << "\n";
}