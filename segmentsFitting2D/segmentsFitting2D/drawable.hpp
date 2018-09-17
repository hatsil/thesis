/*
 * drawable.hpp
 *
 *  Created on: 13 Sep 2018
 *      Author: hatsil
 */

#pragma once

namespace thesis {

class Drawable {
public:
	Drawable();
	virtual ~Drawable();

	virtual void draw() const = 0;
};

} /* namespace thesis */
