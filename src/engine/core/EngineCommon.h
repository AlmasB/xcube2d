#ifndef __ENGINE_COMMON_H__
#define __ENGINE_COMMON_H__

#include <exception>

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

#endif