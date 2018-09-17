#define GLEW_STATIC
#include <GL/glew.h>

#include "getColorOnPress.hpp"

namespace thesis {
uint getColorOnPress(GLFWwindow* glfwWindow) {
	double xpos, ypos;
	glfwGetCursorPos(glfwWindow, &xpos, &ypos);
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	unsigned char colorData[4];
	glReadPixels((int)xpos, viewport[3] - (int)ypos, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, colorData);
	return (uint)colorData[2] + ((uint)colorData[1] << 8) + ((uint)colorData[0] << 16);

	//mesh init
	//float r = ((int)((color & 0xff0000) >> 16)) / 255.0f;
	//float g = ((int)((color & 0xff00) >> 8)) / 255.0f;
	//float b = ((int)(color & 0xff)) / 255.0f;
	//glm::vec3 colorVec(r, g, b);
	//
	//for (Vertex& vertex : vertices)
	//	vertex.GetColor()[0] = colorVec;
}

} /* namespace thesis */