#pragma once
#include <vector>
#include <stack>
#include <string>
#include <sstream>
#include <map>

#include "bit_type.h"
#include "mod_stack.h"

/// <summary>
/// Stack-processor model
/// </summary>
class processor
{
private:
    static constexpr short stack_size = 8;
    mod_stack<bit_type> stack;
    static const unsigned int tc_num = 2;
    unsigned int PC, TC, RS, SL;

    struct command
    {
        enum name_t : unsigned int
        {
            push, pop,
        	add, sub, mul, div,
            dup, rev,
            COUNT
        };
        static std::map<name_t, const char*> name_map;

        name_t name;
        bit_type val;

        std::string str() const;
    } IR;

    std::vector<std::string> program;

public:
    processor(std::vector<std::string> program, size_t ram_size = 10);

    bool do_tick();
    void end_tick();

    std::string get_state() const;

    std::string get_program_info() const;
};
