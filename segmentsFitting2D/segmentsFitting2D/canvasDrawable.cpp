#include "canvasDrawable.hpp"

#include <utility>

namespace thesis {
CanvasDrawable::CanvasDrawable() {}

CanvasDrawable::~CanvasDrawable() {}

void CanvasDrawable::inserted(const std::list<CanvasDrawable*>::iterator& it) {
	this->it = it;
}

void CanvasDrawable::inserted(std::list<CanvasDrawable*>::iterator&& it) {
	this->it = std::move(it);
}

void CanvasDrawable::setDelegate(CanvasDrawableDelegate* canvasDrawableDelegate) {
	this->canvasDrawableDelegate = canvasDrawableDelegate;
}

} /* namespace thesis */