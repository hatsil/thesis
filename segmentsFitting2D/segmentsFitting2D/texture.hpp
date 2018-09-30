/*
 * texture.hpp
 *
 *  Created on: 12 Sep 2018
 *      Author: hatsil
 */

#pragma once

#include "defs.hpp"

namespace thesis {

class Texture {
public:
	Texture(const char* fileName);
	virtual ~Texture();

	void bind() const;

private:
	uint m_texture;
};

} /* namespace thesis */
