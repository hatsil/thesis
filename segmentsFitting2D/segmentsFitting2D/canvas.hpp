/*
 * canvas.hpp
 *
 *  Created on: 14 Sep 2018
 *      Author: hatsil
 */

#pragma once

#include "pressable.hpp"

namespace thesis {
class Window;
class Canvas: public Pressable {
public:
	Canvas(int width, int height, uint pickingColor, Window& window);
	virtual ~Canvas();

	void press() override {}
	void release() override {}
	void deliverPress(double xpos, double ypos) override {}
	void drawForPicking() const override {}
	void draw() const override {}



private:
	int width;
	int height;
	Window& window;

	//friends:
	friend Window;

	//private methods:
	void controlPress() {}
	void controlRelease() {}
};

} /* namespace thesis */
