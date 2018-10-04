#pragma once

#include "selectable.hpp"
#include "canvasPlate.hpp"

namespace thesis {
class BrokenLinePlateDelegate;
class BrokenLinePlate : public CanvasPlate {
public:
	BrokenLinePlate();
	virtual ~BrokenLinePlate();

	//MARK: Drawable
	void draw() const override;

	//MARK: Selectable
	void leftPress(Selectable*) override;
	void leftRelease() override;
	void rightPress() override;
	void resign() override;
	void position(double xpos, double ypos) override;

	void setDelegate(BrokenLinePlateDelegate* brokenLinePlateDelegate);
	void setDelegate(SelectableDelegate* selectableDelegate) override;

private:
	BrokenLinePlateDelegate* brokenLinePlateDelegate;
};

} /* namespace thesis */

