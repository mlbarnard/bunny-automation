# bunny-automation
Automation game loosely inspired by Conway's game of life
This is one learning project of several, most of the code is likely ignorantly constructed at the moment.

## Game Rules
The game runs on a tick system where every tick represents one year. Every tick bunnies die, have babies, become radioactive mutant vampires, or do nothing.
- The gameboard consists of a 100x100 grid.  Every tick bunnies move one square.
-- Movement is random for now but adding water/food requirements or other motivators would make the game much more Life-like
- At game start 5 bunnies are created with random distribution of genders and colors.
- Each tick ages bunnies one year.
- Bunnies hit adulthood at age 2 and die at age 10.
- If there is an adult male and female bunny within a square of each other, the female will attempt to fill 7 adjacent squares with kits. (e.g. M_F or closer results in bunnies)
-- Newborn bunnies have the same coat color as the mother
- Some bunnies are born as radioactive mutant vampire bunnies (RMVBs). Current rate is 2%.
- RMVBs die at age 50 and cannot reproduce.
- If RMVB is directly adjacent to a normal bunny at any point it will convert that bunny to a RMVB.
- If there are more than 1000 bunnies alive a food shortage occurs and every bunny has a 50% chance of starving.

## Future Work
- Current state is text only and lacking the graph-ness of Life, obviously this is first.
- Add motivators for the various bunnies.
-- Food, water, radioactive zones, predators, etc?
- Seed system where all randomness comes from one input so you can have repeatable scenarios.

Idea comes from some random old forum post, no idea of the original. I've modified it a little bit and made some decisions one way or another where the instructions were unclear.
http://www.cplusplus.com/forum/articles/12974/
