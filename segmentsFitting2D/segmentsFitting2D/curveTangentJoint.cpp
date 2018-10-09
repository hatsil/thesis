#include "curve.hpp"

namespace thesis {
Curve::TangentJoint::TangentJoint():
	Selectable(),
	tangent(0),
	parent(nullptr),
	translation(1),
	color(normalTangentJointColor),
	pressed(false), released(false), moved(false),
	xposPrev(0), yposPrev(0) {}

Curve::TangentJoint::~TangentJoint() {}

void Curve::TangentJoint::draw() const {
	mesh().draw(translation * rot45Scale(), color);
}

void Curve::TangentJoint::drawForPicking() const {
	mesh().draw(translation * rot45Scale(), pickingColorVec);
}

void Curve::TangentJoint::leftPress(Selectable*) {
	parent->leftPress(nullptr);
	pressed = true;
	released = false;
	moved = false;
	color = selectedTangentJointColor;
	selectableDelegate->getCursorPosition(xposPrev, yposPrev);
	selectableDelegate->setDraw();
}

void Curve::TangentJoint::leftRelease() {
	released = true;
	if(moved) selectableDelegate->setDrawForPicking();
	else selectableDelegate->setDraw();
}

void Curve::TangentJoint::leftPosition(double xpos, double ypos) {
	if(pressed && !released) {
		moved = true;
		glm::vec2 p0 = parent->convertPos(xposPrev, yposPrev);
		glm::vec2 p1 = parent->convertPos(xpos, ypos);
		xposPrev = xpos;
		yposPrev = ypos;

		glm::vec2 dir = p1 - p0;
		tangent += dir;

		calcTranslation();
		selectableDelegate->setDraw();
	}
}

void Curve::TangentJoint::resign() {
	parent->resign();
}

void Curve::TangentJoint::middlePress() {
	parent->middlePress();
}

void Curve::TangentJoint::middleRelease() {
	parent->middleRelease();
}

bool Curve::TangentJoint::mark() {
	if(!pressed) {
		color = selectedTangentJointColor;
		return true;
	}
	return false;
}

bool Curve::TangentJoint::unmark() {
	if(!pressed) {
		color = normalTangentJointColor;
		return true;
	}
	return false;
}

void Curve::TangentJoint::setDelegate(SelectableDelegate* selectableDelegate) {
	Selectable::setDelegate(selectableDelegate);
	calcTranslation();
}

} /* namespace thesis */
