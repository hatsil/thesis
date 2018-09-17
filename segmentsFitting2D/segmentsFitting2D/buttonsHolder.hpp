/*
 * buttonsHolder.hpp
 *
 *  Created on: 14 Sep 2018
 *      Author: hatsil
 */

#pragma once

#include "pressable.hpp"
#include "button.hpp"

#include <set>

namespace thesis {
class Window;
class ButtonsHolder: public Pressable {
public:
	ButtonsHolder(int width, int buttonSize, uint pickingColor, Window& window);
	virtual ~ButtonsHolder();

	void press() override {}
	void release() override {}
	void deliverPress(double xpos, double ypos) override {}
	void drawForPicking() const override {}
	void draw() const override {}

private:
	Window& window;
	int width;
	int height;
	std::set<Button*, PressablePtrComp> buttons;
};

} /* namespace thesis */
