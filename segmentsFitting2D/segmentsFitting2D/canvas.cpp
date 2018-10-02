/*
 * canvas.cpp
 *
 *  Created on: 14 Sep 2018
 *      Author: hatsil
 */

#define GLEW_STATIC
#include <GL/glew.h>

#include "canvas.hpp"
#include "canvasDrawables.hpp"

#include "canvasDelegate.hpp"

#include "globalVars.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace thesis {
Canvas::Canvas(size_t width, size_t height) :
	Drawable(),
	width(width),
	height(height),
	removables(),
	rippedObjects(),
	drawables(),
	lineTransformation(nullptr) {
	defaultPlate = new DefaultPlate;
	controlPlate = new ControlPlate;
	linePlate = new LinePlate;
	defaultPlate->setDelegate((DefaultPlateDelegate*)this);
	linePlate->setDelegate((LinePlateDelegate*)this);
	controlPlate->setDelegate((ControlPlateDelegate*)this);
	//set defalt plate:
	curPlate = prevPlate = defaultPlate;
}

Canvas::~Canvas() {
	delete defaultPlate;
	delete linePlate;
	delete controlPlate;

	if(lineTransformation)
		delete lineTransformation;
	
	for(CanvasDrawable* canvasDrawable : drawables)
		delete canvasDrawable;
}

glm::vec2 Canvas::convertPos(double xpos, double ypos) const {
	canvasDelegate->fixOffsetCanvas(xpos, ypos);
	double x = (2 * xpos - (double)width) / (double)width;
	double y = ((double)height - 2 * ypos) / (double)height;
	return {x, y};
}

void Canvas::lineDraw() {
	defaultDraw();
	if(lineTransformation) {
		float prevLineWidth;
		glGetFloatv(GL_LINE_WIDTH, &prevLineWidth);
		glLineWidth(boldLineWidth);
		lineMesh().draw(*lineTransformation, defaultLineColor);
		glLineWidth(prevLineWidth);
		
		//cleanup
		delete lineTransformation;
		lineTransformation = nullptr;
	}
}

void Canvas::setTempLine(double xposBegin, double yposBegin, double xposEnd, double yposEnd) {
	if(lineTransformation)
		delete lineTransformation;

	//calc transformation
	glm::vec2 p1 = convertPos(xposBegin, yposBegin);
	glm::vec2 p2 = convertPos(xposEnd, yposEnd);
	glm::vec2 dir = p2 - p1;
	float angle = std::acos(glm::dot(glm::normalize(dir), { 1, 0 }));

	if (dir.y < 0)
		angle = -angle;

	glm::mat4 t = glm::translate(glm::mat4(1), glm::vec3(p1, 0));
	glm::mat4 tr = glm::rotate(t, angle, glm::vec3(0, 0, 1));
	lineTransformation = new glm::mat4(glm::scale(tr, glm::vec3(glm::length(dir), 0, 0)));
}

void Canvas::packLine(double xposBegin, double yposBegin) {
	if(lineTransformation) {
		delete lineTransformation;
		lineTransformation = nullptr;
	}

	double xposEnd;
	double yposEnd;
	canvasDelegate->getCursorPosition(xposEnd, yposEnd);
	glm::vec2 p1 = convertPos(xposBegin, yposBegin);
	glm::vec2 p2 = convertPos(xposEnd, yposEnd);
	Line* line = new Line(p1, p2);
	line->setDelegate(canvasDelegate);
	line->setDelegate((RemovableDelegate*)this);
	line->setDelegate((CanvasDrawableDelegate*)this);
	line->inserted(drawables.insert(drawables.cend(), line));
}

void Canvas::addRemovable(Removable* removable) {
	removables.insert(removable);
}

void Canvas::remove(const std::list<CanvasDrawable*>::iterator& it) {
	drawables.erase(it);
}

void Canvas::moveToFront(std::list<CanvasDrawable*>::iterator& it) {
	CanvasDrawable* canvasDrawable = *it;
	drawables.erase(it);
	it = drawables.insert(drawables.cend(), canvasDrawable);
}

void Canvas::addRipped(Removable* ripped) {
	rippedObjects.push_back(ripped);
}

void Canvas::controlPress() {
	prevPlate = curPlate;
	curPlate = controlPlate;
}

void Canvas::controlRelease() {
	curPlate = prevPlate;
}

void Canvas::setDefaultPlate() {
	curPlate = defaultPlate;
}

void Canvas::setLinePlate() {
	curPlate = linePlate;
}

Selectable* Canvas::getDefaultPlate() const {
	return defaultPlate;
}

Selectable* Canvas::getControlPlate() const {
	return controlPlate;
}

Selectable* Canvas::getLinePlate() const {
	return linePlate;
}

void Canvas::clearRippedObjects() {
	for(auto it = rippedObjects.begin(); it != rippedObjects.end();) {
		Removable* removable = *it;
		canvasDelegate->removeSelectable(removable);
		removables.erase(removable);
		it = rippedObjects.erase(it);
		delete removable;
	}
}

void Canvas::draw() const {
	curPlate->draw();
}

void Canvas::drawForPicking() const {
	curPlate->drawForPicking();
}

void Canvas::defaultDraw() const {
	forEach(&CanvasDrawable::defaultDraw);
}

void Canvas::defaultDrawForPicking() const {
	forEach(&CanvasDrawable::defaultDrawForPicking);
}

void Canvas::controlDraw() const {
	forEach(&CanvasDrawable::controlDraw);
}

void Canvas::controlDrawForPicking() const {
	forEach(&CanvasDrawable::controlDrawForPicking);
}

void Canvas::forEach(CanvasDrawableFunc func) const {
	for(CanvasDrawable* canvasDrawable : drawables)
		(canvasDrawable->*func)();
}

const LineMesh& Canvas::lineMesh() const {
	return canvasDelegate->getLineMesh();
}

void Canvas::undo() {
	//TODO: implement
}

void Canvas::wait() {
	//TODO: implement
}

size_t Canvas::getWidth() const {
	return width;
}

size_t Canvas::getHeight() const {
	return height;
}

void Canvas::setDelegate(CanvasDelegate* canvasDelegate) {
	this->canvasDelegate = canvasDelegate;
	defaultPlate->setDelegate(canvasDelegate);
	linePlate->setDelegate(canvasDelegate);
	controlPlate->setDelegate(canvasDelegate);
}

} /* namespace thesis */
