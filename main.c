#include <stdio.h>
#include "Globals.h"
#include "Time.h"
#include "World.h"
#include "Creature.h"

//prototypes
void GameLoop();

struct Time myTime;
struct World world;

int main()
{
	GRID_WIDTH = 75;
	GRID_HEIGHT = 35;
	CHRONONS_PASSED = 0;
	FISH_BREED = 3;
	// setup 
	//Time_Setup(&myTime);
	//Fish_Setup(&myFish);
	World_Setup(&world, 5, 5);
	GameLoop();

	return (0);
}

void GameLoop()
{	
	int i;
	int j;
	for(i = 0; i < 2500; i++)
	{
		for(j = 0; j < 20000000; j++){}
		World_Update(&world);
		World_Draw(&world);
	}
}
