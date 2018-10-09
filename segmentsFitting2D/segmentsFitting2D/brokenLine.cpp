#include "brokenLine.hpp"
#include "canvasDrawableDelegate.hpp"

namespace thesis {
BrokenLine::BrokenLine(const std::list<glm::vec2>& points) :
	CanvasDrawable(),
	joints(),
	color(defaultBrokenLineColor),
	pressed(false), released(true),
	moved(false), marked(false),
	xposPrev(0), yposPrev(0),
	selectableDelegate(nullptr),
	removableDelegate(nullptr) {
	for(const glm::vec2& point : points) {
		Joint* joint = new Joint(point);
		joint->setParent(this);
		joint->inserted(joints.insert(joints.cend(), joint));
	}

	forEach([](Joint* joint) {
		joint->createSegment();
	});
}

BrokenLine::~BrokenLine() {
	forEach([] (Joint* joint) {
		joint->destroySegment();
		delete joint;
	});
}

void BrokenLine::defaultDraw() const {
	forEach([](const Joint* joint) {
		joint->draw();
	});
}

void BrokenLine::defaultDrawForPicking() const {
	forEach([](const Joint* joint) {
		joint->drawForPicking();
	});
}

void BrokenLine::controlDraw() const {
	forEach([](const Joint* joint) {
		joint->controlDraw();
	});
}

void BrokenLine::controlDrawForPicking() const {
	forEach([](const Joint* joint) {
		joint->controlDrawForPicking();
	});
}

void BrokenLine::setDelegate(CanvasDrawableDelegate* canvasDrawableDelegate) {
	CanvasDrawable::setDelegate(canvasDrawableDelegate);
}

void BrokenLine::setDelegate(SelectableDelegate* selectableDelegate) {
	this->selectableDelegate = selectableDelegate;
	forEach([=](Joint* joint) {
		joint->setDelegate(selectableDelegate);
	});
}

void BrokenLine::setDelegate(RemovableDelegate* removableDelegate) {
	this->removableDelegate = removableDelegate;
	forEach([=](Joint* joint) {
		joint->setDelegate(removableDelegate);
	});
}

void BrokenLine::leftPress(Selectable* prev) {
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

void BrokenLine::leftRelease() {
	released = true;
	if(moved) selectableDelegate->setDrawForPicking();
	else selectableDelegate->setDraw();
}

void BrokenLine::leftPosition(double xpos, double ypos) {
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

void BrokenLine::resign() {
	pressed = marked = moved = false;
	color = defaultBrokenLineColor;
	setDefaultState();
	selectableDelegate->setDrawForPicking();
}

void BrokenLine::middlePress() {
	pressed = true;
	released = false;
	moved = false;
	color = middlePressedColor;
	setDefaultState();
	selectableDelegate->setDrawForPicking();
}

void BrokenLine::middleRelease(Removable* child) {
	color = defaultBrokenLineColor;
	released = true;
	if(selectableDelegate->getSelectable() == child) {
		child->ripMe();
		return;
	}
	selectableDelegate->setDrawForPicking();
}

bool BrokenLine::mark() {
	if(!pressed) {
		marked = true;
		setDefaultState();
		return true;
	}
	return false;
}

bool BrokenLine::unmark() {
	if(!pressed) {
		marked = false;
		return true;
	}
	return false;
}

} /* namespace thesis */
