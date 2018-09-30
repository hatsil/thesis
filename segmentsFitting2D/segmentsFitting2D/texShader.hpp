#pragma once

#include "shader.hpp"

namespace thesis {
	class TexShader : public Shader {
	public:
		TexShader();
		virtual ~TexShader();

		void update(float darkness) const;
	};
} /* namespace thesis */

