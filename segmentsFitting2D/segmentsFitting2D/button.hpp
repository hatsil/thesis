/*
 * button.hpp
 *
 *  Created on: 12 Sep 2018
 *      Author: hatsil
 */

#pragma once

#include <string>
#include <functional>

#include "texture.hpp"
#include "pressable.hpp"

namespace thesis {

class Button: public Pressable {
public:
	Button(uint pickingColor, const char* texture);
	virtual ~Button();

	

private:
	Texture* texture;
	std::function<void()> pressAction;
};

} /* namespace thesis */

