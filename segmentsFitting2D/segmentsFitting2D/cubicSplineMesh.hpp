#pragma once
#include <vector>

#include <glm/glm.hpp>

#include "shaders.hpp"

namespace thesis {
class CubicSplineMesh {
public:
	CubicSplineMesh(const CubicSplineShader& shader);
	virtual ~CubicSplineMesh();

	void draw(const glm::mat4x2& f, const glm::vec3& color) const;
	void draw(const glm::vec4& fx, const glm::vec4& fy, const glm::vec3& color) const;

private:
	const CubicSplineShader& shader;
	std::vector<uint> m_vertexArrayBuffers;
	uint m_vertexArrayObject;

	void draw() const;
};

} /* namespace thesis */
