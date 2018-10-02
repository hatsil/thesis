#include "linePlate.hpp"
#include "selectableDelegate.hpp"
#include "linePlateDelegate.hpp"

namespace thesis {

LinePlate::LinePlate():
	CanvasPlate(),
	pressed(false),
	xpos(0), ypos(0) {}

LinePlate::~LinePlate() {}

void LinePlate::draw() const {
	linePlateDelegate->lineDraw();
}

void LinePlate::leftPress(Selectable*) {
	pressed = true;
	selectableDelegate->getCursorPosition(xpos, ypos);
}

void LinePlate::leftRelease() {
	pressed = false;
	linePlateDelegate->packLine(xpos, ypos);
	selectableDelegate->setDraw();
}

void LinePlate::leftPosition(double xpos, double ypos) {
	if(pressed) {
		linePlateDelegate->setTempLine(this->xpos, this->ypos, xpos, ypos);
		selectableDelegate->setDraw();
	}
}

void LinePlate::setDelegate(LinePlateDelegate* linePlateDelegate) {
	this->linePlateDelegate = linePlateDelegate;
}

void LinePlate::setDelegate(SelectableDelegate* selectableDelegate) {
	Selectable::setDelegate(selectableDelegate);
}

} /* namespace thesis */