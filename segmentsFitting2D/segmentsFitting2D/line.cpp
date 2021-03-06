#define GLEW_STATIC
#include <GL/glew.h>

#include "line.hpp"
#include "canvasDrawableDelegate.hpp"

namespace thesis {
Line::Line(const glm::vec2& q1, const glm::vec2& q2):
	CanvasDrawable(),
	Removable(),
	color(defaultLineColor),
	relatives(),
	isRipped(false), pressed(false),
	released(true), moved(false), marked(false),
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
	if(!isRipped) {
		delete p1;
		delete p2;
	}
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
	
	if(pressed) {
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
	p1->setDelegate(removableDelegate);
	p2->setDelegate(removableDelegate);
}

void Line::ripMe() {
	if(!isRipped) {
		isRipped = true;
		canvasDrawableDelegate->remove(it);
		removableDelegate->addRipped(p1);
		removableDelegate->addRipped(p2);
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

} /* namespace thesis */
