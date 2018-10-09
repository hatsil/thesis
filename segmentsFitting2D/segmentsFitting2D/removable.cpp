#include "removable.hpp"
#include "removableDelegate.hpp"

namespace thesis {

Removable::Removable():
	Selectable(),
	removableDelegate(nullptr) {}

Removable::~Removable() {}

void Removable::draw() const {}

void Removable::drawForPicking() const {}

bool Removable::isRemovable() const {
	return true;
}

void Removable::setDelegate(RemovableDelegate* removableDelegate) {
	this->removableDelegate = removableDelegate;
}

} /* namespace thesis */
