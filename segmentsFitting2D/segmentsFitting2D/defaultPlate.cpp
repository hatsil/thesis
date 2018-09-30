#include "defaultPlate.hpp"
#include "defaultPlateDelegate.hpp"

namespace thesis {
DefaultPlate::DefaultPlate():
	CanvasPlate() {}

DefaultPlate::~DefaultPlate() {}

void DefaultPlate::draw() const {
	defaultPlateDelegate->defaultDraw();
}
	
void DefaultPlate::drawForPicking() const {
	CanvasPlate::drawForPicking();
	defaultPlateDelegate->defaultDrawForPicking();
}

void DefaultPlate::setDelegate(DefaultPlateDelegate* defaultPlateDelegate) {
	this->defaultPlateDelegate = defaultPlateDelegate;
}

void DefaultPlate::setDelegate(SelectableDelegate* selectableDelegate) {
	Selectable::setDelegate(selectableDelegate);
}

} /* namespace thesis */