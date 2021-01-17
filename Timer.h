#ifndef __TIMER_H__
#define __TIMER_H__

#include "Globals.h"
#include "SDL\include\SDL.h"

class Timer
{
public:

	// Constructor
	Timer()
	{
		Start();
	}

	void Start()
	{
		startTime = SDL_GetTicks();
	}

	Uint32 Read() const
	{
		return SDL_GetTicks() - startTime;
	}

	float ReadSec() const
	{
		return float(SDL_GetTicks() - startTime) / 1000.0f;
	}

private:

	Uint32 startTime;
};

#endif //__TIMER_H__