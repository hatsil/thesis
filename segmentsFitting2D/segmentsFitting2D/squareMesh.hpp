#pragma once
#include <vector>

#include <glm/glm.hpp>

#include "shaders.hpp"

namespace thesis {
	class SquareMesh {
	public:
		SquareMesh(const SimpleShader& shader);
		virtual ~SquareMesh();

		void draw(const glm::mat4& trans, const glm::vec3& color) const;

	private:
		const SimpleShader& shader;
		std::vector<uint> m_vertexArrayBuffers;
		uint m_vertexArrayObject;
	};
} /* namespace thesis */
