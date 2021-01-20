/*
    Radioactive Bunny Game

*/

#include <cstdlib>
#include <ctime>
#include <vector>
#include <list>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "bunny.h"

// At program start, create bunnies
#define INITIAL_BUNNIES 5
// Every turn:
// - bunnies age one year
// - a new bunny is created for every adult female if there is at least one adult male 
// - any bunny over max age dies
#define BUNNY_MAX_AGE 10

// If the number of bunnies gets too large a food shortage will occur
#define MAX_BUNNIES 1000
#define BUNNY_FOOD_KILL_PCT 50 // in % chance

// Some bunnies are born as radioactive mutant vampire bunnies
// Each rad bunny tries to convert another bunny into a rad bunny every turn
// Rad bunnies do not count as adult bunnies
// Rad bunnies have a different max age
#define RAD_BUNNY_MAX_AGE 50


// TOO MANY BUNNIES, bunny massacre time
void food_shortage(std::list<Bunny> &bun_list)
{
    std::cout << "Oh no! Too many bunnies to feed!" << '\n';
    std::cout << "Total before starvation:" << bun_list.size() << '\n';

    auto&& iter = bun_list.begin();

    // Go through all bunnies and check if they starved
    while(iter != bun_list.end())
    {
        if(static_cast<uint32_t>(std::rand() % 100) < BUNNY_FOOD_KILL_PCT)
        {
            if(iter->is_rad()) 
                std::cout << "Radioactive Mutant Vampire Bunny "
                    << iter->get_name() << "has died!" << '\n';
            else
                std::cout << "Bunny "
                    << iter->get_name() << "has died!" << '\n';
                    
            iter = bun_list.erase(iter);
        }
    }

    std::cout << "Total after starvation:" << bun_list.size() << '\n';
}


int main()
{
    // Initialize RNG, use current time as seed
    std::srand(std::time(nullptr)); // TODO: Should this technically be casted?

    // Create initial bunnies
    std::list<Bunny> bun_list;
    for(uint32_t i = 0; i < INITIAL_BUNNIES; i++)
    {
        // Note bias because %
        bun_list.push_back(Bunny(static_cast<uint32_t>(std::rand() % 100)));
    }

    // DEBUG: Confirm bunnies are properly created
    for(auto i : bun_list)
    {
        std::cout << i.get_name() << '\n';
    }

    /*  Each loop is one timestep, run until all bunnies are dead
        Every tick:
            Age bunnies
            Keep track of if there is a male, # of females, and # of rad bunnies
            Check max age (normal and rad) and die if necessary
                Max age normal bunnies cannot survive the rad transition and still die
            Change bunnies into required number of rad bunnies
            New bunnies are born
    */
    uint32_t num_ticks = 0;
    while(!bun_list.empty())
    {
        std::cout << "Year " << num_ticks << '\n';

        // Need one living male to reproduce
        uint32_t num_males = 0;
        // Count how many healthy females for kits
        uint32_t num_females = 0;
        // Count how many radioactive for new rad bunnies
        uint32_t num_radioactive = 0;

        auto&& iter = bun_list.begin();
        
        do
        {
            // Bunny gets older, save age to test for murder
            uint32_t new_age = iter->aging();

            // Rad or nah
            if(iter->is_rad())
            {
                num_radioactive++;

                // Check for max age and kill the current bunny if needed
                // This increments the list automatically
                if(new_age >= RAD_BUNNY_MAX_AGE)
                {
                    std::cout << "Radioactive Mutant Vampire Bunny "
                        << iter->get_name() << " has died!" << '\n';
                    iter = bun_list.erase(iter);
                }
                else iter++;
            }
            else
            {
                if(iter->get_sex() == 'f') num_females++;
                else num_males++;

                // Check for max age and kill the current bunny if needed
                // This increments the list automatically
                if(new_age >= BUNNY_MAX_AGE){
                    std::cout << "Bunny "
                        << iter->get_name() << " has died!" << '\n';
                    iter = bun_list.erase(iter);
                }
                else iter++;
            }
        } while(iter != bun_list.end());

        // Is there gonna be a food shortage?
        if(bun_list.size() > MAX_BUNNIES) food_shortage(bun_list);

        std::cout << '\n' << "Living bunnies:" << '\n';
        std::cout << "Males:" << num_males << '\n';
        std::cout << "Females:" << num_females << '\n';
        std::cout << "Radioactive:" << num_radioactive << '\n';

        // Attempt to irradiate bunnies
        // std::vector<std::reference_wrapper<Bunny>>
        //     bunny_shuffle(bun_list.begin(), bun_list.end());
        // uint32_t bunnies_radiated = 0, i = 0;
        // Need better randomization, also perhaps a vector was the right
        //  choice after all.
        uint32_t i = 0;
        while(i < num_radioactive && bun_list.size() > 1)
        {
            // Choose random bunny
            uint32_t chosen_bunny = 
                static_cast<uint32_t>(std::rand() % bun_list.size());
            
            std::list<Bunny>::iterator iter =
                std::next(bun_list.begin(), chosen_bunny);
            
            iter->irradiated();

            i++;
        }

        // New bunnies are born
        if(num_males > 0)
        {
            if(num_females > 1) std::cout << "Bunnies ";
            else if(num_females > 0) std::cout << "Bunny ";

            for(uint32_t i = 0; i < num_females; i++)
            {
                bun_list.push_back(Bunny(static_cast<uint32_t>(std::rand() % 100)));

                if(i > 0) std::cout << ", ";
                std::cout << bun_list.back().get_name();
            }

            if(num_females > 1) std::cout << " have been born!" << '\n';
            else if(num_females > 0) std::cout << " has been born!" << '\n';

        }

        num_ticks++;

        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << '\n' << '\n';
    }
    
}