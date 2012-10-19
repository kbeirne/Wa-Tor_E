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
	CHRONONS_PASSED = 0;
	// setup 
	Time_Setup(&myTime);
	Fish_Setup(&myFish);
	World_Setup(&world, 1);
	GameLoop();

	return (0);
}

void GameLoop()
{	
	printf("start loop");
	int i;
	for(i = 0; i < 50; i++)
	{
/*
		Time_Update(&myTime);
		Time_Wait(&myTime, 1);
		Fish_Draw(&myFish);*/
		World_Update(&world);
		World_Draw(&world);
	}
}
