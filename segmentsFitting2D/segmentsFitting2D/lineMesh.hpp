#pragma once

#include "shaders.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <vector>

namespace thesis {
	class LineMesh {
	public:
		LineMesh(const SimpleShader& shader);
		LineMesh(const SimpleShader& shader, const std::vector<glm::vec2>& points);
		virtual ~LineMesh();

		void draw(const glm::mat4& trans, const glm::vec3& color) const;


		static inline glm::mat4 calcTransformation(const glm::vec2& p1, const glm::vec2& p2) {
			glm::vec2 dir = p2 - p1;
			float angle = std::acos(glm::dot(glm::normalize(dir), { 1, 0 }));

			if(dir.y < 0)
				angle = -angle;

			glm::mat4 t = glm::translate(glm::mat4(1), glm::vec3(p1, 0));
			glm::mat4 tr = glm::rotate(t, angle, glm::vec3(0, 0, 1));
			return glm::scale(tr, glm::vec3(glm::length(dir), 1, 1));
		}

		static inline glm::mat4 calcTransformation(const glm::vec2& q1, const glm::vec2& q2, const glm::mat4& m) {
			glm::vec2 p1(m * glm::vec4(q1, 0, 1));
			glm::vec2 p2(m * glm::vec4(q2, 0, 1));
			return calcTransformation(p1, p2);
		}

		static inline glm::mat4 calcTransformation(
				const glm::vec2& from1,
				const glm::vec2& from2,
				const glm::vec2& to1,
				const glm::vec2& to2) {
			glm::dvec4 x(from1.x, 0, from2.x, 0);
			glm::dvec4 y(1, 0, 1, 0);
			glm::dvec4 z(0, from1.y, 0,from2.y);
			glm::dvec4 w(0, 1, 0, 1);
			glm::dmat4 m = glm::inverse(glm::dmat4(x, y, z, w));
			glm::dvec4 abcd = m * glm::dvec4(to1.x, to1.y, to2.x, to2.y);
			glm::mat4 ans(1);
			ans[0][0] = (float)abcd.x;
			ans[3][0] = (float)abcd.y;
			ans[1][1] = (float)abcd.z;
			ans[3][1] = (float)abcd.w;
			return ans;
		}

	private:
		const SimpleShader& shader;
		std::vector<uint> m_vertexArrayBuffers;
		uint m_vertexArrayObject;
		uint numIndices;
	};
} /* namespace thesis */
