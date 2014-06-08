#include "Debug.h"

std::stack<std::string> ErrorStack::errorData;

void ErrorStack::push(const std::string & errorMessage) {
	errorData.push(errorMessage);
}

void ErrorStack::dump() {
	std::cout << "ERROR STACK: " << std::endl;
	while (!errorData.empty()) {
		std::cout << "\t" << errorData.top() << std::endl;
		errorData.pop();
	}
}