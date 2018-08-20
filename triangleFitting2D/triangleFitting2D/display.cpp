#define GLEW_STATIC
#include <GL/glew.h>

#include "display.hpp"

thesis::Display::Display(int width, int height, const char* title) :
	window(0) {
	std::string what("Failed init dispaly");
	bool needTermination = false;
	
	//Initialize the library:
	if(glfwInit()) {
		needTermination = true;
		if ((window = glfwCreateWindow(width, height, title, 0, 0))) {
			glfwMakeContextCurrent(window);
			if (glewInit() != GLEW_OK) {
				what += ": Glew failed to initialize";
				goto bad;
			}
			glClearColor(1.f, 1.f, 1.f, 1.f);
			clear();
			swapBuffers();
			clear();
			return;
		}
		what += ": Failed to create window";
		goto bad;
	}

bad:
	if(window)
		glfwDestroyWindow(window);

	if(needTermination)
		glfwTerminate();

	throw std::runtime_error(what);

	//glEnable(GL_DEPTH_TEST);
	// During init, enable debug output
	//glEnable(GL_SMOOTH);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT_AND_BACK);
}

thesis::Display::~Display() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

void thesis::Display::clear() const {
	glClear(GL_COLOR_BUFFER_BIT);
}

void thesis::Display::swapBuffers() const {
	glfwSwapBuffers(window);
}

void thesis::Display::duplicateBuffer() const {
	//glfwBuffer
}
