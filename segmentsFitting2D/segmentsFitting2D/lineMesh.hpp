#pragma once
#include <vector>

#include <glm/gtc/matrix_transform.hpp>

#include "shaders.hpp"

namespace thesis {
	class LineMesh {
	public:
		LineMesh(const SimpleShader& shader, const std::vector<glm::vec2>& points);
		virtual ~LineMesh();

		void draw(const glm::mat4& trans, const glm::vec3& color) const;

		static inline glm::mat4 calcTransformation(const glm::vec2& p1, const glm::vec2& p2) {
			glm::vec2 dir = p2 - p1;
			float angle = std::acos(glm::dot(glm::normalize(dir), { 1, 0 }));

			if (dir.y < 0)
				angle = -angle;

			glm::mat4 t = glm::translate(glm::mat4(1), glm::vec3(p1, 0));
			glm::mat4 tr = glm::rotate(t, angle, glm::vec3(0, 0, 1));
			return glm::scale(tr, glm::vec3(glm::length(dir), 0, 0));
		}

		static inline glm::mat4 calcTransformation(const glm::vec2& q1, const glm::vec2& q2, const glm::mat4& m) {
			glm::vec2 p1(m * glm::vec4(q1, 0, 1));
			glm::vec2 p2(m * glm::vec4(q2, 0, 1));
			return calcTransformation(p1, p2);
		}

	private:
		const SimpleShader& shader;
		std::vector<uint> m_vertexArrayBuffers;
		uint m_vertexArrayObject;
		uint numIndices;
	};
} /* namespace thesis */
