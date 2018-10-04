#define GLEW_STATIC
#include <GL/glew.h>

#include "brokenLine.hpp"

namespace thesis {
BrokenLine::Segment::Segment():
	Removable(),
	deleteParent(false) {}

BrokenLine::Segment::~Segment() {
	if(deleteParent)
		delete parent;
}

void BrokenLine::Segment::leftPress(Selectable* prev) {
	parent->leftPress(prev);
}

void BrokenLine::Segment::leftRelease() {
	parent->leftRelease();
}

void BrokenLine::Segment::leftPosition(double xpos, double ypos) {
	parent->leftPosition(xpos, ypos);
}

void BrokenLine::Segment::resign() {
	parent->resign();
}

void BrokenLine::Segment::middlePress() {
	parent->middlePress();
}

void BrokenLine::Segment::middleRelease() {
	parent->middleRelease(this);
}

bool BrokenLine::Segment::mark() {
	return parent->mark();
}

bool BrokenLine::Segment::unmark() {
	return parent->unmark();
}

void BrokenLine::Segment::ripMe() {
	deleteParent = true;
	parent->forEach([&](Joint* joint) {
		removableDelegate->addRemovable(joint);
		if(joint->segment)
			removableDelegate->addRipped(joint->segment);
	});
	parent->clear();
	selectableDelegate->setClearRemovables();
}

void BrokenLine::Segment::setDelegate(SelectableDelegate* selectableDelegate) {
	Selectable::setDelegate(selectableDelegate);
}

void BrokenLine::Segment::setDelegate(RemovableDelegate* removableDelegate) {
	Removable::setDelegate(removableDelegate);
}

void BrokenLine::Segment::draw() const {
	glm::mat4 transformation = calcTransformation();
	if(parent->isBold()) {
		float prevLineWidth;
		glGetFloatv(GL_LINE_WIDTH, &prevLineWidth);
		glLineWidth(boldLineWidth);
		mesh().draw(transformation, parent->color);
		glLineWidth(prevLineWidth);
		return;
	}
	mesh().draw(transformation, parent->color);
}

void BrokenLine::Segment::drawForPicking() const {
	glm::mat4 transformation = calcTransformation();
	float prevLineWidth;
	glGetFloatv(GL_LINE_WIDTH, &prevLineWidth);
	glLineWidth(boldLineWidth);
	mesh().draw(transformation, pickingColorVec);
	glLineWidth(prevLineWidth);
}

void BrokenLine::Segment::controlDraw() const {
	glm::mat4 transformation = calcTransformation();
	mesh().draw(transformation, defaultLineColor);
}

} /* namespace thesis */