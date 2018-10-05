#include "curve.hpp"
#include "canvasDrawableDelegate.hpp"

namespace thesis {
Curve::Curve(const glm::vec2& q1, const glm::vec2& q2):
	CanvasDrawable(),
	joints() {
	Joint* arr[] = { new Joint(q1), new Joint(q2) };
	for(Joint* joint : arr) {
		joint->setParent(this);
		joint->inserted(joints.insert(joints.cend(), joint));
	}

	forEach([](Joint* joint) {
		joint->createSegment();
	});
}

Curve::~Curve() {
	forEach([](Joint* joint) {
		joint->destroySegment();
		delete joint;
	});
}

void Curve::defaultDraw() const {
	forEach([](const Joint* joint) {
		joint->draw();
	});
}

void Curve::defaultDrawForPicking() const {
	forEach([](const Joint* joint) {
		joint->drawForPicking();
	});
}

void Curve::controlDraw() const {
	forEach([](const Joint* joint) {
		joint->controlDraw();
	});
}

void Curve::controlDrawForPicking() const {
	forEach([](const Joint* joint) {
		joint->controlDrawForPicking();
	});
}

void Curve::setDelegate(CanvasDrawableDelegate* canvasDrawableDelegate) {
	CanvasDrawable::setDelegate(canvasDrawableDelegate);
}

void Curve::setDelegate(SelectableDelegate* selectableDelegate) {
	this->selectableDelegate = selectableDelegate;
	forEach([=](Joint* joint) {
		joint->setDelegate(selectableDelegate);
	});
}

void Curve::setDelegate(RemovableDelegate* removableDelegate) {
	this->removableDelegate = removableDelegate;
	forEach([=](Joint* joint) {
		joint->setDelegate(removableDelegate);
	});
}

void Curve::leftPress(Selectable* prev) {
	pressed = true;
	released = false;
	moved = false;
	setDefaultState();
	selectableDelegate->getCursorPosition(xposPrev, yposPrev);
	if(isRelative(prev))
		selectableDelegate->setDraw();
	else {
		canvasDrawableDelegate->moveToFront(it);
		selectableDelegate->setDrawForPicking();
	}
}

void Curve::leftRelease() {
	released = true;
	if(moved) selectableDelegate->setDrawForPicking();
	else selectableDelegate->setDraw();
}

void Curve::leftPosition(double xpos, double ypos) {
	if(pressed && !released) {
		moved = true;
		glm::vec2 q1 = convertPos(xposPrev, yposPrev);
		glm::vec2 q2 = convertPos(xpos, ypos);
		xposPrev = xpos;
		yposPrev = ypos;

		glm::vec2 dir = q2 - q1;

		forEach([&](Joint* joint) {
			joint->addOffset(dir);
		});

		selectableDelegate->setDraw();
	}
}

void Curve::resign() {
	pressed = marked = moved = false;
	color = defaultLineColor;
	setDefaultState();
	selectableDelegate->setDrawForPicking();
}

void Curve::middlePress() {
	pressed = true;
	released = false;
	moved = false;
	color = middlePressedColor;
	setDefaultState();
	selectableDelegate->setDrawForPicking();
}

void Curve::middleRelease(Removable* child) {
	color = defaultLineColor;
	released = true;
	if(selectableDelegate->getSelectable() == child) {
		child->ripMe();
		return;
	}
	selectableDelegate->setDrawForPicking();
}

bool Curve::mark() {
	if(!pressed) {
		marked = true;
		setDefaultState();
		return true;
	}
	return false;
}

bool Curve::unmark() {
	if(!pressed) {
		marked = false;
		return true;
	}
	return false;
}

} /* namespace thesis */
