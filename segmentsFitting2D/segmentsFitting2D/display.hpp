#pragma once

#include <exception>
#include <stdexcept>

#include <GLFW/glfw3.h>

namespace thesis {
	class InteractionsHandler;
	class Display {
		friend InteractionsHandler;
		GLFWwindow* window;
	
	public:
		Display(int width, int height, const char* title);
		virtual ~Display();

		void clear() const;
		void swapBuffers() const;
		void duplicateBuffer() const;
	};
}