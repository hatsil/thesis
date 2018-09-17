/*
 * pressable.hpp
 *
 *  Created on: 13 Sep 2018
 *      Author: hatsil
 */

#pragma once

#include "defs.hpp"
#include "drawable.hpp"

namespace thesis {

class Button;
struct PressablePtrComp;

class Pressable: public Drawable {
public:
	Pressable(uint pickingColor);
	virtual ~Pressable();

	virtual void press() = 0;
	virtual void release() = 0;
	virtual void deliverPress(double xpos, double ypos);
	virtual void drawForPicking() const = 0;

private:
	uint pickingColor;

	//friends:
	friend Button;
	friend PressablePtrComp;
};

struct PressablePtrComp {
	using is_transparent = uint;
	bool operator()(Pressable* const  & lhs, Pressable* const & rhs) const;
	bool operator()(Pressable* const  & lhs, const uint& rhs) const;
	bool operator()(const uint& lhs, Pressable* const & rhs) const;
};

} /* namespace thesis */
