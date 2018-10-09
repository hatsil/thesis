#include "button.hpp"
#include "buttonDelegate.hpp"

#include <glm/glm.hpp>

namespace thesis {
Button::Button(const char* fileName):
	Selectable(),
	buttonDelegate(nullptr),
	relatives(),
	texture(fileName),
	marked(false),
	needRelease(true) {
	relatives.insert(this);
}

Button::~Button() {}

void Button::draw() const {
	texture.bind();
	texMesh().draw(marked ? .5f : .0f);
}

void Button::drawForPicking() const {
	squareMesh().draw(glm::mat4(1), pickingColorVec);
}

void Button::leftPress(Selectable* prev) {
	if(!isRelative(prev))
		needRelease = true;

	marked = true;
	selectableDelegate->setDraw();
}

void Button::leftRelease() {
	if(selectableDelegate->getSelectable() == this && needRelease) {
		needRelease = false;
		buttonOperation();
		selectableDelegate->setDrawForPicking();
	} else {
		marked = false;
		selectableDelegate->setDraw();
	}
}

void Button::resign() {
	marked = false;
}

bool Button::mark() {
	if(!marked) {
		marked = true;
		return true;
	}
	return false;
}

bool Button::unmark() {
	marked = false;
	return true;
}

void Button::setDelegate(ButtonDelegate* buttonDelegate) {
	this->buttonDelegate = buttonDelegate;
	Selectable::setDelegate(buttonDelegate);
	setRelatives();
}

const TexMesh& Button::texMesh() const {
	return selectableDelegate->getTexMesh();
}

const SquareMesh& Button::squareMesh() const {
	return selectableDelegate->getSquareMesh();
}

bool Button::isRelative(Selectable* selectable) const {
	return relatives.find(selectable) != relatives.cend();
}

} /* namespace thesis */
