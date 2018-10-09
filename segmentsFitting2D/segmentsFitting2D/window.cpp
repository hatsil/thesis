/*
 * Window.cpp
 *
 *  Created on: 14 Sep 2018
 *      Author: hatsil
 */

#define GLEW_STATIC
#include <GL/glew.h>

#include "window.hpp"

#include <cmath>

namespace thesis {
static const size_t CANVAS_WIDTH = 800;
static const size_t CANVAS_HEIGHT = 800;
static const size_t BUTTON_SIZE = 70;
static const size_t WINDOW_WIDTH = CANVAS_WIDTH;
static const size_t WINDOW_HEIGHT = CANVAS_HEIGHT + BUTTON_SIZE + BUTTON_SIZE / (size_t)5;

static const char* WINDOW_TITLE = "2D Basic GUI";

static GLFWwindow* makeWindow() {
	std::string what("Failed init window");
	bool needTermination = false;
	GLFWwindow* glfwWindow = nullptr;
	//Initialize the library:
	if(glfwInit()) {
		needTermination = true;
		if((glfwWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, 0, 0))) {
			glfwMakeContextCurrent(glfwWindow);
			if(glewInit() != GLEW_OK) {
				what += ": Glew failed to initialize";
				goto bad;
			}
			glClearColor(1, 1, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			glfwSwapBuffers(glfwWindow);
			glClear(GL_COLOR_BUFFER_BIT);
			return glfwWindow;
		}
		what += ": Failed to create glfw window";
		goto bad;
	}

bad:
	if(glfwWindow)
		glfwDestroyWindow(glfwWindow);

	if(needTermination)
		glfwTerminate();

	throw std::runtime_error(what);
}

void keyCallback1(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods) {
	Window* window;
	if(!glfwWindowShouldClose(glfwWindow) &&
		(window = (Window*)glfwGetWindowUserPointer(glfwWindow)))
		window->keyCallback(key, scancode, action, mods);
}

void mouseCallback1(GLFWwindow* glfwWindow, int button, int action, int mods) {
	Window* window;
	if(!glfwWindowShouldClose(glfwWindow) &&
		(window = (Window*)glfwGetWindowUserPointer(glfwWindow)))
		window->mouseCallback(button, action, mods);
}

void cursorPositionCallback1(GLFWwindow* glfwWindow, double xpos, double ypos) {
	Window* window;
	if(!glfwWindowShouldClose(glfwWindow) &&
		(window = (Window*)glfwGetWindowUserPointer(glfwWindow)))
		window->cursorPositionCallback(xpos, ypos);
}

Window::Window():
	glfwWindow(makeWindow()),
	selectables(),
	width(WINDOW_WIDTH),
	height(WINDOW_HEIGHT),
	prevTime(std::chrono::system_clock::now()),
	waitingTime(0),
	drawStatus(false),
	drawForPickingStatus(false),
	clearRemovablesStatus(false),
	selected(nullptr),
	marked(nullptr) {
	colorsBuffer = new uchar[WINDOW_WIDTH * WINDOW_HEIGHT * (size_t)4];

	simpleShader = new SimpleShader;
	texShader = new TexShader;
	cubicSplineShader = new CubicSplineShader;

	lineMesh = new LineMesh(*simpleShader);
	squareMesh = new SquareMesh(*simpleShader);
	texMesh = new TexMesh(*texShader);
	cubicSplineMesh = new CubicSplineMesh(*cubicSplineShader);

	canvas = new Canvas(CANVAS_WIDTH, CANVAS_HEIGHT);
	buttonsHolder = new ButtonsHolder(WINDOW_WIDTH, BUTTON_SIZE);

	buttonsHolder->setDelegate(this);
	canvas->setDelegate(this);

	glfwSetWindowUserPointer(glfwWindow, this);

	drawAll();
	
	initCallbacks();
}

Window::~Window() {
	canvas->wait();
	canvas->clearRippedObjects();

	delete canvas;
	delete buttonsHolder;

	delete texMesh;
	delete squareMesh;
	delete lineMesh;
	delete cubicSplineMesh;

	delete texShader;
	delete simpleShader;
	delete cubicSplineShader;

	delete[] colorsBuffer;

	glfwDestroyWindow(glfwWindow);
	glfwTerminate();
}

bool Window::isActive() const {
	return !glfwWindowShouldClose(glfwWindow);
}

bool Window::waitForever() const {
	return !drawStatus;
}

double Window::getWaitingTime() const {
	return waitingTime;
}

void Window::buttonsHolderViewport() const {
	glViewport(
		0,
		(GLint)canvas->getHeight(),
		(GLsizei)buttonsHolder->getWidth(),
		(GLsizei)buttonsHolder->getHeight()
	);
}

void Window::canvasViewport() const {
	glViewport(
		0,
		0,
		(GLsizei)canvas->getWidth(),
		(GLsizei)canvas->getHeight()
	);
}

void Window::draw() const {
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	buttonsHolderViewport();
	buttonsHolder->draw();
	canvasViewport();
	canvas->draw();
	glfwSwapBuffers(glfwWindow);
}

void Window::drawForPicking() const {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	buttonsHolderViewport();
	buttonsHolder->drawForPicking();
	canvasViewport();
	canvas->drawForPicking();
	glFlush();
	glFinish();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glReadPixels(
		0,
		0,
		(GLsizei)width,
		(GLsizei)height,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		colorsBuffer
	);
}

void Window::addSelectable(Selectable* selectable) {
	selectables.insert(selectable);
}

void Window::removeSelectable(Selectable* selectable) {
	selectables.erase(selectable);
}

void Window::initCallbacks() const {
	glfwSetKeyCallback(glfwWindow, keyCallback1);
	glfwSetMouseButtonCallback(glfwWindow, mouseCallback1);
	glfwSetCursorPosCallback(glfwWindow, cursorPositionCallback1);
}

void Window::keyCallback(int key, int scancode, int action, int mods) {
	switch (key) {
	case GLFW_KEY_ESCAPE:
		if(action == GLFW_PRESS)
			glfwSetWindowShouldClose(glfwWindow, GLFW_TRUE);
		break;

	case GLFW_KEY_LEFT_CONTROL:
		if(action == GLFW_PRESS)
			controlPress();
		else if(action == GLFW_RELEASE)
			controlRelease();
		break;

	case GLFW_KEY_DELETE:
		if(action == GLFW_RELEASE && selected && selected->isRemovable()) {
			selected->resign();
			((Removable*)selected)->ripMe();
			drawIfNeeded();
		}
		break;

	case GLFW_KEY_BACKSPACE:
		if(action == GLFW_PRESS || action == GLFW_REPEAT) {
			if(marked) {
				marked->unmark();
				marked = nullptr;
			}

			if(selected) {
				selected->resign();
				selected = nullptr;
			}

			canvas->undo();
			drawIfNeeded();
		}
		break;
	}
}

void Window::mouseCallback(int button, int action, int mods) {	
	switch(button) {
	case GLFW_MOUSE_BUTTON_LEFT:
		if(action == GLFW_PRESS) {
			double xpos, ypos;
			getCursorPosition(xpos, ypos);
			Selectable* newSelectable = getSelectable(xpos, ypos);

			if(selected && selected != newSelectable)
				selected->resign();

			if(newSelectable)
				newSelectable->leftPress(selected);
			
			selected = newSelectable;

			drawIfNeeded();
		} else {
			if(selected) {
				selected->leftRelease();
				drawIfNeeded();
			}

		}
		break;

	case GLFW_MOUSE_BUTTON_RIGHT:
		if(action == GLFW_PRESS) {
			double xpos, ypos;
			getCursorPosition(xpos, ypos);
			Selectable* newSelectable = getSelectable(xpos, ypos);

			if(selected && selected != newSelectable)
				selected->resign();

			if(newSelectable)
				newSelectable->rightPress();

			selected = newSelectable;

			drawIfNeeded();
		} else {
			if(selected) {
				selected->rightRelease();
				drawIfNeeded();
			}
		}
		break;

	case GLFW_MOUSE_BUTTON_MIDDLE:
		if(action == GLFW_PRESS) {
			double xpos, ypos;
			getCursorPosition(xpos, ypos);
			Selectable* newSelectable = getSelectable(xpos, ypos);

			if(selected && selected != newSelectable)
				selected->resign();
			
			selected = newSelectable;
			
			if(newSelectable)
				newSelectable->middlePress();

			drawIfNeeded();
		} else {
			if(selected) {
				selected->middleRelease();
				drawIfNeeded();
			}
		}
		break;
	}
}

void Window::cursorPositionCallback(double xpos, double ypos) {
	if(glfwGetMouseButton(glfwWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if(selected) {
			selected->leftPosition(xpos, ypos);
			drawIfNeeded();
		}
	} else if(glfwGetMouseButton(glfwWindow, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		if(selected) {
			selected->rightPosition(xpos, ypos);
			drawIfNeeded();
		}
	} else if(glfwGetMouseButton(glfwWindow, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE) {
		Selectable* newMarkable = getSelectable(xpos, ypos);

		if(marked != newMarkable) {
			drawStatus = false;
			if(marked)
				drawStatus = marked->unmark();
			
			if(newMarkable)
				drawStatus |= newMarkable->mark();
			
			marked = newMarkable;
		}

		if(selected)
			selected->position(xpos, ypos);

		drawIfNeeded();
	}
}

void Window::getCursorPosition(double& xpos, double& ypos) const {
	glfwGetCursorPos(glfwWindow, &xpos, &ypos);
}

void Window::fixOffsetCanvas(double&, double& ypos) const {
	ypos -= buttonsHolder->getHeight();
}

void Window::buttonViewport(int i) const {
	int offset = (GLint)BUTTON_SIZE / 10;
	int buttonWidth = (GLint)BUTTON_SIZE + offset;
	glViewport(
		i*buttonWidth + offset,
		(GLint)canvas->getHeight() + offset,
		(GLsizei)BUTTON_SIZE,
		(GLsizei)BUTTON_SIZE
	);
}

void Window::setDefaultPlate() {
	canvas->setDefaultPlate();
}

void Window::setLinePlate() {
	canvas->setLinePlate();
}

void Window::setBrokenLinePlate() {
	canvas->setBrokenLinePlate();
}

void Window::setCurvePlate() {
	canvas->setCurvePlate();
}

void Window::setSketchPlate() {
	canvas->setSketchPlate();
}

Selectable* Window::getDefaultPlate() const {
	return canvas->getDefaultPlate();
}

Selectable* Window::getControlPlate() const {
	return canvas->getControlPlate();
}

Selectable* Window::getLinePlate() const {
	return canvas->getLinePlate();
}

Selectable* Window::getBrokenLinePlate() const {
	return canvas->getBrokenLinePlate();
}

Selectable* Window::getCurvePlate() const {
	return canvas->getCurvePlate();
}

Selectable* Window::getSketchPlate() const {
	return canvas->getSketchPlate();
}

void Window::drawAll() {
	if(clearRemovablesStatus) {
		canvas->clearRippedObjects();
		selected = marked = nullptr;
	}
	drawStatus = drawForPickingStatus = false;
	prevTime = std::chrono::system_clock::now();
	drawForPicking();
	draw();
}

void Window::setDraw() {
	drawStatus = true;
	drawForPickingStatus = false;
	clearRemovablesStatus = false;
}

void Window::setDrawForPicking() {
	drawStatus = true;
	drawForPickingStatus = true;
	clearRemovablesStatus = false;
}

void Window::setClearRemovables() {
	drawStatus = true;
	drawForPickingStatus = true;
	clearRemovablesStatus = true;
}

void Window::drawIfNeeded() {
	if(clearRemovablesStatus) {
		clearRemovablesStatus = false;
		selected = marked = nullptr;
		canvas->clearRippedObjects();
	}

	if(drawForPickingStatus)
		drawForPicking();

	if(drawStatus) {
		auto curTime = std::chrono::system_clock::now();
		if(drawForPickingStatus) {
			drawForPickingStatus = false;
			drawStatus = false;
			prevTime = curTime;
			draw();
		} else {
			std::chrono::duration<double, std::milli> dur = curTime - prevTime;
			double count = dur.count();
			if(count > 30) {
				drawStatus = false;
				prevTime = curTime;
				draw();
			} else waitingTime = (31 - count) / 1000.;
		}
	}
	drawForPickingStatus = false;
}

Selectable* Window::getSelectable() const {
	double xpos, ypos;
	getCursorPosition(xpos, ypos);
	return getSelectable(xpos, ypos);
}

const LineMesh& Window::getLineMesh() const {
	return *lineMesh;
}

const SquareMesh& Window::getSquareMesh() const {
	return *squareMesh;
}

const TexMesh& Window::getTexMesh() const {
	return *texMesh;
}

const CubicSplineMesh& Window::getCubicSplineMesh() const {
	return *cubicSplineMesh;
}

const SimpleShader& Window::getSimpleShader() const {
	return *simpleShader;
}

Selectable* Window::getSelectable(double xpos, double ypos) const {
	int x = (int)xpos;
	int y = (int)height-1 - (int)ypos;
	
	if(x < 0 || x >= (int)width || y < 0 || y >= (int)height)
		return nullptr;
	
	size_t i = ((size_t)y * width + (size_t)x) * (size_t)4;
	uchar* pixel = colorsBuffer + i;
	uint colorID = (uint)pixel[2] + ((uint)pixel[1] << 8) + ((uint)pixel[0] << 16);

	if(colorID == 0)
		return nullptr;
	
	auto it = selectables.find(colorID);
	
	if(it == selectables.cend())
		return nullptr;
	
	return *it;
}

void Window::controlPress() {
	if(marked) {
		marked->unmark();
		marked = nullptr;
	}

	if(selected) {
		selected->resign();
		selected = nullptr;
	}

	buttonsHolder->controlPress();
	canvas->controlPress();
	drawAll();
}

void Window::controlRelease() {
	if(marked) {
		marked->unmark();
		marked = nullptr;
	}

	buttonsHolder->controlRelease();
	canvas->controlRelease();
	drawAll();
}

} /* namespace thesis */
