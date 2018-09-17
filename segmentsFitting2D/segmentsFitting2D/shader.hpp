#pragma once

#include "defs.hpp"

#include <string>
#include <vector>

namespace thesis {

class SimpleShader;
class TexShader;

class Shader {
public:
	Shader(const char* fileName);
	virtual ~Shader();
	
private:
	static std::string loadShader(const std::string& fileName);
		
	static void checkShaderError(uint shader,
		uint flag,
		bool isProgram,
		const std::string& errorMessage);

	static uint createShader(const std::string& text, uint type);

	uint m_program;
	std::vector<uint> m_shaders;
	std::vector<uint> m_uniforms;

	//friends:
	friend SimpleShader;
	friend TexShader;
};

} /* namespace thesis */