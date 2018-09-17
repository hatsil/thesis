#define GLEW_STATIC
#include <GL/glew.h>

#include "texShader.hpp"

namespace thesis {
TexShader::TexShader() : Shader("./res/shaders/texShader") {}

TexShader::~TexShader() {}

void TexShader::update() const {
	glUseProgram(m_program);
}

} /* namespace thesis */