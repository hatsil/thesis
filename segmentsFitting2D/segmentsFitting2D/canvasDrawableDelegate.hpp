#pragma once

#include "canvasDrawable.hpp"

namespace thesis {
class CanvasDrawableDelegate {
public:
	virtual ~CanvasDrawableDelegate() {}

	virtual void remove(const std::list<CanvasDrawable*>::iterator& it) = 0;
	virtual void moveToFront(std::list<CanvasDrawable*>::iterator& it) = 0;
};

} /* namespace thesis */