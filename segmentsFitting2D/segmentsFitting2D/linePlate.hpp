#pragma once

#include "selectable.hpp"
#include "canvasPlate.hpp"

namespace thesis {
class LinePlateDelegate;
class LinePlate: public CanvasPlate {
public:
	LinePlate();
	virtual ~LinePlate();

	//MARK: Drawable
	void draw() const override;

	//MARK: Selectable
	void leftPress(Selectable*) override;
	void leftRelease() override;
	void leftPosition(double xpos, double ypos) override;

	void setDelegate(LinePlateDelegate* linePlateDelegate);
	void setDelegate(SelectableDelegate* selectableDelegate) override;

private:
	bool pressed;
	double xpos, ypos;
	LinePlateDelegate* linePlateDelegate;
};

} /* namespace thesis */