#define GLEW_STATIC
#include <GL/glew.h>

#include "texShader.hpp"

namespace thesis {
TexShader::TexShader() : Shader("./res/shaders/texShader") {
	m_uniforms.push_back(glGetUniformLocation(m_program, "darkness"));
}

TexShader::~TexShader() {}

void TexShader::update(float darkness) const {
	glUseProgram(m_program);
	glUniform1f(m_uniforms[0], darkness);
}

} /* namespace thesis */