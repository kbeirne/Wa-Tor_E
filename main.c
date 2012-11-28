/** @file main.c
 *  @brief Brief explanation of the main.c
 */

#include <stdio.h>
#include <time.h>
#include "Globals.h"
//#include "Time.h"
#include "World.h"
#include "Creature.h"

//prototypes
void GameLoop();/*!< Detailed description after the member function*/

//struct Time myTime;/*!< Detailed description after the member */
struct World world;/*!< Detailed description after the member */


/**
 * @brief this main function
 * @return 0 for program kill
 */
 int threads = 16;
int main()
{
	
	/** @code */
	omp_set_num_threads(threads);
	finished = 0;
	GRID_WIDTH = 500;/*!< Detailed description after the member */
	GRID_HEIGHT = 500;/*!< Detailed description after the member */
	CHRONONS_PASSED = 0;/*!< Detailed description after the member */
	FISH_BREED = 3;/*!< Detailed description after the member */
	// setup 
	//Time_Setup(&myTime);
	//Fish_Setup(&myFish);
	World_Setup(&world, 4500, 500);
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

struct timeval tvbegin;
gettimeofday(&tvbegin, NULL);
	for(i = 0; i < 10000; i++)
	{
		World_Update(&world);
		//World_Draw(&world);
	}

	struct timeval tvend;
	gettimeofday(&tvend, NULL);
	int secs;
	int usecs;

	FILE *out;
	out = fopen( "GridThreads.txt", "a" );


	if(tvend.tv_usec - tvbegin.tv_usec < 0)
	{
		secs = tvend.tv_sec - tvbegin.tv_sec;
		usecs = 1000000 + (tvend.tv_usec - tvbegin.tv_usec);
		//printf("Current time is %i.%i", secs, usecs);
	 	fprintf(out, "Time: %i.%i, Threads: %i (at 1000 frames, 500x500 grid)\n", secs, usecs, threads);
	}
	else
	{
	 	fprintf(out, "Time: %i.%i, Threads: %i (at 1000 frames, 500x500 grid)\n", (int)(tvend.tv_sec - tvbegin.tv_sec), (int)(tvend.tv_usec - tvbegin.tv_usec), threads);
	}
    	
	fclose(out);
	/** @endcode */
}
