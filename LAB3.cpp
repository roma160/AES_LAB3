#include <iostream>
#include "bit_type.h"

using namespace std;

int main()
{
    bit_type t;
    t.set_range(31, 1000);
    t.set_range(31, 42, 1024);
    cout << t.get_double();
}