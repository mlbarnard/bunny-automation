/*
    Bunny class functions
    Must initialize random in main function where this is used
*/

#include <vector>
#include <string>
#include "bunny.h"

// Every bunny has a certain chance of being born male or female
#define MALE_BUNNY_PCT 50
// Every bunny has a chance of being born a radioactive mutant vampire bunny 
#define RAD_BUNNY_PCT 2 // in % chance

static std::vector<std::string> bunny_names = 
{
    "Ralph",
    "Hopper",
    "Steve",
    "James",
    "Amy",
    "Yanny",
    "Lauryl",
    "Guillermo"};

static std::vector<std::string> rad_bunny_names = 
{
    "Jessica",
    "Darth Vader"
};

static std::vector<std::string> colors = 
{
    "white",
    "brown",
    "black",
    "spotted"
};

// seed must be 0-99
Bunny::Bunny(const uint32_t seed)
{
    sex = (seed < MALE_BUNNY_PCT) ? 'm' : 'f';
    age = 0;
    if(seed < RAD_BUNNY_PCT)
    {
        radioactive = true;
        name = rad_bunny_names[seed % rad_bunny_names.size()];
    } else
    {
        radioactive = false;
        name = bunny_names[seed % bunny_names.size()];
    }
    color = colors[seed % colors.size()];
}

uint32_t Bunny::aging()
{
    return ++age;
}

// True if bunny is newly radioactive, false if it was already radioactive
bool Bunny::irradiated()
{
    // If bunny is already radioactive, return failure
    if(radioactive) return false;

    radioactive = true;
    return true;
}