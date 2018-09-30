#pragma once

#include "canvasPlate.hpp"

namespace thesis {
class DefaultPlateDelegate;
class DefaultPlate: public CanvasPlate {
public:
	DefaultPlate();
	virtual ~DefaultPlate();

	void draw() const override;
	void drawForPicking() const override;

	void setDelegate(DefaultPlateDelegate* defaultPlateDelegate);
	void setDelegate(SelectableDelegate* selectableDelegate) override;

private:
	DefaultPlateDelegate* defaultPlateDelegate;
};

} /* namespace thesis */