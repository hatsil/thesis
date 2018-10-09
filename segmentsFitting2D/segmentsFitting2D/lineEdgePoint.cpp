/*
 * lineEdgePoint.cpp
 *
 *  Created on: 8 Oct 2018
 *      Author: hatsil
 */

#include "line.hpp"

namespace thesis {
Line::EdgePoint::EdgePoint(const glm::vec2& position):
	Removable(),
	position(position),
	parent(nullptr),
	translation(glm::translate(glm::mat4(1), glm::vec3(position, 0))),
	color(normalJointColor),
	pressed(false), released(false), moved(false),
	xposPrev(0), yposPrev(0) {}

Line::EdgePoint::~EdgePoint() {}

void Line::EdgePoint::draw() const {
	mesh().draw(translation * scale(), color);
}

void Line::EdgePoint::drawForPicking() const {
	mesh().draw(translation * scale(), pickingColorVec);
}

void Line::EdgePoint::leftPress(Selectable* prev) {
	parent->leftPress(prev);
	pressed = true;
	released = false;
	moved = false;
	color = selectedJointColor;
	selectableDelegate->getCursorPosition(xposPrev, yposPrev);
}

void Line::EdgePoint::leftRelease() {
	released = true;
	if(moved) selectableDelegate->setDrawForPicking();
	else selectableDelegate->setDraw();
}

void Line::EdgePoint::leftPosition(double xpos, double ypos) {
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

void Line::EdgePoint::middlePress() {
	parent->middlePress();
}

void Line::EdgePoint::middleRelease() {
	if(selectableDelegate->getSelectable() == this) {
		ripMe();
		return;
	}
	parent->color = defaultLineColor;
	parent->released = true;
	setDefaultState();
	selectableDelegate->setDrawForPicking();
}

void Line::EdgePoint::resign() {
	parent->resign();
}

bool Line::EdgePoint::mark() {
	if(!pressed) {
		color = markedJointColor;
		return true;
	}
	return false;
}

bool Line::EdgePoint::unmark() {
	if(!pressed) {
		color = normalJointColor;
		return true;
	}
	return false;
}

void Line::EdgePoint::setDelegate(SelectableDelegate* selectableDelegate) {
	Selectable::setDelegate(selectableDelegate);
}

void Line::EdgePoint::ripMe() {
	parent->ripMe();
}

void Line::EdgePoint::setDelegate(RemovableDelegate* removableDelegate) {
	Removable::setDelegate(removableDelegate);
}

} /* namespace thesis */
