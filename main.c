
#include <stdio.h>
#include "Time.h"
#include "Fish.h"

//prototypes
void GameLoop();

struct Time myTime;
struct Fish myFish;
int main()
{
	// setup 
	Time_Setup(&myTime);
	Fish_Setup(&myFish);

	printf("Start!!!\n");

	//GameLoop();

	
	return (0);
}

void GameLoop()
{	
	while(1 == 1)
	{
		Time_Update(&myTime);
		Time_Wait(&myTime, 1);
		Fish_Draw(&myFish);
	}
}
