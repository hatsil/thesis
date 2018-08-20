#include "interactionsHandler.hpp"

namespace thesis {
	const int DISPLAY_WIDTH = 800;
	const int DISPLAY_HEIGHT = 800;
}		

thesis::InteractionsHandler::InteractionsHandler():
	display(0),
	width(DISPLAY_WIDTH),
	height(DISPLAY_HEIGHT),
	keyCallback(),
	mouseCallback(),
	framebufferSizeCallback(),
	realVertices(),
	cloud(),
	estimatedVertices(),
	showRealTriangle(true),
	showClould(false),
	showEstimatedTrinagle(false) {
	//init display: might throw exception
	display = new Display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "2D Triangle fitting");
	initCallbacks();
	setCallbacks();
}

thesis::InteractionsHandler::~InteractionsHandler() {
	delete display;
}

void thesis::InteractionsHandler::initCallbacks() {
	keyCallback = [&](GLFWwindow* window, int key, int scancode, int action, int mods) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			if(action == GLFW_PRESS)
				glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;

		case GLFW_KEY_ENTER:
			if(action = GLFW_PRESS) {
				//TODO: raster points.
			}

		case GLFW_KEY_SPACE:
			if (action == GLFW_PRESS)
				//TODO: show\unshow triangle.
				break;

		case GLFW_KEY_LEFT_SHIFT:
			if (action == GLFW_PRESS)
				//TODO: show\unshow triangle.
				break;
		}
	};
	
	mouseCallback = [&](GLFWwindow* window, int button, int action, int mods) {
		if (action == GLFW_PRESS) {
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			//TODO: set point;
		}
	};

	framebufferSizeCallback = [&](GLFWwindow* window, int width, int height) {
		//TODO: resize window
		this->width = width;
		this->height = height;
	};
}

void thesis::InteractionsHandler::setCallbacks() {
	glfwSetKeyCallback(display->window, keyCallback.target<void(GLFWwindow*, int, int, int, int)>());
	glfwSetMouseButtonCallback(display->window, mouseCallback.target<void(GLFWwindow*, int, int, int)>());
	glfwSetFramebufferSizeCallback(display->window, framebufferSizeCallback.target<void(GLFWwindow*, int, int)>());
}

void thesis::InteractionsHandler::drawAll() const {
	display->clear();

	if(showClould)
		drawCloud();

	if(showRealTriangle)
		drawRealTriangle();

	if(showEstimatedTrinagle)
		drawEstimatedTriangle();

	display->swapBuffers();
}