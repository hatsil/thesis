#pragma once

#include "selectable.hpp"
#include "canvasPlate.hpp"

namespace thesis {
class CurvePlateDelegate;
class CurvePlate: public CanvasPlate {
public:
	CurvePlate();
	virtual ~CurvePlate();

	//MARK: Drawable
	void draw() const override;

	//MARK: Selectable
	void leftPress(Selectable*) override;
	void leftRelease() override;
	void leftPosition(double xpos, double ypos) override;

	void setDelegate(CurvePlateDelegate* curvePlateDelegate);
	void setDelegate(SelectableDelegate* selectableDelegate) override;

private:
	bool pressed;
	double xpos, ypos;
	CurvePlateDelegate* curvePlateDelegate;
};

} /* namespace thesis */
