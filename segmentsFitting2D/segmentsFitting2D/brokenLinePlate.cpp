#include "brokenLinePlate.hpp"
#include "selectableDelegate.hpp"
#include "brokenLinePlateDelegate.hpp"

namespace thesis {
BrokenLinePlate::BrokenLinePlate():
	CanvasPlate(),
	brokenLinePlateDelegate(nullptr) {}

BrokenLinePlate::~BrokenLinePlate() {}

void BrokenLinePlate::draw() const {
	brokenLinePlateDelegate->brokenLineDraw();
}

void BrokenLinePlate::leftPress(Selectable*) {
	brokenLinePlateDelegate->brokenLineLeftPress();
}

void BrokenLinePlate::leftRelease() {}

void BrokenLinePlate::rightPress() {
	brokenLinePlateDelegate->brokenLineRightPress();
}

void BrokenLinePlate::resign() {
	brokenLinePlateDelegate->brokenLineResign();
}

void BrokenLinePlate::position(double xpos, double ypos) {
	brokenLinePlateDelegate->brokenLinePosition(xpos, ypos);
}

void BrokenLinePlate::setDelegate(BrokenLinePlateDelegate* brokenLinePlateDelegate) {
	this->brokenLinePlateDelegate = brokenLinePlateDelegate;
}

void BrokenLinePlate::setDelegate(SelectableDelegate* selectableDelegate) {
	Selectable::setDelegate(selectableDelegate);
}

} /* namespace thesis */
