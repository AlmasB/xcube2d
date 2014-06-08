#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <iostream>
#include <stack>
#include <string>

/**
	If enabled, most of the classes/structs will have
	a printDebug() function, which prints debug info to std out
	Also debug info will be shown at crucial stages

	Uncomment the following to remove debug code from release build
*/
#define __DEBUG

inline void debug(const char * msg, const char * details = "") {
	std::cout << "DEBUG: " << msg << " " << details << std::endl;
}

inline void debug(const char * msg, int value) {
	std::cout << "DEBUG: " << msg << " " << value << std::endl;
}

class ErrorStack {
	private:
		static std::stack<std::string> errorData;
	public:
		static void push(const std::string & errorMessage);
		static void dump();
};

#endif