#pragma once

#include <vector>

#include "texture.hpp"
#include "shaders.hpp"

namespace thesis {
	class TexMesh {
	public:
		TexMesh(const TexShader& shader);
		virtual ~TexMesh();

		void draw(float darkness) const;

	private:
		const TexShader& shader;
		std::vector<uint> m_vertexArrayBuffers;
		uint m_vertexArrayObject;
	};
} /* namespace thesis */