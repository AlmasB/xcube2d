#ifndef __ENGINE_COMMON_H__
#define __ENGINE_COMMON_H__

#include <exception>
#include <memory>

#include <SDL2/SDL_timer.h>

#include "Debug.h"

#define _ENGINE_ERROR_NONE ""

#define safeDelete(ptr) if (ptr) delete ptr

class EngineException : public std::exception {
	private:
		std::string message;

	public:
		/**
		 * @param arg0, arg1 - exception details
		 */
		EngineException(std::string arg0, std::string arg1 = "") : message("EngineException: " + arg0 + " - " + arg1) {
			std::cout << "\t" << message << std::endl;
		}

		EngineException(const char * arg0, const char * arg1) : EngineException(std::string(arg0), std::string(arg1)) {}

		virtual const char* what() const throw() {
			return message.c_str();
		}
};

class Runnable {
	public:
		virtual void run() = 0;
};

class Task {
	private:
		Uint32 interval;
		bool started, cancelled, postCancel;
		void(*func)(void);
		SDL_TimerID timerID;
		std::shared_ptr<Runnable> runnable;

		static Uint32 run(Uint32 interval, void * param) {
			Task * task = static_cast<Task *>(param);

			//if (nullptr == task)
				//return 0;

			if (task->isCancelled()) {
				//task->postCancel = true;
				return 0;

			}

			if (nullptr != task->runnable) {
				task->runnable->run();
			}
			else {
				task->func();
			}
			return interval;
		}

	public:
		Task(const Uint32 & interval, void(*func)(void)) : func(func), started(false), 
			cancelled(false), interval(interval), postCancel(false) {}

		Task(const Uint32 & interval, std::shared_ptr<Runnable> runnable) : runnable(runnable), interval(interval),
			started(false), cancelled(false), postCancel(false) {}

		~Task() {
			#ifdef __DEBUG
					debug("Task::~() started");
			#endif
					runnable.reset();
					postCancel = true;

			#ifdef __DEBUG
					debug("Task::~() finished");
			#endif
		}

		/**
		* If the task hasn't been started yet, starts running it
		* on a separate thread
		*/
		void start() {
			if (!started) {
				timerID = SDL_AddTimer(interval, &Task::run, this);
				started = true;
			}
		}

		bool isCancelled() { return postCancel; }

		void cancel() {
			if (started) {
				cancelled = true;
				//while (!postCancel) SDL_Delay(1);
				SDL_RemoveTimer(timerID);
			}
		}
};

#endif