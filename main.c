/** @file main.c
 *  @brief Brief explanation of the main.c
 */

#include <stdio.h>
#include "Globals.h"
#include "Time.h"
#include "World.h"
#include "Creature.h"

//prototypes
void GameLoop();/*!< Detailed description after the member function*/

struct Time myTime;/*!< Detailed description after the member */
struct World world;/*!< Detailed description after the member */


/**
 * @brief this main function
 * @return 0 for program kill
 */
 
int main()
{
	
	/** @code */
	
	finished = 0;
	GRID_WIDTH = 75;/*!< Detailed description after the member */
	GRID_HEIGHT = 35;/*!< Detailed description after the member */
	CHRONONS_PASSED = 0;/*!< Detailed description after the member */
	FISH_BREED = 3;/*!< Detailed description after the member */
	// setup 
	//Time_Setup(&myTime);
	//Fish_Setup(&myFish);
	World_Setup(&world, 1500, 500);
	GameLoop();

	
	return (0);
	
	/** @endcode */
}

/**
 * @brief the game loop
 * @return nothing
 */
void GameLoop()
{	
	/** @code */
	int i;
	int j;

	while(finished == 0)
	{
//		for(j = 0; j < 8000000; j++){}
		World_Update(&world);
		World_Draw(&world);
	}
	
	/** @endcode */
}
