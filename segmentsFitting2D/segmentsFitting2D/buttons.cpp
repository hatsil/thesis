#include "buttons.hpp"
#include "buttonDelegate.hpp"

namespace thesis {
//MARK: DefautlButton
DefaultButton::DefaultButton():
	Button("./res/textures/buttons/default.jpg") {}

DefaultButton::~DefaultButton() {}

void DefaultButton::buttonOperation() {
	buttonDelegate->setDefaultPlate();
}

void DefaultButton::setRelatives() {
	relatives.insert(buttonDelegate->getDefaultPlate());
	relatives.insert(buttonDelegate->getControlPlate());
}


//MARK: LineButton
LineButton::LineButton():
	Button("./res/textures/buttons/line.jpg") {}

LineButton::~LineButton() {}

	
void LineButton::buttonOperation() {
	buttonDelegate->setLinePlate();
}

void LineButton::setRelatives() {
	relatives.insert(buttonDelegate->getLinePlate());
	relatives.insert(buttonDelegate->getControlPlate());
}


//MARK: BrokenLineButton
BrokenLineButton::BrokenLineButton() :
	Button("./res/textures/buttons/broken.jpg") {}

BrokenLineButton::~BrokenLineButton() {}


void BrokenLineButton::buttonOperation() {
	buttonDelegate->setBrokenLinePlate();
}

void BrokenLineButton::setRelatives() {
	relatives.insert(buttonDelegate->getBrokenLinePlate());
	relatives.insert(buttonDelegate->getControlPlate());
}


//MARK: CurveButton
CurveButton::CurveButton():
	Button("./res/textures/buttons/curve.jpg") {}

CurveButton::~CurveButton() {}


void CurveButton::buttonOperation() {
	buttonDelegate->setCurvePlate();
}

void CurveButton::setRelatives() {
	relatives.insert(buttonDelegate->getCurvePlate());
	relatives.insert(buttonDelegate->getControlPlate());
}


//MARK: CurveButton
SketchButton::SketchButton():
	Button("./res/textures/buttons/pencil.jpg") {}

SketchButton::~SketchButton() {}


void SketchButton::buttonOperation() {
	buttonDelegate->setSketchPlate();
}

void SketchButton::setRelatives() {
	relatives.insert(buttonDelegate->getSketchPlate());
	relatives.insert(buttonDelegate->getControlPlate());
}

} /* namespace thesis */
