#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "bit_type.h"
#include "processor.h"

using namespace std;

vector<string> read_file(string filename = "program.txt")
{
    ifstream file(filename, ios_base::in);
    vector<string> ret{};
    string buff;
    while (getline(file, buff))
    {
        if (buff.empty() || buff[0] == '#' || buff[0] == '\r') continue;
        ret.push_back(buff);
        //cout << buff << "\n";
    }
    file.close();
    return ret;
}

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


    cout << "\nLoading and starting the program:\n";
    auto program = read_file();
    processor p(program);
    cout << p.get_program_info() << "\nStarting debug: \n";

    while (p.do_tick())
    {
        cout << p.get_state();
        p.end_tick();
#ifdef _WIN32
        cin.get();
#endif
    }
}