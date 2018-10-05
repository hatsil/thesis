#pragma once

#include <glm/glm.hpp>

#include "shader.hpp"

namespace thesis {
class CubicSplineShader: public Shader {
public:
	CubicSplineShader();
	virtual ~CubicSplineShader();

	void update(const glm::mat4x2& f, const glm::vec3& color) const;
	void update(const glm::vec4& fx, const glm::vec4& fy, const glm::vec3& color) const;

	static inline glm::mat4x2 convert(const glm::vec4& fx, const glm::vec4& fy) {
		return glm::mat4x2({ fx.x, fy.x }, { fx.y, fy.y }, { fx.z, fy.z }, { fx.w, fy.w });
	}
};
} /* namespace thesis */
