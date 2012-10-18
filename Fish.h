#ifndef FISH_H
#define FISH_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
//#include "World.h"

int Fish_Breed = 0;

typedef enum { WEST, EAST, SOUTH, NORTH } Direction;

struct Fish
{
	char * m_name;
	int m_alive;
	int m_timeAlive;
	float m_posX;
	float m_posY;
};

// prototypes
void Fish_Setup(struct Fish * f);
void Fish_Draw(struct Fish * f);
void Fish_Update(struct Fish * f);

void Fish_Setup(struct Fish * f)
{
	srand(time(NULL));
	f->m_name = "Mr.Fish";
	f->m_posX = 0;
	f->m_posY = 0;
	f->m_alive = 0;
	f->m_timeAlive = 0;
}

void Fish_Draw(struct Fish * f)
{
	printf("%.7s\n", f->m_name);
}

void Fish_Update(struct Fish * f)
{
	f->m_timeAlive++;
	Direction newLocation = rand() % 4;//0-3
	switch(newLocation)
	{
		case WEST:
		{
			if(f->m_posX < 0)
			{
				f->m_posX = (GRID_WIDTH - 1);
			}
			else
			{
				f->m_posX--;
			}
			break;
		}
		case EAST:
		{
			f->m_posX++;
			if(f->m_posX >= (GRID_WIDTH))
				f->m_posX = 0;
			break;
		}
		case NORTH:
		{
			if(f->m_posY < 0)
				f->m_posX = (GRID_HEIGHT - 1);
			else 
				f->m_posX--;
			break;
		}
		case SOUTH:
		{
			if(f->m_posY > GRID_HEIGHT)
			{
			}
			else
			{
				f->m_posX++;
			}
			break;
		}
	};
}

#endif
