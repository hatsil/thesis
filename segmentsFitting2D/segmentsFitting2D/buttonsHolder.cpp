/*
 * buttonsHolder.cpp
 *
 *  Created on: 14 Sep 2018
 *      Author: hatsil
 */

#include "buttonsHolder.hpp"
#include "buttonDelegate.hpp"

#include "buttons.hpp"

#include "globalVars.hpp"

#include <glm/glm.hpp>

namespace thesis {
ButtonsHolder::ButtonsHolder(size_t width, size_t buttonSize):
	width(width),
	height(buttonSize + buttonSize / (size_t)5),
	controlPressed(false),
	buttons(),
	buttonDelegate(nullptr) {
	buttons = {new LineButton, new BrokenLineButton, new CurveButton, new SketchButton, new DefaultButton};
}

ButtonsHolder::~ButtonsHolder() {
	forEach([] (Button* button) {
		delete button;
	});
}

void ButtonsHolder::draw() const {
	mesh().draw(glm::mat4(1), buttonsHolderBackgroundColor);
	forEach([&] (int i, Button* button) {
		buttonDelegate->buttonViewport(i);
		button->draw();
	});
}

void ButtonsHolder::drawForPicking() const {
	if(controlPressed)
		return;
	forEach([&](int i, Button* button) {
		buttonDelegate->buttonViewport(i);
		button->drawForPicking();
	});
}

void ButtonsHolder::controlPress() {
	controlPressed = true;
}

void ButtonsHolder::controlRelease() {
	controlPressed = false;
}

size_t ButtonsHolder::getWidth() const {
	return width;
}

size_t ButtonsHolder::getHeight() const {
	return height;
}

void ButtonsHolder::setDelegate(ButtonDelegate* buttonDelegate) {
	this->buttonDelegate = buttonDelegate;
	forEach([=] (Button* button) {
		button->setDelegate(buttonDelegate);
	});
}

void ButtonsHolder::forEach(const std::function<void(int, Button*)>& func) const {
	for(int i = 0; i < (int)buttons.size(); ++i)
		func(i, buttons[i]);
}

void ButtonsHolder::forEach(const std::function<void(Button*)>& func) const {
	for(Button* button : buttons)
		func(button);
}

const SquareMesh& ButtonsHolder::mesh() const {
	return buttonDelegate->getSquareMesh();
}

} /* namespace thesis */


