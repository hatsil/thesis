//#include <iostream>
//#include <exception>
//
//#include <cstdlib>
//
//#include "interactionsHandler.hpp"
//
//#include "executor.hpp"
//
//namespace thesis {
//	extern InteractionsHandler* iHandler;
//}
//
//int main() {
//	int ans = 0;
//	
//	try {
//		thesis::iHandler = new thesis::InteractionsHandler(); //throws...
//		thesis::iHandler->initCallbacks();
//		
//		while(thesis::iHandler->isActive())
//			glfwPollEvents();
//		
//		delete thesis::iHandler;
//	} catch(const std::exception& e) {
//		std::cerr << "Exception thrown: " << e.what() << std::endl;
//		ans = 1;
//	}
//
//	return ans;
//}

#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>
#include <exception>

#include <cstdlib>

#include "window.hpp"

int main() {
	int ans = 0;

	try {
		thesis::Window* window = new thesis::Window; //throws...

		while(window->isActive())
			glfwWaitEvents();

		delete window;
	} catch(const std::exception& e) {
		std::cerr << "Exception thrown: " << e.what() << std::endl;
		ans = 1;
	}

	return ans;
}

