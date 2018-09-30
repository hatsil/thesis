#include "controlPlate.hpp"
#include "controlPlateDelegate.hpp"

namespace thesis {
ControlPlate::ControlPlate():
	CanvasPlate() {}

ControlPlate::~ControlPlate() {}

void ControlPlate::draw() const {
	controlPlateDelegate->controlDraw();
}
	
void ControlPlate::drawForPicking() const {
	CanvasPlate::drawForPicking();
	controlPlateDelegate->controlDrawForPicking();
}

void ControlPlate::setDelegate(ControlPlateDelegate* controlPlateDelegate) {
	this->controlPlateDelegate = controlPlateDelegate;
}

void ControlPlate::setDelegate(SelectableDelegate* selectableDelegate) {
	Selectable::setDelegate(selectableDelegate);
}

} /* namespace thesis */