#pragma once
#include <vector>

#include <glm/glm.hpp>

#include "shaders.hpp"

namespace thesis {
	class LineMesh {
	public:
		LineMesh(const SimpleShader& shader, const std::vector<glm::vec2>& points);
		virtual ~LineMesh();

		void draw(const glm::mat4& trans, const glm::vec3& color) const;

	private:
		const SimpleShader& shader;
		std::vector<uint> m_vertexArrayBuffers;
		uint m_vertexArrayObject;
		uint numIndices;
	};
} /* namespace thesis */
