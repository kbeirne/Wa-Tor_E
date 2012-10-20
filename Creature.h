#ifndef Creature_H
#define Creature_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int BreedCount = 3;//NOTE: more than 1 doesn't work ???

typedef enum { NORTH, EAST, SOUTH, WEST } Direction;
typedef enum { FISH, SHARK } Species;

struct Position
{
	int m_x;
	int m_y;
};

struct Creature
{
	int m_alive;
	int m_timeAlive;
	int m_timesMoved;
	Species m_type;
	struct Position m_pos;
};

// prototypes
void Creature_Setup(struct Creature * c);
void Creature_Update(struct Creature * c, struct Creature *** grid, struct Position * posToUpdate);
void Creature_Copy(struct Creature * c, struct Creature *** grid, struct Position * newPos);
void Fish_Make_Move(struct Creature * c, struct Creature *** grid, struct Position * newPos);

void Creature_Setup(struct Creature * c)
{
	srand(time(NULL));
	c->m_alive = 0;
	c->m_timeAlive = 0;
	c->m_timesMoved = 0;
	c->m_type = FISH;
}

//Don't need to pass in c if you have grid and posToUpdate but more efficient then constantly dereferencing posToUpdate on grid
void Creature_Update(struct Creature * c, struct Creature *** grid, struct Position * posToUpdate)
{
	c->m_timeAlive++;
	Direction startLocation = rand() % 4;//0-3

	if(startLocation == EAST) goto east;
	else if(startLocation == SOUTH) goto south;
	else if(startLocation == NORTH) goto north;

	west:
	{
		posToUpdate->m_x--;
		if(posToUpdate->m_x < 0)
			posToUpdate->m_x = (GRID_WIDTH - 1);

		//NOTE FOR DECLAN: I ONLY CHECK IF THE SPACE HAS SOMETHING ON IT BEFORE IGNORING IT
		//YOU WILL HAVE TO ALSO CHECK IF THE TYPE AT THIS LOCATION IS A FISH, IS ALIVE AND IF YOU'RE A SHARK
		//TO CHECK FOR A SHARK MOVE CORRECTLY - HOPE THIS MAKES SENSE TO YOU
		if((*grid)[posToUpdate->m_x][posToUpdate->m_y].m_alive)//If this space is free (nothing alive)
		//then exit loop and move using this number
		{
			if(startLocation == EAST)//Are we going back to where we started (round in circles)? 
			{
				//if so then set next pos to null (don't move) and skip to end
				posToUpdate = NULL;
				goto end;
			}
		}
		else//space is free so use our current posToUpdate and skip to the end
		{
			goto end;
		}
			
	}
	east://same as west: comments
	{
		posToUpdate->m_x++;
		if(posToUpdate->m_x >= (GRID_WIDTH))
			posToUpdate->m_x = 0;
		if((*grid)[posToUpdate->m_x][posToUpdate->m_y].m_alive)
		{
			if(startLocation == NORTH)
			{
				posToUpdate = NULL;
				goto end;
			}
		}
		else
		{
			goto end;
		}
	}
	north://same as west: comments
	{
		posToUpdate->m_y--;
		if(posToUpdate->m_y < 0)
			posToUpdate->m_y = (GRID_HEIGHT - 1);
		if(!(*grid)[posToUpdate->m_x][posToUpdate->m_y].m_alive)
		{			
			if(startLocation == SOUTH)
			{
				posToUpdate = NULL;
				goto end;
			}
			
		}
		else
		{
			goto end;						
		}
	}
	south://same as west: comments but don't need to goto end as we will naturally reach the end unless we goto west
	{
		posToUpdate->m_y++;
		if(posToUpdate->m_y >= GRID_HEIGHT)
			posToUpdate->m_y = 0;

		if((*grid)[posToUpdate->m_x][posToUpdate->m_y].m_alive)
		{	
			if(startLocation == WEST)
				posToUpdate = NULL;
			else
				goto west;
		}
	}
	

	end:
		if(c->m_type== FISH)
			Fish_Make_Move(c, grid, posToUpdate);
		//else
			//Shark Move
}

//NOTE: Make_Move encompasses all fish actions (moving and breeding) not just moving, Shark_Make_Move should be the same
//NOTE: Uncomment printf commands to see fish decision making process in-game
void Fish_Make_Move(struct Creature * c, struct Creature *** grid, struct Position * newPos)
{
	//printf("\nFish at %i, %i\n", c->m_pos.m_x, c->m_pos.m_y);
	//printf("Time Alive: %i\n", c->m_timeAlive);
	//if(c->m_timeAlive % BreedCount == 0)//If ready to breed
	//	printf("Time Alive(%i) mod BreedCount(%i) = 0 Therefore Wants to Breed - ", c->m_timeAlive, BreedCount);

	if(newPos != NULL)
	{	
		Creature_Copy(c, grid, newPos);//Copy to new location
		if((c->m_timeAlive % BreedCount) == 0)//If bred then set times moved to 0, don't want to copy old life span
		{
			(*grid)[newPos->m_x][newPos->m_y].m_timesMoved = 0;
			//printf("Breeding");
		}
		else //otherwise kill old fish (i.e move him)
		{
			(*grid)[c->m_pos.m_x][c->m_pos.m_y].m_alive = 0;
			c->m_pos = (*newPos);
			//printf("Moving - Doesn't want to breed");
		}
	}
	else if(c->m_timeAlive % BreedCount == 0)//If ready to breed
	{
		c->m_timesMoved--;//Set this back so that it will breed next turn if there's a free space
		//printf("Not Moving - Can't breed");
	}
	//else printf("Not Moving - Doesn't want to breed");
	//printf("\n");
}

void Creature_Copy(struct Creature * c, struct Creature *** grid, struct Position * newPos)
{
	(*grid)[newPos->m_x][newPos->m_y].m_alive = 1;
	(*grid)[newPos->m_x][newPos->m_y].m_timeAlive = (*grid)[c->m_pos.m_x][c->m_pos.m_y].m_timeAlive;

	(*grid)[newPos->m_x][newPos->m_y].m_type = (*grid)[c->m_pos.m_x][c->m_pos.m_y].m_type;

	(*grid)[newPos->m_x][newPos->m_y].m_pos = *newPos;
	
	//Set him to one behind CHRONON count 
	//i.e ready to move again
	(*grid)[newPos->m_x][newPos->m_y].m_timesMoved = CHRONONS_PASSED;
}

#endif
