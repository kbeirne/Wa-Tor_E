#ifndef TIME_H
#define TIME_H

#include <time.h>

struct Time
{
	long m_timeElapsed;
	float m_timeLastFrame;
	float m_timeSinceLastFrame;
};

// prototypes
void Time_Setup(struct Time * thisObj);
void Time_Update(struct Time * thisObj);
void Time_Wait(struct Time * thisObj, double waitTime);
float Time_GetTimeSinceLastFrame(struct Time * thisObj);
float Time_GetTimeElapsed(struct Time * thisObj);

void Time_Setup(struct Time * thisObj)
{
	thisObj->m_timeLastFrame = Time_GetTimeElapsed(thisObj);
}

void Time_Update(struct Time * thisObj)
{
	thisObj->m_timeSinceLastFrame = Time_GetTimeElapsed(thisObj) - thisObj->m_timeLastFrame;
	thisObj->m_timeLastFrame = Time_GetTimeElapsed(thisObj);
}

void Time_Wait(struct Time * thisObj, double waitTime)
{	
	//float var = 0;
	//while(var < waitTime)
	//{
	//	Time_Update(thisObj);
	//	var += thisObj->m_timeSinceLastFrame;
	//}
}

// Get Time since the last frame
float Time_GetTimeSinceLastFrame(struct Time * thisObj)
{  
	return(thisObj->m_timeSinceLastFrame);
}

float Time_GetTimeElapsed(struct Time * thisObj)
{
  	float t = clock();
	float secondsSinceStart = ((float)t)/CLOCKS_PER_SEC;
  
	return(secondsSinceStart);
}

#endif
