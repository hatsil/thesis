/*
 * sketchEdgePoint.cpp
 *
 *  Created on: 8 Oct 2018
 *      Author: hatsil
 */

#include "sketch.hpp"

namespace thesis {
Sketch::EdgePoint::EdgePoint(const glm::vec2& position):
	Removable(),
	position(position),
	parent(nullptr),
	translation(glm::translate(glm::mat4(1), glm::vec3(position, 0))),
	color(normalJointColor),
	pressed(false), released(false), moved(false),
	xposPrev(0), yposPrev(0) {}

Sketch::EdgePoint::~EdgePoint() {}

void Sketch::EdgePoint::draw() const {
	mesh().draw(translation * scale(), color);
}

void Sketch::EdgePoint::drawForPicking() const {
	mesh().draw(translation * scale(), pickingColorVec);
}

void Sketch::EdgePoint::leftPress(Selectable* prev) {
	parent->leftPress(prev);
	pressed = true;
	released = false;
	moved = false;
	color = selectedJointColor;
	selectableDelegate->getCursorPosition(xposPrev, yposPrev);
}

void Sketch::EdgePoint::leftRelease() {
	released = true;
	if(moved) selectableDelegate->setDrawForPicking();
	else selectableDelegate->setDraw();
}

void Sketch::EdgePoint::leftPosition(double xpos, double ypos) {
	if(pressed && !released) {
		moved = true;
		glm::vec2 p0 = parent->convertPos(xposPrev, yposPrev);
		glm::vec2 p1 = parent->convertPos(xpos, ypos);
		xposPrev = xpos;
		yposPrev = ypos;

		glm::vec2 dir = p1 - p0;
		position += dir;

		calcTranslation();
		selectableDelegate->setDraw();
	}
}

void Sketch::EdgePoint::middlePress() {
	parent->middlePress();
}

void Sketch::EdgePoint::middleRelease() {
	if(selectableDelegate->getSelectable() == this) {
		ripMe();
		return;
	}
	parent->color = defaultSketchColor;
	parent->released = true;
	setDefaultState();
	selectableDelegate->setDrawForPicking();
}

void Sketch::EdgePoint::resign() {
	parent->resign();
}

bool Sketch::EdgePoint::mark() {
	if(!pressed) {
		color = markedJointColor;
		return true;
	}
	return false;
}

bool Sketch::EdgePoint::unmark() {
	if(!pressed) {
		color = normalJointColor;
		return true;
	}
	return false;
}

void Sketch::EdgePoint::setDelegate(SelectableDelegate* selectableDelegate) {
	Selectable::setDelegate(selectableDelegate);
}

void Sketch::EdgePoint::ripMe() {
	parent->ripMe();
}

void Sketch::EdgePoint::setDelegate(RemovableDelegate* removableDelegate) {
	Removable::setDelegate(removableDelegate);
}

} /* namespace thesis */



