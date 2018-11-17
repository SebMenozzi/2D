#include "clock.h"

#ifdef _WIN32
  #include <windows.h>
#else
  #include <time.h>
#endif

Clock::Clock()
{
  timeBeginning = this->getTicks();
}

void Clock::adjust(sint32 time)
{
  this->timeBeginning = this->getTicks() - time;
}

sint32 Clock::time(void)
{
  return this->getTicks() - this->timeBeginning;
}

sint32 Clock::getTicks(void)
{
  #ifdef _WIN32
    DWORD time;
  	time = timeGetTime(); // Linker : -lwinmm
  	return time;
  #else
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC, &tp);
    return (tp.tv_sec * 1000) + (tp.tv_nsec / 1000000);
  #endif
}
