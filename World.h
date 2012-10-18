#ifndef WORLD_H
#define WORLD_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Globals.h"
#include "Fish.h"

struct World
{
	int m_width;
	int m_height;
	struct Fish ** m_grid;
};

// prototypes
void World_Setup(struct World * w, int numFish);
void World_Destroy(struct World * w);
void World_Draw(struct World * w);
void World_Update(struct World * w);

void World_Setup(struct World * w, int numFish)
{
	srand(time(NULL));
	w->m_width = GRID_WIDTH;
	w->m_height = GRID_HEIGHT;

	//Setup 2d array using malloc
	w->m_grid = (struct Fish**)malloc(w->m_width * sizeof(struct Fish*));
	
	//Allocate memory for grid
	int i;
	for (i = 0; i < w->m_width; i++)
		w->m_grid[i] = (struct Fish*)malloc(w->m_height * sizeof(struct Fish));
	
	//Place a number of fish = numFish at random points on map
	for(i = 0; i < numFish; i++)
	{
		int x = rand() % w->m_width;
		int y = rand() % w->m_height;
		if(w->m_grid[x][y].m_alive == 0)
			w->m_grid[x][y].m_alive = 1;
		else
			i--;//redo this fish in a new random location
	}
}

void World_Destroy(struct World * w)
{
	//deallocate grid
	int i;
	for (i = 0; i < w->m_width; i++)
	  free(w->m_grid[i]);
	free(w->m_grid);
}

void World_Draw(struct World * w)
{
	int j;
	for(j = 0; j < w->m_height; j++)
	{
		int i;
		for(i = 0; i < w->m_width; i++)
		{
			if(w->m_grid[i][j].m_alive)
				printf("f");
			else
				printf("0");
		}
		printf("\n");
	}
}

void World_Update(struct World * w)
{
}

#endif
