/*
 * canvas.cpp
 *
 *  Created on: 14 Sep 2018
 *      Author: hatsil
 */

#include "canvas.hpp"
#include "window.hpp"

namespace thesis {

Canvas::Canvas(int width, int height, uint pickingColor, Window& window):
	Pressable(pickingColor),
	width(width),
	height(height),
	window(window) {
	// TODO Auto-generated constructor stub

}

Canvas::~Canvas() {
	// TODO Auto-generated destructor stub
}

} /* namespace thesis */
