#pragma once

#include "canvasPlate.hpp"

namespace thesis {
class ControlPlateDelegate;
class ControlPlate: public CanvasPlate {
public:
	ControlPlate();
	virtual ~ControlPlate();

	//MARK: Drawable
	void draw() const override;
	void drawForPicking() const override;

	void setDelegate(ControlPlateDelegate* controlPlateDelegate);
	void setDelegate(SelectableDelegate* selectableDelegate) override;

private:
	ControlPlateDelegate* controlPlateDelegate;
};

} /* namespace thesis */
