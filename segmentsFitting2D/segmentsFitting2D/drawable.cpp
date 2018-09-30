/*
 * drawable.cpp
 *
 *  Created on: 13 Sep 2018
 *      Author: hatsil
 */

#include "drawable.hpp"

namespace thesis {

Drawable::Drawable() {}

Drawable::~Drawable() {}

glm::vec3 Drawable::convertPickingColor(uint pickingColor) {
	float r = ((int)((pickingColor & 0xff0000) >> 16)) / 255.0f;
	float g = ((int)((pickingColor & 0xff00) >> 8)) / 255.0f;
	float b = ((int)(pickingColor & 0xff)) / 255.0f;
	return glm::vec3(r, g, b);
}

} /* namespace thesis */