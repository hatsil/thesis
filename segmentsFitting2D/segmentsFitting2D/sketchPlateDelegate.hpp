/*
 * sketchPlateDelegate.hpp
 *
 *  Created on: 8 Oct 2018
 *      Author: hatsil
 */

#pragma once

namespace thesis {
class SketchPlateDelegate {
public:
	virtual ~SketchPlateDelegate() {}

	virtual void sketchDraw() = 0;
	virtual void sketchLeftPress() = 0;
	virtual void sketchLeftPosition(double xpos, double ypos) = 0;
	virtual void packSketch() = 0;
};

} /* namespace thesis */

