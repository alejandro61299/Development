// ----------------------------------------------------
// j1PerfTimer.cpp
// Slow timer with microsecond precision
// ----------------------------------------------------

#include "j1PerfTimer.h"
#include "SDL\include\SDL_timer.h"

uint64 j1PerfTimer::frequency = 0;

// ---------------------------------------------
j1PerfTimer::j1PerfTimer()
{
	// TODO 2: Fill Constructor, Start(),ReadMs() and ReadTicks() methods
	// they are simple, one line each!

	Start();
}

// ---------------------------------------------
void j1PerfTimer::Start()
{
	frequency = SDL_GetPerformanceCounter();
	started_at = SDL_GetPerformanceCounter() / SDL_GetPerformanceFrequency();
}

// ---------------------------------------------
double j1PerfTimer::ReadMs() const
{
	return (double)(SDL_GetPerformanceCounter() / SDL_GetPerformanceFrequency());
}

// ---------------------------------------------
uint64 j1PerfTimer::ReadTicks() const
{
	return SDL_GetPerformanceCounter() / SDL_GetPerformanceFrequency() - started_at;
}


