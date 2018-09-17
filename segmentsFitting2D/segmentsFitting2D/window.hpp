/*
 * window.hpp
 *
 *  Created on: 14 Sep 2018
 *      Author: hatsil
 */

#pragma once

#include "shaders.hpp"
#include "buttonsHolder.hpp"
#include "canvas.hpp"
#include "concurrent.hpp"

#include <set>
#include <string>
#include <exception>
#include <stdexcept>

#include <GLFW/glfw3.h>

namespace thesis {

class Window {
public:
	Window();
	virtual ~Window();

private:
	GLFWwindow* glfwWindow;
	std::set<Pressable*, PressablePtrComp> pressables;

	ButtonsHolder* buttons;
	Canvas* canvas;

	//shaders:
	SimpleShader* simpleShader;
	TexShader* texShader;
	
	Pressable* selected;

	//methods:
	void keyCallback(int key, int scancode, int action, int mods);
	void mouseCallback(int button, int action, int mods);
	void cursorPositionCallback(double xpos, double ypos);
	void drawForPicking() const;
	void select();
	void deselect();

	//friends:
	friend void keyCallback1(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods);
	friend void mouseCallback1(GLFWwindow* glfwWindow, int button, int action, int mods);
	friend void cursorPositionCallback1(GLFWwindow* glfwWindow, double xpos, double ypos);
};

} /* namespace thesis */

