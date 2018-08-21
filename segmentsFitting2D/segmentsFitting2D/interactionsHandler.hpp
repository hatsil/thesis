#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "display.hpp"

//glfwSetKeyCallback(display->m_window, key_callback);
//glfwSetWindowSizeCallback(display->m_window, window_size_callback);
//#include <iostream>
//
//#include <thread>
//
//#include "display.h"
//#include "GLFW\glfw3.h"
//#include "Scene.hpp"
//
//static tsahi::Scene* simulatedScene = NULL;
//
//void key_callback1(GLFWwindow* window, int key, int scancode, int action, int mods);
//void mouse_callback(GLFWwindow* window, int button, int action, int mods);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void cursor_position_callback1(GLFWwindow* window, double xpos, double ypos);
//
//void tsahi::Scene::beginSimulation() {
//	simulatedScene = this;
//
//	//set callback functions:
//	glfwSetKeyCallback(display->m_window, key_callback1);
//	glfwSetMouseButtonCallback(display->m_window, mouse_callback);
//	glfwSetScrollCallback(display->m_window, scroll_callback);
//	glfwSetCursorPosCallback(display->m_window, cursor_position_callback1);
//
//	draw();
//
//	simulatedScene = NULL;
//}
//
//void key_callback1(GLFWwindow* window, int key, int scancode, int action, int mods) {
//	switch (key) {
//	case GLFW_KEY_ESCAPE:
//		if (action == GLFW_PRESS)
//			glfwSetWindowShouldClose(window, GLFW_TRUE);
//		break;
//
//	case GLFW_KEY_RIGHT:
//		if (action == GLFW_PRESS || action == GLFW_REPEAT)
//			simulatedScene->rotateY(5);
//		break;
//
//	case GLFW_KEY_LEFT:
//		if (action == GLFW_PRESS || action == GLFW_REPEAT)
//			simulatedScene->rotateY(-5);
//		break;
//
//	case GLFW_KEY_DOWN:
//		if (action == GLFW_PRESS || action == GLFW_REPEAT)
//			simulatedScene->rotateX(-5);
//		break;
//
//	case GLFW_KEY_UP:
//		if (action == GLFW_PRESS || action == GLFW_REPEAT)
//			simulatedScene->rotateX(5);
//		break;
//
//	case GLFW_KEY_SPACE:
//		if (action == GLFW_PRESS)
//			simulatedScene->toggleSolvingMode();
//		break;
//
//	default:
//		break;
//	}
//}
//
//void mouse_callback(GLFWwindow* window, int button, int action, int mods) {
//	if (action == GLFW_PRESS) {
//		double xpos, ypos;
//		glfwGetCursorPos(window, &xpos, &ypos);
//		simulatedScene->select(xpos, ypos);
//	}
//	else if (action == GLFW_RELEASE) {
//		simulatedScene->unselect();
//	}
//}
//
//void cursor_position_callback1(GLFWwindow* window, double xpos, double ypos) {
//	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
//		simulatedScene->translate(xpos, ypos);
//	}
//	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
//		simulatedScene->rotate(xpos, ypos);
//	}
//}
//void window_size_callback(GLFWwindow* window, int width, int height) {
//	scn->Resize(width, height);
//	relation = (float)width / (float)height;
//}
//}

namespace thesis {
	class InteractionsHandler {
	public:
		InteractionsHandler();
		virtual ~InteractionsHandler();

		inline bool isActive() const {
			return !glfwWindowShouldClose(display->window);
		}

		void initCallbacks() const;

	private:
		//friends:
		friend void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend void mouseCallback(GLFWwindow* window, int button, int action, int mods);
		friend void framebufferSizeCallback(GLFWwindow* window, int width, int height);

		//fields:
		Display* display;
		int width;
		int height;
		
		std::vector<glm::dvec2> realVertices;
		std::vector<glm::dvec2> cloud;
		std::vector<glm::dvec2> estimatedVertices;

		bool showRealTriangle;
		bool showClould;
		bool showEstimatedTrinagle;
		
		//methods:
		void draw() const;
		void drawRealTriangle() const;
		void drawCloud() const;
		void drawEstimatedTriangle() const;
		void showResult() const;
		void generateNewPointsCloud();
		void addVertex(const double& xpos, const double& ypos);
	};
}