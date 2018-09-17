/*
 * pressable.cpp
 *
 *  Created on: 13 Sep 2018
 *      Author: hatsil
 */

#include "pressable.hpp"

namespace thesis {
Pressable::Pressable(uint pickingColor) :
	pickingColor(pickingColor) {}

Pressable::~Pressable() {}

void Pressable::deliverPress(double xpos, double ypos) {}

bool PressablePtrComp::operator()(Pressable* const  & lhs, Pressable* const & rhs) const {
	return lhs->pickingColor < rhs->pickingColor;
}

bool PressablePtrComp::operator()(Pressable* const  & lhs, const uint& rhs) const {
	return lhs->pickingColor < rhs;
}

bool PressablePtrComp::operator()(const uint& lhs, Pressable* const & rhs) const {
	return lhs < rhs->pickingColor;
}

} /* namespace thesis */
