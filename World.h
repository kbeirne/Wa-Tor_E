/** @file World.h
 *  @brief Brief explanation of the World.h
 */

#ifndef WORLD_H
#define WORLD_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Globals.h"
#include "Creature.h"
#include <omp.h>


struct World
{
	struct Creature ** m_grid;
	int sharkCount;
	int fishCount;
};

// prototypes
void World_Setup(struct World * w, int numFish, int numShark);
void World_Destroy(struct World * w);
void World_Draw(struct World * w);
void World_Update(struct World * w);

void World_Setup(struct World * w, int numFish, int numShark)
{
	srand(time(NULL));

	w->sharkCount = 0;
	w->fishCount = 0;
	//Setup 2d array using malloc
	w->m_grid = (struct Creature**)malloc(GRID_WIDTH * sizeof(struct Creature*));
	
	//Allocate memory for grid
	int i;
	int j;
	//unsafe and/or stupid! (malloc)
	#pragma omp parallel for
	for (i = 0; i < GRID_WIDTH; i++)
		w->m_grid[i] = (struct Creature*)malloc(GRID_HEIGHT * sizeof(struct Creature));

	//initialize grid
	int a;
	int b;

	#pragma omp parallel for
	for(a = 0; a < GRID_WIDTH; a++)
	{
		#pragma omp parallel for
		for(b = 0; b < GRID_HEIGHT; b++)
		{
			Creature_Setup(&(w->m_grid[a][b]));
		}
	}
	
	
	//Place a number of fish = numFish at random points on map

	#pragma omp parallel for
	for(i = 0; i < numFish; i++)
	{
		int x = rand() % GRID_WIDTH;
		int y = rand() % GRID_HEIGHT;

		if(w->m_grid[x][y].m_alive == 0)
		{
			//Might cause slight inaccuracy in num fish, should always be very small error
			w->m_grid[x][y].m_alive = 1;
			w->m_grid[x][y].m_type = FISH;
		}
		else
		{
			i--;//redo this fish in a new random location
		}

	}

	//Place a number of shark = numShark at random points on map
	#pragma omp parallel for
	for(i = 0; i < numShark; i++)
	{
		int x = rand() % GRID_WIDTH;
		int y = rand() % GRID_HEIGHT;
		if(w->m_grid[x][y].m_alive == 0)
		{
			//Might cause slight inaccuracy in num sharks, should always be very small error
			w->m_grid[x][y].m_alive = 1;
			w->m_grid[x][y].m_type = SHARK;
		}
		else
		{
			i--;//redo this fish in a new random location
		}
	}
	
	#pragma omp parallel for
	for(i = 0; i < GRID_WIDTH; i++)
	{
		#pragma omp parallel for
		for(j = 0; j < GRID_HEIGHT; j++)
		{
			struct Position pos = { .m_x = i, .m_y = j };
			w->m_grid[i][j].m_pos = pos;
		}
	}
}

void World_Destroy(struct World * w)
{
	//deallocate grid
	int i;
	for (i = 0; i < GRID_WIDTH; i++)
		free(w->m_grid[i]);
	free(w->m_grid);
}


void World_Update(struct World * w)
{
	int i;
	int j;

	for(i = 0; i < GRID_WIDTH; i++)
	{
		for(j = 0; j < GRID_HEIGHT; j++)
		{
			if (w->m_grid[i][j].m_alive)
			{
				if(w->m_grid[i][j].m_chrononsPassed < CHRONONS_PASSED)
				{
					
					struct Position newPos = { .m_x = i, .m_y = j };
					Creature_Update(&w->m_grid[i][j], &w->m_grid, &newPos);
					w->m_grid[i][j].m_chrononsPassed++;
				}
			}
		}
	}

	
	#pragma omp parallel for// private fish and shark count for each thread
	for(i = 0; i < GRID_WIDTH; i++)
	{	
		for(j = 0; j < GRID_HEIGHT; j++)
		{
			if (w->m_grid[i][j].m_alive)
			{
				
				if(w->m_grid[i][j].m_type == FISH)
				{
					w->fishCount++;
				}
				else if(w->m_grid[i][j].m_type == SHARK)
				{
					w->sharkCount++;
				}
			}
		}
	}
	//add shark and fish counts from each thread here, assign to w->fishCount and w->sharkCount

	FILE *out;
	out = fopen( "SharksAndFish.txt", "a" );
 	fprintf( out,"%d,%d\n",w->fishCount, w->sharkCount);
	fclose(out);
	if(w->fishCount == 0 || w->sharkCount == 0)
	{
		finished = 1;
		printf("Game Over. Shark = %i, Fish = %i\n", w->sharkCount, w->fishCount);
		printf("Chronons Passed: %i", CHRONONS_PASSED);
	}
	w->fishCount = 0;//resiting each frame
	w->sharkCount = 0;//resiting each frame
	CHRONONS_PASSED++;
}

void World_Draw(struct World * w)
{
	int i;
	int j;
	printf("\n\n");
	
	for(j = 0; j < GRID_HEIGHT; j++)
	{
		//drawn in any order no good unless GUI
		for(i = 0; i < GRID_WIDTH; i++)
		{
			if(w->m_grid[i][j].m_alive)
			{
				if(w->m_grid[i][j].m_type == FISH)
				{
					printf("f");	
				}
				else if(w->m_grid[i][j].m_type == SHARK)
				{
					printf("s");
				}
			}
			else
				printf("~");
		}
		printf("\n");
	}
	printf("\n");
	printf("  ");
	
	//Doable but probably useless	
	//#pragma omp parallel for
	for(i = 2; i < (GRID_WIDTH - 2); i++)//Place a line between each map draw
		printf("_");
	printf("  ");
	printf("\n");
}

#endif
