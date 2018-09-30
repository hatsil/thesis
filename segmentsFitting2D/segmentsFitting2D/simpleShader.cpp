#define GLEW_STATIC
#include <GL/glew.h>

#include "simpleShader.hpp"

namespace thesis {
SimpleShader::SimpleShader(): Shader("./res/shaders/simpleShader") {
	m_uniforms.push_back(glGetUniformLocation(m_program, "transformation"));
	m_uniforms.push_back(glGetUniformLocation(m_program, "color"));
}

SimpleShader::~SimpleShader() {}

void SimpleShader::update(const glm::mat4& trans, const glm::vec3& color) const {
	glUseProgram(m_program);
	glUniformMatrix4fv(m_uniforms[0], 1, GL_FALSE, &trans[0][0]);
	glUniform3fv(m_uniforms[1], 1, &color[0]);
}

} /* namespace thesis */