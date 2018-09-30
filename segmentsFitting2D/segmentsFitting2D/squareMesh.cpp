#define GLEW_STATIC
#include <GL/glew.h>

#include "squareMesh.hpp"
#include "squareModel.hpp"

namespace thesis {
static const uint numBuffers = 2U;
static const uint numIndices = 6U;

SquareMesh::SquareMesh(const SimpleShader& shader) :
	shader(shader),
	m_vertexArrayBuffers(numBuffers, 0U) {

	glGenVertexArrays(1U, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	glGenBuffers(numBuffers, m_vertexArrayBuffers.data());

	SquareModel model;
	uint i = glGetAttribLocation(shader.m_program, "position");
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[0U]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.positions[0]) * model.positions.size(), &model.positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(i);
	glVertexAttribPointer(i, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[1U]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(model.indices[0]) * model.indices.size(), &model.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0U);
}

SquareMesh::~SquareMesh() {
	glDeleteBuffers(numBuffers, m_vertexArrayBuffers.data());
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void SquareMesh::draw(const glm::mat4& trans, const glm::vec3& color) const {
	shader.update(trans, color);
	glBindVertexArray(m_vertexArrayObject);
	glDrawElementsBaseVertex(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0, 0);
	glBindVertexArray(0U);
}

} /* namespace thesis */