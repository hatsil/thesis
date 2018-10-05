#define GLEW_STATIC
#include <GL/glew.h>

#include "cubicSplineShader.hpp"

namespace thesis {
CubicSplineShader::CubicSplineShader(): Shader("./res/shaders/cubicSplineShader") {
	m_uniforms.push_back(glGetUniformLocation(m_program, "f"));
	m_uniforms.push_back(glGetUniformLocation(m_program, "color"));
}

CubicSplineShader::~CubicSplineShader() {}

void CubicSplineShader::update(const glm::mat4x2& f, const glm::vec3& color) const {
	glUseProgram(m_program);
	glUniformMatrix4x2fv(m_uniforms[0], 1, GL_FALSE, &f[0][0]);
	glUniform3fv(m_uniforms[1], 1, &color[0]);
}

void CubicSplineShader::update(const glm::vec4& fx, const glm::vec4& fy, const glm::vec3& color) const {
	update(convert(fx, fy), color);
}

} /* namespace thesis */