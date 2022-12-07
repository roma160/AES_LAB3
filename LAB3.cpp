#include <iostream>
#include "bit_type.h"

using namespace std;

int main()
{
    bit_type buff;
    cout << "Double demo:\n";

    buff.set_abs_min();
    cout << buff.get_bit_string() << " " << buff.get_double() << "\n";

    buff.set_max();
    cout << buff.get_bit_string() << " " << buff.get_double() << "\n";

    buff.set_min();
    cout << buff.get_bit_string() << " " << buff.get_double() << "\n";

    buff.set_double(1);
    cout << buff.get_bit_string() << " " << buff.get_double() << "\n";

    buff.set_infty();
    cout << buff.get_bit_string() << " " << buff.get_double() << "\n";

    buff.set_minfty();
    cout << buff.get_bit_string() << " " << buff.get_double() << "\n";

    buff.set_double(5);
    bit_type non_norm = buff.to_non_normalized();
    cout << non_norm.get_bit_string() << " " << buff.get_double() << "\n";

    buff.set_nan();
    cout << buff.get_bit_string() << " " << buff.get_double() << "\n";
}