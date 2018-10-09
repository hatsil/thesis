/*
 * sketchPlate.cpp
 *
 *  Created on: 8 Oct 2018
 *      Author: hatsil
 */

#include "sketchPlate.hpp"
#include "selectableDelegate.hpp"
#include "sketchPlateDelegate.hpp"

namespace thesis {

SketchPlate::SketchPlate():
	CanvasPlate(),
	pressed(false),
	sketchPlateDelegate(nullptr) {}

SketchPlate::~SketchPlate() {}

void SketchPlate::draw() const {
	sketchPlateDelegate->sketchDraw();
}

void SketchPlate::leftPress(Selectable*) {
	pressed = true;
	sketchPlateDelegate->sketchLeftPress();
}

void SketchPlate::leftRelease() {
	pressed = false;
	sketchPlateDelegate->packSketch();
	selectableDelegate->setDraw();
}

void SketchPlate::leftPosition(double xpos, double ypos) {
	if(pressed) {
		sketchPlateDelegate->sketchLeftPosition(xpos, ypos);
		selectableDelegate->setDraw();
	}
}

void SketchPlate::setDelegate(SketchPlateDelegate* sketchPlateDelegate) {
	this->sketchPlateDelegate = sketchPlateDelegate;
}

void SketchPlate::setDelegate(SelectableDelegate* selectableDelegate) {
	Selectable::setDelegate(selectableDelegate);
}

} /* namespace thesis */

