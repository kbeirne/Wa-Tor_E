#include <stdio.h>
#include "Globals.h"
#include "Time.h"
#include "World.h"
#include "Fish.h"

//prototypes
void GameLoop();

struct Time myTime;
struct Fish myFish;
struct World world;

int main()
{
	GRID_WIDTH = 75;
	GRID_HEIGHT = 20;
	// setup 
	Time_Setup(&myTime);
	Fish_Setup(&myFish);
	World_Setup(&world, 30);
	World_Draw(&world);
	
	//GameLoop();

	return (0);
}

void GameLoop()
{	
	while(1)
	{
		Time_Update(&myTime);
		Time_Wait(&myTime, 1);
		Fish_Draw(&myFish);
	}
}
