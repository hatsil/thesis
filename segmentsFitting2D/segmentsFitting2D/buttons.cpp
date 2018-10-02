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

} /* namespace thesis */