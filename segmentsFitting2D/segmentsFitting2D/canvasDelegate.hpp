#pragma once

#include "selectableDelegate.hpp"

namespace thesis {
class CanvasDelegate: virtual public SelectableDelegate {
public:
	virtual ~CanvasDelegate() {}

	virtual void fixOffsetCanvas(double& xpos, double& ypos) const = 0;
};

} /* namespace thesis */