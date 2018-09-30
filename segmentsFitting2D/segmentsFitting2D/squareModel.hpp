#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "defs.hpp"

namespace thesis {
struct SquareModel {
	SquareModel();
	virtual ~SquareModel();

	std::vector<glm::vec2> positions;
	std::vector<glm::vec2> texCoords;
	std::vector<uint> indices;
};

} /* namespace thesis */

