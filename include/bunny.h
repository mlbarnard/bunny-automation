#pragma once

#include <string>

class Bunny
{
    public:
        Bunny(const uint32_t seed); // seed must be 0-99
        uint32_t aging();
        bool irradiated();

        char get_sex() { return sex; };
        uint32_t get_age() { return age; };
        bool is_rad() { return radioactive; };
        std::basic_string<char> get_name() { return name; };
        std::basic_string<char> get_color() { return color; };

    private:
        char sex;
        uint32_t age;
        bool radioactive;
        std::basic_string<char> name;
        std::basic_string<char> color;
};