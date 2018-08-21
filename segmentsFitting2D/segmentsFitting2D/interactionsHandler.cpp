#include <iostream>
#include <cmath>

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
	static const double NOISE_RADIUS = .1;
	static const double pi = std::acos(-1.);

	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			if (action == GLFW_PRESS)
				glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;

		case GLFW_KEY_ENTER:
			if (action = GLFW_PRESS) {
				iHandler->showClould = true;
				iHandler->generateNewPointsCloud();
				iHandler->draw();
			}
			break;

		case GLFW_KEY_SPACE:
			if (action == GLFW_PRESS) {
				iHandler->showClould = !iHandler->showClould;
				iHandler->draw();
			}
			break;

		case GLFW_KEY_LEFT_SHIFT:
			if (action == GLFW_PRESS) {
				iHandler->showEstimatedTrinagle = !iHandler->showEstimatedTrinagle;
				iHandler->draw();
			}
			break;

		case GLFW_KEY_RIGHT_SHIFT:
			if (action == GLFW_PRESS) {
				iHandler->showRealTriangle = !iHandler->showRealTriangle;
				iHandler->draw();
			}
			break;
		}
	}

	void mouseCallback(GLFWwindow* window, int button, int action, int mods) {
		if(action == GLFW_PRESS) {
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			iHandler->addVertex(xpos, ypos);
		}
	}

	void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
		iHandler->width = width;
		iHandler->height = height;
		glViewport(0, 0, width, height);
		iHandler->draw();
	}
}		

thesis::InteractionsHandler::InteractionsHandler():
	display(0),
	width(DISPLAY_WIDTH),
	height(DISPLAY_HEIGHT),
	realVertices(),
	cloud(),
	estimatedVertices(),
	showRealTriangle(true),
	showClould(false),
	showEstimatedTrinagle(false) {
	//init display: might throw exception
	display = new Display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "2D Triangle fitting");
}

thesis::InteractionsHandler::~InteractionsHandler() {
	delete display;
}

void thesis::InteractionsHandler::initCallbacks() const {
	glfwSetKeyCallback(display->window, keyCallback);
	glfwSetMouseButtonCallback(display->window, mouseCallback);
	glfwSetFramebufferSizeCallback(display->window, framebufferSizeCallback);
}

void thesis::InteractionsHandler::draw() const {
	display->clear();

	if(showClould)
		drawCloud();

	if(showRealTriangle)
		drawRealTriangle();

	if(showEstimatedTrinagle)
		drawEstimatedTriangle();

	display->swapBuffers();
}

void thesis::InteractionsHandler::drawRealTriangle() const {
	//TODO: implement
}

void thesis::InteractionsHandler::drawCloud() const {
	//TODO: implement
}

void thesis::InteractionsHandler::drawEstimatedTriangle() const {
	//TODO: implement
}

void thesis::InteractionsHandler::showResult() const {
	//TODO: implement
}

void thesis::InteractionsHandler::generateNewPointsCloud() {
	if(realVertices.size() != 3U) {
		std::cout << "need three corners to generate points cloud" << std::endl;
		return;
	}

	cloud.clear();

	for(int i = 0; i < MAX_POINTS; ++i) {
		glm::dvec3 barCoords(random(), random(), random());
		//normalize:
		barCoords /= (barCoords.x + barCoords.y + barCoords.z);

		//create point:
		glm::dvec2 point(0);
		for(int i = 0; i < 3; ++i)
			point += barCoords[i] * realVertices[i];

		//generate noisy translation:
		double radius = NOISE_RADIUS * random();
		double angle = 2 * pi * random();
		glm::dvec2 noisyTrans = radius * glm::dvec2(std::cos(angle), std::sin(angle));

		//add noise to generated point:
		point += noisyTrans;

		//add the point to the cloud:
		cloud.push_back(point);
	}
}

void thesis::InteractionsHandler::addVertex(const double& xpos, const double& ypos) {
	std::cout << xpos << "   " << ypos << std::endl;
}