#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>
#include <fstream>

#include "shader.hpp"

namespace thesis {
Shader::Shader(const char* fileName) :
	m_shaders(),
	m_uniforms() {
	m_program = glCreateProgram();
	m_shaders = { createShader(loadShader(std::string(fileName) + ".vs"), GL_VERTEX_SHADER),
		createShader(loadShader(std::string(fileName) + ".fs"), GL_FRAGMENT_SHADER) };

	for (uint m_shader : m_shaders)
		glAttachShader(m_program, m_shader);

	glLinkProgram(m_program);
	checkShaderError(m_program, GL_LINK_STATUS, true, "Error linking shader program");

	glValidateProgram(m_program);
	checkShaderError(m_program, GL_LINK_STATUS, true, "Invalid shader program");
}

Shader::~Shader() {
	for (auto&& m_shader : m_shaders) {
		glDetachShader(m_program, m_shader);
		glDeleteShader(m_shader);
	}
	glDeleteProgram(m_program);
}

std::string Shader::loadShader(const std::string& fileName) {
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
		while (file.good()) {
			std::getline(file, line);
			output.append(line + "\n");
		}
	else
		std::cerr << "Unable to load shader: " << fileName << std::endl;

	file.close();

	return output;
}

void Shader::checkShaderError(uint shader, uint flag, bool isProgram, const std::string& errorMessage) {
	GLint success = 0U;
	uint sizeError = 1024U;

	std::vector<char> error(sizeError, (char)0);

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE) {
		if (isProgram)
			glGetProgramInfoLog(shader, sizeError, NULL, error.data());
		else
			glGetShaderInfoLog(shader, sizeError, NULL, error.data());

		std::cerr << errorMessage << ": '" << error.data() << "'" << std::endl;
	}
}

uint Shader::createShader(const std::string& text, uint type) {
	GLuint shader = glCreateShader(type);

	if (shader == 0)
		std::cerr << "Error compiling shader type " << type << std::endl;

	const GLchar* p[1];
	p[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, p, lengths);
	glCompileShader(shader);

	checkShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");

	return shader;
}

} /* namespace thesis */