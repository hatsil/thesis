#include <cstdlib>
#include <iostream>
#include <exception>

#include "interactionsHandler.hpp"

namespace thesis {
	extern InteractionsHandler* iHandler;
}

int main() {
	int ans = 0;
	try {
		thesis::iHandler = new thesis::InteractionsHandler(); //throws...
		thesis::iHandler->initCallbacks();
		
		while(thesis::iHandler->isActive())
			glfwPollEvents();
		
		delete thesis::iHandler;
	} catch(const std::exception& e) {
		std::cerr << "Exception thrown: " << e.what() << std::endl;
		ans = 1;
	}

	std::system("pause");
	return ans;
}

