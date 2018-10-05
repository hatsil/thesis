#include "curve.hpp"

namespace thesis {
Curve::Joint::Joint(const glm::vec2& position):
	Removable(),
	position(position),
	deleteParent(false),
	segment(nullptr),
	translation(glm::translate(glm::mat4(1), glm::vec3(position, 0))),
	color(normalJointColor),
	isRipped(false), pressed(false), released(false), moved(false),
	xposPrev(0), yposPrev(0) {
	tj = new TangentJoint;
	tj->setParent(this);
}

Curve::Joint::~Joint() {
	delete tj;
	if(deleteParent) {
		delete parent;
	}
}

void Curve::Joint::createSegment() {
	if(!parent->isLast(it)) {
		segment = new Segment();
		segment->setParent(parent);
		segment->inserted(it);
	}
}

void Curve::Joint::leftPress(Selectable*) {
	parent->leftPress(nullptr);
	pressed = true;
	released = false;
	moved = false;
	color = selectedJointColor;
	selectableDelegate->getCursorPosition(xposPrev, yposPrev);
}

void Curve::Joint::leftRelease() {
	released = true;
	if(moved) selectableDelegate->setDrawForPicking();
	else selectableDelegate->setDraw();
}

void Curve::Joint::leftPosition(double xpos, double ypos) {
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

void Curve::Joint::resign() {
	parent->resign();
}

void Curve::Joint::middlePress() {
	parent->middlePress();
	pressed = true;
	released = false;
	moved = false;
	color = middlePressedJointColor;
}

void Curve::Joint::middleRelease() {
	if(selectableDelegate->getSelectable() == tj) {
		parent->color = defaultLineColor;
		parent->released = true;
		ripMe();
	} else {
		parent->middleRelease(this);
		if(!isRipped) {
			released = true;
			color = selectedJointColor;
		}
	}
}

bool Curve::Joint::mark() {
	if(!pressed) {
		color = markedJointColor;
		return true;
	}
	return false;
}

bool Curve::Joint::unmark() {
	if(!pressed) {
		color = normalJointColor;
		return true;
	}
	return false;
}

void Curve::Joint::setDelegate(SelectableDelegate* selectableDelegate) {
	if(segment)
		segment->setDelegate(selectableDelegate);

	tj->setDelegate(selectableDelegate);
	Selectable::setDelegate(selectableDelegate);
}

void Curve::Joint::ripMe() {
	isRipped = true;

	if(parent->canTakeDemolitionOwnership()) {
		deleteParent = true;
		parent->forEach([&](Joint* joint) {
			selectableDelegate->removeSelectable(joint->tj);
			removableDelegate->addRipped(joint);
			if(joint->segment)
				removableDelegate->addRipped(joint->segment);
		});
		parent->clear();
	} else {
		selectableDelegate->removeSelectable(tj);
		removableDelegate->addRipped(this);
		parent->remove(this);
		if(segment) {
			removableDelegate->addRipped(segment);
			parent->remove(segment);
		} else { //last link
			Joint* prev = *std::prev(it);
			removableDelegate->addRipped(prev->segment);
			parent->remove(prev->segment);
			prev->segment = nullptr;
		}
		parent->remove(it);
	}

	selectableDelegate->setClearRemovables();
}

void Curve::Joint::setDelegate(RemovableDelegate* removableDelegate) {
	if(segment)
		segment->setDelegate(removableDelegate);

	Removable::setDelegate(removableDelegate);
}

void Curve::Joint::draw() const {
	if(segment)
		segment->draw();

	if(parent->pressed)
		mesh().draw(translation * scale(), color);

	if(pressed)
		tj->draw();
}

void Curve::Joint::drawForPicking() const {
	if(segment)
		segment->drawForPicking();

	if(parent->isBold())
		mesh().draw(translation * scale(), pickingColorVec);

	if(pressed)
		tj->drawForPicking();
}

void Curve::Joint::controlDraw() const {
	if(segment)
		segment->controlDraw();

	mesh().draw(translation * scale(), color);
	tj->draw();
}

void Curve::Joint::controlDrawForPicking() const {
	mesh().draw(translation * scale(), pickingColorVec);
	tj->drawForPicking();
}

} /* namespace thesis*/