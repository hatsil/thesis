/*
 * button.cpp
 *
 *  Created on: 12 Sep 2018
 *      Author: hatsil
 */

#include "button.hpp"

thesis::Button::Button(uint pickingColor, const char* texture):
Pressable(pickingColor),
texture(0) {}

thesis::Button::~Button() {

	if(texture)
		delete texture;
}


