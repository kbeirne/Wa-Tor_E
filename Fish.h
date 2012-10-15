#ifndef FISH_H
#define FISH_H

#include <stdio.h>

struct Fish
{
	char * m_name;
	float m_posX;
	float m_posY;
};

// prototypes
void Fish_Setup(struct Fish * thisObj);
void Fish_Draw(struct Fish * thisObj);
void Fish_Update(struct Fish * thisObj);

void Fish_Setup(struct Fish * thisObj)
{
	thisObj->m_name = "Mr.Fish";
	thisObj->m_posX = 0;
	thisObj->m_posY = 0;
}

void Fish_Draw(struct Fish * thisObj)
{
	printf("%.7s\n", thisObj->m_name);
}

void Fish_Update(struct Fish * thisObj)
{
}

#endif
