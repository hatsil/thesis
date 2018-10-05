#include "curvePlate.hpp"
#include "selectableDelegate.hpp"
#include "curvePlateDelegate.hpp"

namespace thesis {
CurvePlate::CurvePlate() :
	CanvasPlate(),
	pressed(false),
	xpos(0), ypos(0) {}

CurvePlate::~CurvePlate() {}

void CurvePlate::draw() const {
	curvePlateDelegate->curveDraw();
}

void CurvePlate::leftPress(Selectable*) {
	pressed = true;
	selectableDelegate->getCursorPosition(xpos, ypos);
}

void CurvePlate::leftRelease() {
	pressed = false;
	curvePlateDelegate->packCurve(xpos, ypos);
	selectableDelegate->setDraw();
}

void CurvePlate::leftPosition(double xpos, double ypos) {
	if(pressed) {
		curvePlateDelegate->setTempCurve(this->xpos, this->ypos, xpos, ypos);
		selectableDelegate->setDraw();
	}
}

void CurvePlate::setDelegate(CurvePlateDelegate* curvePlateDelegate) {
	this->curvePlateDelegate = curvePlateDelegate;
}

void CurvePlate::setDelegate(SelectableDelegate* selectableDelegate) {
	Selectable::setDelegate(selectableDelegate);
}

} /* namespace thesis */
