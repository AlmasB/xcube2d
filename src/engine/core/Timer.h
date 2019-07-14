#ifndef __TIMER_H__
#define __TIMER_H__

#include <SDL.h>

static const int SECOND = 1000;
static const int MINUTE = 60 * SECOND;
static const int HOUR = 60 * MINUTE;

/**
 * Relative timer, used to tell how much time has passed
 * since certain event rather than the actual time
 */
class Timer {
	private:
		Uint32 time;
	public:
		Timer();
		void measure();
		void reset();
		Uint32 getTime();
		Uint32 getElapsed();
};

#endif