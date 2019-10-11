#include "Timer.h"

Timer::Timer() : time(0) {}

void Timer::measure() {
	time = SDL_GetTicks();
}

void Timer::reset() {
	time = 0;
}

Uint32 Timer::getTime() {
	return time;
}

Uint32 Timer::getElapsed() {
	return SDL_GetTicks() - time;
}