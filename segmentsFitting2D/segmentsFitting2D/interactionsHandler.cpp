#include <iostream>
#include <cmath>
#include <algorithm>

#include "random.hpp"

#include "interactionsHandler.hpp"

namespace thesis {
	extern InteractionsHandler* iHandler;
}

thesis::InteractionsHandler* thesis::iHandler = 0;

namespace thesis {
	static const int DISPLAY_WIDTH = 800;
	static const int DISPLAY_HEIGHT = 800;
	static const int MAX_POINTS = 2000;
	static const double NOISE_RADIUS = .02;
	static const double pi = std::acos(-1.);

	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		enum ReadingStatus {
			START, END
		};

		static ReadingStatus readNumberStatus = END;
		static int num = 0;
		if(!glfwWindowShouldClose(window) && action == GLFW_PRESS) {
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
				if(readNumberStatus == END) {
					readNumberStatus = START;
					num = 0;
				} else {
					readNumberStatus = END;
					iHandler->segments = num;
				}
				break;
			}

			if(readNumberStatus == START && key >= GLFW_KEY_0 && key <= GLFW_KEY_9)
				num = 10 * num + key - GLFW_KEY_0;
		}
	}

	void mouseCallback(GLFWwindow* window, int button, int action, int mods) {
		if(!glfwWindowShouldClose(window)) {
			switch(action) {
			case GLFW_RELEASE:
				iHandler->generateNoisyVertices();
				break;

			case GLFW_PRESS:
				iHandler->realVertices.clear();
				iHandler->showRealVertices = true;
				iHandler->showNoisyVertices = false;
				iHandler->showEstimatedSegments = false;
				break;
			}
		}
	}

	void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
		if(!glfwWindowShouldClose(window)) {
			if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
				iHandler->addVertex(xpos, ypos);
				iHandler->draw();
			}
		}
	}

	void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
		if(!glfwWindowShouldClose(window)) {
			iHandler->width = width;
			iHandler->height = height;
			glViewport(0, 0, width, height);
			iHandler->draw();
		}
	}
}		

thesis::InteractionsHandler::InteractionsHandler():
	display(0),
	width(DISPLAY_WIDTH),
	height(DISPLAY_HEIGHT),
	segments(2),
	realVertices(),
	noisyVertices(),
	estimatedVertices(),
	showRealVertices(true),
	showNoisyVertices(false),
	showEstimatedSegments(false) {
	//init display: might throw exception
	display = new Display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "2D Triangle fitting");
}

thesis::InteractionsHandler::~InteractionsHandler() {
	delete display;
}

void thesis::InteractionsHandler::initCallbacks() const {
	glfwSetKeyCallback(display->window, keyCallback);
	glfwSetMouseButtonCallback(display->window, mouseCallback);
	glfwSetCursorPosCallback(display->window, cursorPositionCallback);
	glfwSetFramebufferSizeCallback(display->window, framebufferSizeCallback);
}

void thesis::InteractionsHandler::draw() const {
	display->clear();

	if(showNoisyVertices)
		drawNoisyVertices();

	if(showRealVertices)
		drawRealVertices();

	if(showEstimatedSegments)
		drawEstimatedSegments();

	display->swapBuffers();
}

void thesis::InteractionsHandler::drawNoisyVertices() const {
	glColor3d(.5, .5, .5);
	glBegin(GL_POINTS);
	for(const glm::dvec2& v : noisyVertices)
		glVertex2d(v.x, v.y);
	glEnd();
}

void thesis::InteractionsHandler::drawRealVertices() const {
	glColor3d(1, 0, 0);
	glBegin(GL_LINE_STRIP);
	for (const glm::dvec2& v : realVertices)
		glVertex2d(v.x, v.y);
	glEnd();
}

void thesis::InteractionsHandler::drawEstimatedSegments() const {
	glColor3d(0, 1, 0);
	glBegin(GL_LINE_STRIP);
	for (const glm::dvec2& v : estimatedVertices)
		glVertex2d(v.x, v.y);
	glEnd();
}

void thesis::InteractionsHandler::generateNoisyVertices() {
	if(realVertices.size() == 0U) {
		std::cout << "Please draw line first." << std::endl;
		return;
	}

	noisyVertices.clear();

	for(int i = 0; i < MAX_POINTS; ++i) {
		//generate noisy translation:
		double radius = NOISE_RADIUS * random();
		double angle = 2 * pi * random();
		glm::dvec2 noisyTrans = radius * glm::dvec2(std::cos(angle), std::sin(angle));

		//add the point to the cloud:
		noisyVertices.push_back(realVertices[getRandomIndex()] + noisyTrans);
	}

	//shuffles the noisy points:
	std::shuffle(noisyVertices.begin(), noisyVertices.end(), URBG());
}

void thesis::InteractionsHandler::addVertex(const double& xpos, const double& ypos) {
	double x = (2 * xpos - width) / width;
	double y = (height - 2 * ypos) / height;
	realVertices.emplace_back(x, y);
}

void thesis::InteractionsHandler::fitSegments() {
	//TODO: implement
}

uint thesis::InteractionsHandler::getRandomIndex() {
	uint size = realVertices.size();
	uint index = (uint)(size * random());
	
	if(index >= size && size > 0)
		index = size - 1U;

	return index;
}