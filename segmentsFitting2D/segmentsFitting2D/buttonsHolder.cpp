/*
 * buttonsHolder.cpp
 *
 *  Created on: 14 Sep 2018
 *      Author: hatsil
 */

#include "buttonsHolder.hpp"
#include "window.hpp"
#include "executor.hpp"

namespace thesis {

ButtonsHolder::ButtonsHolder(int width, int buttonSize, uint pickingColor, Window& window):
	Pressable(pickingColor),
	window(window),
	width(width),
	height(buttonSize + buttonSize/5),
	buttons() {
	// TODO Auto-generated constructor stub
}

ButtonsHolder::~ButtonsHolder() {
	// TODO Auto-generated destructor stub
}

} /* namespace thesis */
