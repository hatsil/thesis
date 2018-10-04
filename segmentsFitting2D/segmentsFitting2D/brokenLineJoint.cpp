#include "brokenLine.hpp"

namespace thesis {
BrokenLine::Joint::Joint(const glm::vec2& position):
	Removable(),
	position(position),
	deleteParent(false),
	segment(nullptr),
	translation(glm::translate(glm::mat4(1), glm::vec3(position, 0))),
	scale(glm::scale(glm::mat4(1), jointScaleFactor)),
	color(normalJointColor),
	isRipped(false), pressed(false), released(false), moved(false),
	xposPrev(0), yposPrev(0) {}

BrokenLine::Joint::~Joint() {
	if(deleteParent) {
		delete parent;
	}
}

void BrokenLine::Joint::createSegment() {
	if(!parent->isLast(it)) {
		segment = new Segment();
		segment->setParent(parent);
		segment->inserted(it);
	}
}

void BrokenLine::Joint::leftPress(Selectable* prev) {
	parent->leftPress(prev);
	pressed = true;
	released = false;
	moved = false;
	color = selectedJointColor;
	selectableDelegate->getCursorPosition(xposPrev, yposPrev);
}

void BrokenLine::Joint::leftRelease() {
	released = true;
	if(moved) selectableDelegate->setDrawForPicking();
	else selectableDelegate->setDraw();
}

void BrokenLine::Joint::leftPosition(double xpos, double ypos) {
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

void BrokenLine::Joint::resign() {
	parent->resign();
}

void BrokenLine::Joint::middlePress() {
	parent->middlePress();
	pressed = true;
	released = false;
	moved = false;
	color = middlePressedJointColor;
}

void BrokenLine::Joint::middleRelease() {
	parent->middleRelease(this);
	if(!isRipped) {
		released = true;
		color = selectedJointColor;
	}
}

bool BrokenLine::Joint::mark() {
	if(!pressed) {
		color = markedJointColor;
		return true;
	}
	return false;
}

bool BrokenLine::Joint::unmark() {
	if(!pressed) {
		color = normalJointColor;
		return true;
	}
	return false;
}

void BrokenLine::Joint::setDelegate(SelectableDelegate* selectableDelegate) {
	if(segment)
		segment->setDelegate(selectableDelegate);

	Selectable::setDelegate(selectableDelegate);
}

void BrokenLine::Joint::ripMe() {
	isRipped = true;

	if(parent->canTakeDemolitionOwnership()) {
		deleteParent = true;
		parent->forEach([&] (Joint* joint) {
			removableDelegate->addRemovable(joint);
			if(joint->segment)
				removableDelegate->addRipped(joint->segment);
		});
		parent->clear();
	} else {
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

void BrokenLine::Joint::setDelegate(RemovableDelegate* removableDelegate) {
	if(segment)
		segment->setDelegate(removableDelegate);

	Removable::setDelegate(removableDelegate);
}

void BrokenLine::Joint::draw() const {
	if(segment)
		segment->draw();

	if(parent->pressed)
		mesh().draw(translation * scale, color);
}

void BrokenLine::Joint::drawForPicking() const {
	if(segment)
		segment->drawForPicking();

	if(parent->isBold())
		mesh().draw(translation * scale, pickingColorVec);
}

void BrokenLine::Joint::controlDraw() const {
	if(segment)
		segment->controlDraw();

	mesh().draw(translation * scale, color);
}

void BrokenLine::Joint::controlDrawForPicking() const {
	mesh().draw(translation * scale, pickingColorVec);
}

} /* namespace thesis*/