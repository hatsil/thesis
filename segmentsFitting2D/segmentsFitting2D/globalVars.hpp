#pragma once

#include <glm/glm.hpp>

namespace thesis {
	//MARK: joints vars
	//colors:
	extern const glm::vec3 normalJointColor;
	extern const glm::vec3 selectedJointColor;
	extern const glm::vec3 markedJointColor;
	extern const glm::vec3 middlePressedJointColor;

	extern const glm::vec3 normalTangentJointColor;
	extern const glm::vec3 selectedTangentJointColor;

	//scale factor
	extern const glm::vec3 jointScaleFactor;

	//MARK: line width
	extern const float boldLineWidth;

	//MARK: segments colors
	extern const glm::vec3 defaultLineColor;
	extern const glm::vec3 defaultBrokenLineColor;
	extern const glm::vec3 defaultCurveColor;
	extern const glm::vec3 defaultSketchColor;
	extern const glm::vec3 middlePressedColor;

	//MARK: buttons holder background color
	extern const glm::vec3 buttonsHolderBackgroundColor;

	//MARK: default functions
	const glm::mat4& scale();
	const glm::mat4& rot45();
	const glm::mat4& rot45Scale();
}
