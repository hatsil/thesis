/*
 * Window.cpp
 *
 *  Created on: 14 Sep 2018
 *      Author: hatsil
 */

#define GLEW_STATIC
#include <GL/glew.h>

#include "window.hpp"
#include "getColorOnPress.hpp"

namespace thesis {
static const int CANVAS_WIDTH = 800;
static const int CANVAS_HEIGHT = 800;
static const int BUTTON_SIZE = 70;
static const int WINDOW_WIDTH = CANVAS_WIDTH;
static const int WINDOW_HEIGHT = CANVAS_HEIGHT + BUTTON_SIZE + BUTTON_SIZE / 5;

static const char* WINDOW_TITLE = "2D Basic GUI";

static const uint BUTTONS_COLOR = 1U;
static const uint CANVAS_COLOR = 2U;

static GLFWwindow* makeWindow() {
	std::string what("Failed init window");
	bool needTermination = false;
	GLFWwindow* glfwWindow = nullptr;

	//Initialize the library:
	if (glfwInit()) {
		needTermination = true;
		if ((glfwWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, 0, 0))) {
			glfwMakeContextCurrent(glfwWindow);
			if (glewInit() != GLEW_OK) {
				what += ": Glew failed to initialize";
				goto bad;
			}
			glClearColor(1.f, 1.f, 1.f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);
			glfwSwapBuffers(glfwWindow);
			glClear(GL_COLOR_BUFFER_BIT);
			return glfwWindow;
		}
		what += ": Failed to create glfw window";
		goto bad;
	}

bad:
	if (glfwWindow)
		glfwDestroyWindow(glfwWindow);

	if (needTermination)
		glfwTerminate();

	throw std::runtime_error(what);
}

void keyCallback1(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods) {
	Window* window;
	if (!glfwWindowShouldClose(glfwWindow) &&
		(window = (Window*)glfwGetWindowUserPointer(glfwWindow))) {
		window->keyCallback(key, scancode, action, mods);
	}
	
	/*enum ReadingStatus {
		START, END
	};

	static ReadingStatus readNumberStatus = END;
	static int num = 0;
	if (!glfwWindowShouldClose(window) && action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;

		case GLFW_KEY_ENTER:
			iHandler->fitSegments();
			iHandler->draw();
			break;

		case GLFW_KEY_SPACE:
			iHandler->showNoisyVertices = true;
			iHandler->generateNoisyVertices();
			iHandler->draw();
			break;

		case GLFW_KEY_L:
			iHandler->showRealVertices = !iHandler->showRealVertices;
			iHandler->draw();
			break;

		case GLFW_KEY_F:
			iHandler->showEstimatedSegments = !iHandler->showEstimatedSegments;
			iHandler->draw();
			break;

		case GLFW_KEY_P:
			iHandler->showNoisyVertices = !iHandler->showNoisyVertices;
			iHandler->draw();
			break;

		case GLFW_KEY_LEFT_SHIFT:
			if (readNumberStatus == END) {
				readNumberStatus = START;
				num = 0;
			}
			else {
				readNumberStatus = END;
				iHandler->segments = num;
			}
			break;
		}

		if (readNumberStatus == START && key >= GLFW_KEY_0 && key <= GLFW_KEY_9)
			num = 10 * num + key - GLFW_KEY_0;
	}*/
}

void mouseCallback1(GLFWwindow* glfwWindow, int button, int action, int mods) {
	Window* window;
	if (!glfwWindowShouldClose(glfwWindow) &&
		(window = (Window*)glfwGetWindowUserPointer(glfwWindow))) {
		window->mouseCallback(button, action, mods);
	}
	//if (!glfwWindowShouldClose(window)) {
	//	switch (action) {
	//	case GLFW_RELEASE:
	//		iHandler->generateNoisyVertices();
	//		break;
	//
	//	case GLFW_PRESS:
	//		iHandler->realVertices.clear();
	//		iHandler->showRealVertices = true;
	//		iHandler->showNoisyVertices = false;
	//		iHandler->showEstimatedSegments = false;
	//		break;
	//	}
	//}
}

void cursorPositionCallback1(GLFWwindow* glfwWindow, double xpos, double ypos) {
	Window* window;
	if (!glfwWindowShouldClose(glfwWindow) &&
		(window = (Window*)glfwGetWindowUserPointer(glfwWindow))) {
		window->cursorPositionCallback(xpos, ypos);
	}
	//if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		//	iHandler->addVertex(xpos, ypos);
		//	iHandler->draw();
		//}
}

Window::Window():
	glfwWindow(makeWindow()),
	pressables(),
	selected(nullptr) {
	simpleShader = new SimpleShader;
	texShader = new TexShader;
	glfwSetWindowUserPointer(glfwWindow, this);
	pressables.insert((buttons = new ButtonsHolder(WINDOW_WIDTH, BUTTON_SIZE, BUTTONS_COLOR, *this)));
	pressables.insert((canvas = new Canvas(CANVAS_WIDTH, CANVAS_HEIGHT, CANVAS_COLOR, *this)));
}

Window::~Window() {
	glfwDestroyWindow(glfwWindow);
	glfwTerminate();

	delete buttons;
	delete canvas;

	delete simpleShader;
	delete texShader;

	//TODO: cleanup other stuff
}

void Window::keyCallback(int key, int scancode, int action, int mods) {
	switch (key) {
	case GLFW_KEY_ESCAPE:
		if(action == GLFW_PRESS)
			glfwSetWindowShouldClose(glfwWindow, GLFW_TRUE);
		break;

	case GLFW_KEY_LEFT_CONTROL:
		if(action == GLFW_PRESS)
			canvas->controlPress();
		else if(action == GLFW_RELEASE)
			canvas->controlRelease();
		break;
	}
}

void Window::mouseCallback(int button, int action, int mods) {
	if(action == GLFW_PRESS) {
		drawForPicking();
		select();
	} else if(action == GLFW_RELEASE)
		deselect();
}

void Window::cursorPositionCallback(double xpos, double ypos) {
	if(selected)
		selected->deliverPress(xpos, ypos);
}

void Window::drawForPicking() const {
	glClearColor(.0f, .0f, .0f, .0f);
	glClear(GL_COLOR_BUFFER_BIT);
	buttons->drawForPicking();
	canvas->drawForPicking();
}

void Window::select() {
	auto it = pressables.find(getColorOnPress(glfwWindow));
	if(it != pressables.cend())
		(selected = *it)->press();
	else selected = nullptr;
}

void Window::deselect() {
	if(selected) {
		selected->release();
		selected = nullptr;
	}
}

} /* namespace thesis */
