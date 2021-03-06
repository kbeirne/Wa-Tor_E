#ifndef FISH_H
#define FISH_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int Fish_Breed = 0;

typedef enum { WEST, EAST, SOUTH, NORTH } Direction;
typedef enum { SHARK, FISH } Species;



struct Position
{
	int m_x;
	int m_y;
};

struct Fish
{
	char * m_name;
	int m_alive;
	int m_timeAlive;
	int m_timesMoved;
	Species m_type;
	struct Position m_pos;
};

// prototypes
void Fish_Setup(struct Fish * f);
void Fish_Draw(struct Fish * f);
void Fish_Update(struct Fish * f, struct Position * posToUpdate);

void Fish_Setup(struct Fish * f)
{
	srand(time(NULL));
	f->m_name = "Mr.Fish";
	/*f->m_posX = 0;
	f->m_posY = 0;*/
	f->m_alive = 0;
	f->m_timeAlive = 0;
	f->m_timesMoved = 0;
	f->m_type = FISH;
}

void Fish_Draw(struct Fish * f)
{
	printf("%.7s\n", f->m_name);
}

void Fish_Update(struct Fish * f, struct Position * posToUpdate)
{
	f->m_timeAlive++;
	Direction newLocation = rand() % 4;//0-3

	switch(newLocation)
	{
		case WEST:
		{
			if(posToUpdate->m_x < 0)
			{
				posToUpdate->m_x = (GRID_WIDTH - 1);
			}
			else
			{
				posToUpdate->m_x--;
			}
			break;
		}
		case EAST:
		{
			posToUpdate->m_x++;
			if(posToUpdate->m_x >= (GRID_WIDTH))
				posToUpdate->m_x = 0;
			break;
		}
		case NORTH:
		{
			if(posToUpdate->m_y < 0)
				posToUpdate->m_y = (GRID_HEIGHT - 1);
			else 
				posToUpdate->m_y--;
			break;
		}
		case SOUTH:
		{
			if(posToUpdate->m_y > GRID_HEIGHT)
			{
				posToUpdate->m_y = 0;
			}
			else
			{
				posToUpdate->m_y++;
			}
			break;
		}
	};
}

#endif
