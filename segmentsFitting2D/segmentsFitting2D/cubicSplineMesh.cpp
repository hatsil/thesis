#define GLEW_STATIC
#include <GL/glew.h>

#include "cubicSplineMesh.hpp"
#include "cubicSplineModel.hpp"

namespace thesis {
static const uint numBuffers = 2U;
static const uint numIndices = 256U;

CubicSplineMesh::CubicSplineMesh(const CubicSplineShader& shader) :
	shader(shader),
	m_vertexArrayBuffers(numBuffers, 0U) {

	glGenVertexArrays(1U, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	glGenBuffers(numBuffers, m_vertexArrayBuffers.data());

	CubicSplineModel model(numIndices);
	uint i = glGetAttribLocation(shader.m_program, "t");
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[0U]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.ts[0]) * model.ts.size(), &model.ts[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(i);
	glVertexAttribPointer(i, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[1U]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(model.indices[0]) * model.indices.size(), &model.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0U);
}

CubicSplineMesh::~CubicSplineMesh() {
	glDeleteBuffers(numBuffers, m_vertexArrayBuffers.data());
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void CubicSplineMesh::draw() const {
	glBindVertexArray(m_vertexArrayObject);
	glDrawElementsBaseVertex(GL_LINE_STRIP, numIndices, GL_UNSIGNED_INT, 0, 0);
	glBindVertexArray(0U);
}

void CubicSplineMesh::draw(const glm::mat4x2& f, const glm::vec3& color) const {
	shader.update(f, color);
	draw();
}

void CubicSplineMesh::draw(const glm::vec4& fx, const glm::vec4& fy, const glm::vec3& color) const {
	shader.update(fx, fy, color);
	draw();
}

} /* namespace thesis */