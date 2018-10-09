/*
 * sketch.cpp
 *
 *  Created on: 8 Oct 2018
 *      Author: hatsil
 */

#define GLEW_STATIC
#include <GL/glew.h>

#include "sketch.hpp"
#include "canvasDrawableDelegate.hpp"

namespace thesis {
Sketch::Sketch(const std::vector<glm::vec2>& poitns):
	CanvasDrawable(),
	Removable(),
	points(poitns),
	mesh(nullptr),
	color(defaultSketchColor),
	relatives(),
	isRipped(false), pressed(false),
	released(true), moved(false), marked(false),
	xposPrev(0), yposPrev(0) {
	p1 = new EdgePoint(q1());
	p2 = new EdgePoint(q2());
	p1->setParent(this);
	p2->setParent(this);
	relatives.insert(this);
	relatives.insert(p1);
	relatives.insert(p2);
}

Sketch::~Sketch() {
	if(!isRipped) {
		delete p1;
		delete p2;
	}

	delete mesh;
}

void Sketch::defaultDraw() const {
	glm::mat4 transformation = calcTransformation();
	if(isBold()) {
		float prevLineWidth;
		glGetFloatv(GL_LINE_WIDTH, &prevLineWidth);
		glLineWidth(boldLineWidth);
		mesh->draw(transformation, color);
		glLineWidth(prevLineWidth);
		if(pressed) {
			p1->draw();
			p2->draw();
		}
		return;
	}
	mesh->draw(transformation, color);
}

void Sketch::defaultDrawForPicking() const {
	glm::mat4 transformation = calcTransformation();
	float prevLineWidth;
	glGetFloatv(GL_LINE_WIDTH, &prevLineWidth);
	glLineWidth(boldLineWidth);
	mesh->draw(transformation, pickingColorVec);
	glLineWidth(prevLineWidth);

	if(pressed) {
		p1->drawForPicking();
		p2->drawForPicking();
	}
}

void Sketch::controlDraw() const {
	glm::mat4 transformation = calcTransformation();
	mesh->draw(transformation, defaultLineColor);
	p1->draw();
	p2->draw();
}

void Sketch::controlDrawForPicking() const {
	p1->drawForPicking();
	p2->drawForPicking();
}

void Sketch::setDelegate(CanvasDrawableDelegate* canvasDrawableDelegate) {
	CanvasDrawable::setDelegate(canvasDrawableDelegate);
}

void Sketch::setDelegate(RemovableDelegate* removableDelegate) {
	Removable::setDelegate(removableDelegate);
	p1->setDelegate(removableDelegate);
	p2->setDelegate(removableDelegate);
}

void Sketch::ripMe() {
	if(!isRipped) {
		isRipped = true;
		canvasDrawableDelegate->remove(it);
		removableDelegate->addRipped(p1);
		removableDelegate->addRipped(p2);
		removableDelegate->addRipped(this);
		selectableDelegate->setClearRemovables();
	}
}

void Sketch::leftPress(Selectable* prev) {
	pressed = true;
	released = false;
	moved = false;
	p1->setDefaultState();
	p2->setDefaultState();
	selectableDelegate->getCursorPosition(xposPrev, yposPrev);
	if(isRelative(prev))
		selectableDelegate->setDraw();
	else {
		canvasDrawableDelegate->moveToFront(it);
		selectableDelegate->setDrawForPicking();
	}
}

void Sketch::leftRelease() {
	released = true;
	if(moved) selectableDelegate->setDrawForPicking();
	else selectableDelegate->setDraw();
}

void Sketch::leftPosition(double xpos, double ypos) {
	if(pressed && !released) {
		moved = true;
		glm::vec2 q1 = convertPos(xposPrev, yposPrev);
		glm::vec2 q2 = convertPos(xpos, ypos);
		xposPrev = xpos;
		yposPrev = ypos;

		glm::vec2 dir = q2 - q1;
		p1->addOffset(dir);
		p2->addOffset(dir);

		selectableDelegate->setDraw();
	}
}

void Sketch::resign() {
	pressed = marked = moved = false;
	color = defaultSketchColor;
	p1->setDefaultState();
	p2->setDefaultState();
	selectableDelegate->setDrawForPicking();
}

void Sketch::middlePress() {
	pressed = true;
	released =  false;
	moved = false;
	color = middlePressedColor;
	p1->setDefaultState();
	p2->setDefaultState();
	selectableDelegate->setDrawForPicking();
}

void Sketch::middleRelease() {
	if(selectableDelegate->getSelectable() == this) {
		ripMe();
		return;
	}
	color = defaultSketchColor;
	released = true;
	selectableDelegate->setDrawForPicking();
}

bool Sketch::mark() {
	if(!pressed) {
		marked = true;
		p1->setDefaultState();
		p2->setDefaultState();
		return true;
	}
	return false;
}

bool Sketch::unmark() {
	if(!pressed) {
		marked = false;
		return true;
	}
	return false;
}

void Sketch::setDelegate(SelectableDelegate* selectableDelegate) {
	Selectable::setDelegate(selectableDelegate);
	mesh = new LineMesh(selectableDelegate->getSimpleShader(), points);
	p1->setDelegate(selectableDelegate);
	p2->setDelegate(selectableDelegate);
}

} /* namespace thesis */
