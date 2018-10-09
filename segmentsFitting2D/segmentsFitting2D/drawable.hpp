/*
 * drawable.hpp
 *
 *  Created on: 13 Sep 2018
 *      Author: hatsil
 */

#pragma once

#include "defs.hpp"

#include <glm/glm.hpp>

namespace thesis {

class Drawable {
public:
	Drawable();
	virtual ~Drawable();

	virtual void draw() const = 0;
	virtual void drawForPicking() const = 0;

	static glm::vec3 convertPickingColor(uint pickingColor);
};

} /* namespace thesis */
