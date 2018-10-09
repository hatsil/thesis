/*
 * sketchPlate.hpp
 *
 *  Created on: 8 Oct 2018
 *      Author: hatsil
 */

#pragma once

#include "canvasPlate.hpp"

namespace thesis {
class SketchPlateDelegate;
class SketchPlate: public CanvasPlate {
public:
	SketchPlate();
	virtual ~SketchPlate();

	//MARK: Drawable
	void draw() const override;

	//MARK: Selectable
	void leftPress(Selectable*) override;
	void leftRelease() override;
	void leftPosition(double xpos, double ypos) override;

	void setDelegate(SketchPlateDelegate* sketchPlateDelegate);
	void setDelegate(SelectableDelegate* selectableDelegate) override;



private:
	bool pressed;
	SketchPlateDelegate* sketchPlateDelegate;
};

} /* namespace thesis */
