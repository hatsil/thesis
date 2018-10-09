#define GLEW_STATIC
#include <GL/glew.h>

#include "curve.hpp"

namespace thesis {

Curve::Segment::Segment() :
	Removable(),
	parent(nullptr),
	it(),
	deleteParent(false) {}

Curve::Segment::~Segment() {
	if(deleteParent)
		delete parent;
}

void Curve::Segment::leftPress(Selectable* prev) {
	parent->leftPress(prev);
}

void Curve::Segment::leftRelease() {
	parent->leftRelease();
}

void Curve::Segment::leftPosition(double xpos, double ypos) {
	parent->leftPosition(xpos, ypos);
}

void Curve::Segment::rightPress() {
	leftPress(nullptr);
	double xpos, ypos;
	selectableDelegate->getCursorPosition(xpos, ypos);
	glm::vec2 position = parent->convertPos(xpos, ypos);
	parent->addJointAfter(position, it);
}

void Curve::Segment::rightRelease() {
	leftRelease();
}

void Curve::Segment::resign() {
	parent->resign();
}

void Curve::Segment::middlePress() {
	parent->middlePress();
}

void Curve::Segment::middleRelease() {
	parent->middleRelease(this);
}

bool Curve::Segment::mark() {
	return parent->mark();
}

bool Curve::Segment::unmark() {
	return parent->unmark();
}

void Curve::Segment::ripMe() {
	deleteParent = true;
	parent->forEach([&](Joint* joint) {
		selectableDelegate->removeSelectable(joint->tj);
		removableDelegate->addRipped(joint);
		if(joint->segment)
			removableDelegate->addRipped(joint->segment);
	});
	parent->clear();
	selectableDelegate->setClearRemovables();
}

void Curve::Segment::setDelegate(SelectableDelegate* selectableDelegate) {
	Selectable::setDelegate(selectableDelegate);
}

void Curve::Segment::setDelegate(RemovableDelegate* removableDelegate) {
	Removable::setDelegate(removableDelegate);
}

void Curve::Segment::draw() const {
	if (parent->isBold()) {
		float prevLineWidth;
		glGetFloatv(GL_LINE_WIDTH, &prevLineWidth);
		glLineWidth(boldLineWidth);
		mesh().draw(f(), parent->color);
		glLineWidth(prevLineWidth);
		return;
	}
	mesh().draw(f(), parent->color);
}

void Curve::Segment::drawForPicking() const {
	float prevLineWidth;
	glGetFloatv(GL_LINE_WIDTH, &prevLineWidth);
	glLineWidth(boldLineWidth);
	mesh().draw(f(), pickingColorVec);
	glLineWidth(prevLineWidth);
}

void Curve::Segment::controlDraw() const {
	mesh().draw(f(), defaultCurveColor);
}

} /* namespace thesis */
