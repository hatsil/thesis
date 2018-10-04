#define GLEW_STATIC
#include <GL/glew.h>

#include "line.hpp"
#include "removableDelegate.hpp"
#include "canvasDrawableDelegate.hpp"

#include <cmath>

namespace thesis {

Line::Line(const glm::vec2& q1, const glm::vec2& q2):
	CanvasDrawable(),
	Removable(),
	color(defaultLineColor),
	relatives(),
	isRipped(false), pressed(false),
	released(false), moved(false), marked(false),
	xposPrev(0), yposPrev(0) {
	p1 = new EdgePoint(q1);
	p2 = new EdgePoint(q2);
	p1->setParent(this);
	p2->setParent(this);
	relatives.insert(this);
	relatives.insert(p1);
	relatives.insert(p2);
}

Line::~Line() {
	delete p1;
	delete p2;
}

void Line::defaultDraw() const {
	glm::mat4 transformation = calcTransformation();
	if(isBold()) {
		float prevLineWidth;
		glGetFloatv(GL_LINE_WIDTH, &prevLineWidth);
		glLineWidth(boldLineWidth);
		mesh().draw(transformation, color);
		glLineWidth(prevLineWidth);
		if(pressed) {
			p1->draw();
			p2->draw();
		}
		return;
	}
	mesh().draw(transformation, color);
}

void Line::defaultDrawForPicking() const {
	glm::mat4 transformation = calcTransformation();
	float prevLineWidth;
	glGetFloatv(GL_LINE_WIDTH, &prevLineWidth);
	glLineWidth(boldLineWidth);
	mesh().draw(transformation, pickingColorVec);
	glLineWidth(prevLineWidth);
	
	if(isBold()) {
		p1->drawForPicking();
		p2->drawForPicking();
	}
}
	
void Line::controlDraw() const {
	glm::mat4 transformation = calcTransformation();
	mesh().draw(transformation, defaultLineColor);
	p1->draw();
	p2->draw();
}

void Line::controlDrawForPicking() const {
	p1->drawForPicking();
	p2->drawForPicking();
}

void Line::setDelegate(CanvasDrawableDelegate* canvasDrawableDelegate) {
	CanvasDrawable::setDelegate(canvasDrawableDelegate);
}

void Line::setDelegate(RemovableDelegate* removableDelegate) {
	Removable::setDelegate(removableDelegate);
}

void Line::ripMe() {
	if(!isRipped) {
		isRipped = true;
		canvasDrawableDelegate->remove(it);
		selectableDelegate->removeSelectable(p1);
		selectableDelegate->removeSelectable(p2);
		removableDelegate->addRipped(this);
		selectableDelegate->setClearRemovables();
	}
}

void Line::leftPress(Selectable* prev) {
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

void Line::leftRelease() {
	released = true;
	if(moved) selectableDelegate->setDrawForPicking();
	else selectableDelegate->setDraw();
}

void Line::leftPosition(double xpos, double ypos) {
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

void Line::resign() {
	pressed = marked = moved = false;
	color = defaultLineColor;
	p1->setDefaultState();
	p2->setDefaultState();
	selectableDelegate->setDrawForPicking();
}

void Line::middlePress() {
	pressed = true;
	released =  false;
	moved = false;
	color = middlePressedColor;
	p1->setDefaultState();
	p2->setDefaultState();
	selectableDelegate->setDrawForPicking();
}

void Line::middleRelease() {
	if(selectableDelegate->getSelectable() == this) {
		ripMe();
		return;
	}
	color = defaultLineColor;
	released = true;
	selectableDelegate->setDrawForPicking();
}

bool Line::mark() {
	if(!pressed) {
		marked = true;
		p1->setDefaultState();
		p2->setDefaultState();
		return true;
	}
	return false;
}

bool Line::unmark() {
	if(!pressed) {
		marked = false;
		return true;
	}
	return false;
}

void Line::setDelegate(SelectableDelegate* selectableDelegate) {
	Selectable::setDelegate(selectableDelegate);
	p1->setDelegate(selectableDelegate);
	p2->setDelegate(selectableDelegate);
}


//MARK: EdgePoint
Line::EdgePoint::EdgePoint(const glm::vec2& position):
	Selectable(),
	position(position),
	translation(glm::translate(glm::mat4(1), glm::vec3(position, 0))),
	scale(glm::scale(glm::mat4(1), jointScaleFactor)),
	color(normalJointColor),
	pressed(false), released(false), moved(false),
	xposPrev(0), yposPrev(0) {}

Line::EdgePoint::~EdgePoint() {}

void Line::EdgePoint::draw() const {
	mesh().draw(translation * scale, color);
}

void Line::EdgePoint::drawForPicking() const {
	mesh().draw(translation * scale, pickingColorVec);
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

} /* namespace thesis */