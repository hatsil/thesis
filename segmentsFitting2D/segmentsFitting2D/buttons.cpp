#include "buttons.hpp"
#include "buttonDelegate.hpp"

namespace thesis {
DefaultButton::DefaultButton():
	Button("./res/textures/buttons/default.jpg") {}

DefaultButton::~DefaultButton() {}

void DefaultButton::buttonOperation(){
	buttonDelegate->setDefaultPlate();
}

LineButton::LineButton():
	Button("./res/textures/buttons/line.jpg") {}

LineButton::~LineButton() {}

	
void LineButton::buttonOperation() {
	buttonDelegate->setLinePlate();
}

} /* namespace thesis */