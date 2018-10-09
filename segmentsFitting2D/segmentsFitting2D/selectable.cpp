/*
 * pressable.cpp
 *
 *  Created on: 13 Sep 2018
 *      Author: hatsil
 */

#include "selectable.hpp"
#include "selectableDelegate.hpp"

namespace thesis {
static uint pickingColorSingleton = 1;

Selectable::Selectable():
	Drawable(),
	pickingColor(pickingColorSingleton),
	pickingColorVec(convertPickingColor(pickingColorSingleton)),
	selectableDelegate(nullptr) {
		++pickingColorSingleton;
	}

Selectable::~Selectable() {}

void Selectable::leftPosition(double, double) {}

void Selectable::resign() {}

void Selectable::rightPress() {}

void Selectable::rightRelease() {}

void Selectable::rightPosition(double, double) {}

void Selectable::middlePress() {}

void Selectable::middleRelease() {}

bool Selectable::mark() {
	return false;
}

bool Selectable::unmark() {
	return false;
}

bool Selectable::isRemovable() const {
	return false;
}

void Selectable::position(double, double) {}

void Selectable::setDelegate(SelectableDelegate* selectableDelegate) {
	this->selectableDelegate = selectableDelegate;
	selectableDelegate->addSelectable(this);
}

bool SelectablePtrComp::operator()(Selectable* const & lhs, Selectable* const & rhs) const {
	return lhs->pickingColor < rhs->pickingColor;
}

bool SelectablePtrComp::operator()(Selectable* const & lhs, const uint& rhs) const {
	return lhs->pickingColor < rhs;
}

bool SelectablePtrComp::operator()(const uint& lhs, Selectable* const & rhs) const {
	return lhs < rhs->pickingColor;
}

} /* namespace thesis */
