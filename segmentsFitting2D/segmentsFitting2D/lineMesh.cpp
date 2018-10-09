#define GLEW_STATIC
#include <GL/glew.h>

#include "lineMesh.hpp"

namespace thesis {
static const uint numBuffers = 2U;

LineMesh::LineMesh(const SimpleShader& shader):
		LineMesh(shader, {{0,0}, {1,0}}) {}

LineMesh::LineMesh(const SimpleShader& shader, const std::vector<glm::vec2>& points) :
	shader(shader),
	m_vertexArrayBuffers(numBuffers, 0U),
	numIndices((int)points.size()) {

	glGenVertexArrays(1U, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	glGenBuffers(numBuffers, m_vertexArrayBuffers.data());

	uint i = glGetAttribLocation(shader.m_program, "position");
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[0U]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points[0]) * points.size(), &points[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(i);
	glVertexAttribPointer(i, 2, GL_FLOAT, GL_FALSE, 0, 0);

	std::vector<uint> indices(points.size());
	uint j = 0;
	for(uint& index : indices)
		index = j++;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[1U]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0U);
}

LineMesh::~LineMesh() {
	glDeleteBuffers(numBuffers, m_vertexArrayBuffers.data());
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void LineMesh::draw(const glm::mat4& trans, const glm::vec3& color) const {
	shader.update(trans, color);
	glBindVertexArray(m_vertexArrayObject);
	glDrawElementsBaseVertex(GL_LINE_STRIP, numIndices, GL_UNSIGNED_INT, 0, 0);
	glBindVertexArray(0U);
}

} /* namespace thesis */
