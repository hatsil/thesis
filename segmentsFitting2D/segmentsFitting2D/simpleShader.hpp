#pragma once

#include <glm/glm.hpp>

#include "shader.hpp"

namespace thesis {
class SimpleShader: public Shader {
public:
	SimpleShader();
	virtual ~SimpleShader();

	void update(const glm::mat4& translation, const glm::vec3& color) const;
};
} /* namespace thesis */
