#pragma once
class CubicSplineModel
{
public:
	CubicSplineModel();
	virtual ~CubicSplineModel();
};

#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "defs.hpp"

namespace thesis {
struct CubicSplineModel {
	CubicSplineModel(uint numIndices);
	virtual ~CubicSplineModel();

	std::vector<glm::vec4> ts;
	std::vector<uint> indices;
};

} /* namespace thesis */