#include "processor.h"

#include <cstring>
#include <iomanip>
#include <algorithm>
#include <set>

using namespace std;

std::map<processor::command::name_t, const char*> processor::command::name_map{
	{push, "push"}, {pop, "pop"}, {add, "add"}, {sub, "sub"}, {mul, "mul"}, {div, "div"}, {dup, "dup"}, {rev, "rev"}
};

std::string processor::command::str() const
{
	stringstream ret;
	ret << name_map[name] << " " << val.get_bit_string();
	return ret.str();
}

processor::processor(vector<string> program, const size_t ram_size):
	PC(0), TC(0), RS(0), IR(), SL(), stack(stack_size)
{
	this->program = move(program);
}

bool processor::do_tick()
{
	if (PC >= program.size()) return false;

	if (TC == 0)
	{
		// Parsing command data from string
		stringstream s;
		s << program[PC];

		string str_name;
		s >> str_name;
		unsigned int name = 0;
		while (
			strcmp(str_name.c_str(), command::name_map[(command::name_t)name]) != 0 &&
			name < command::name_t::COUNT
			) name++;

		IR.name = (command::name_t)name;
		if (IR.name == command::push)
		{
			double buff;
			s >> buff;
			IR.val.set_double(buff);
		}
	}
	else if (TC == 1)
	{
		switch (IR.name)
		{
		case command::push:
			stack.push(IR.val);
			break;
		case command::pop:
			stack.pop();
			break;
		case command::add:
		{
			bit_type a = stack.pop();
			auto b = stack.top();
			b.set_double(b.get_double() + a.get_double());
			break;
		}
		case command::sub:
		{
			bit_type a = stack.pop();
			auto b = stack.top();
			b.set_double(b.get_double() - a.get_double());
			break;
		}
		case command::mul:
		{
			bit_type a = stack.pop();
			auto b = stack.top();
			b.set_double(b.get_double() * a.get_double());
			break;
		}
		case command::div:
		{
			bit_type a = stack.pop();
			auto b = stack.top();
			b.set_double(b.get_double() / a.get_double());
			break;
		}
		case command::dup:
			stack.duplicate();
			break;
		case command::rev:
			stack.swap();
			break;
		}
		RS = stack.top().get_sign();
		SL = stack.get_head();
	}

	return PC < program.size();
}
void processor::end_tick()
{
	if (TC == tc_num - 1) PC++;
	TC++;
	TC %= tc_num;
}

string to_binary(unsigned int n, size_t size)
{
	stringstream s;
	while (n > 0)
	{
		s << n % 2;
		n >>= 1;
	}
	string ret = s.str();
	reverse(ret.begin(), ret.end());
	ret = ((size - ret.size() > 0) ? string(size - ret.size(), '0') : "") + ret;
	/*for (int i = bitmem::item_size - 8; i > 0; i -= 8)
		ret.insert(i, 1, '.');*/
	return ret;
}

std::string processor::get_state() const
{
	static constexpr auto delim = "------------------------------------\n";

	stringstream ss;
	ss << delim << "IR = " << IR.str() << "\n\n";

	ss << "Stack state:\n";
	const auto stack_iter = stack.get_vector();
	for (short i = 0; i < stack_size; i++) {
		ss << ((short )SL == i) ? ">" : " ";
		ss << (*stack_iter)[i].get_bit_string() << " ";
		ss << (*stack_iter)[i].get_double() << "\n";
	}
	ss << "\n";
	ss << "PC = " << PC << "\n";
	ss << "TC = " << TC << "\n";
	ss << "RS = " << to_binary(RS, 8) << "\n";

	if (TC == tc_num - 1) ss << delim;

	return ss.str();
}

std::string processor::get_program_info() const
{
	stringstream ret;
	ret << "Total program length: " << program.size() << " lines\n";
	return ret.str();
}
