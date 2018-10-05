#pragma once

#include "globalVars.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace thesis {
	//MARK: joints vars
	//colors:
	const glm::vec3 normalJointColor = glm::vec3(230.f/255.f, 0, 0);
	const glm::vec3 selectedJointColor = glm::vec3(0, 204.f/255.f, 0);
	const glm::vec3 markedJointColor = glm::vec3(250.f/255.f, 205.f/255.f, 0);
	const glm::vec3 middlePressedJointColor = glm::vec3(0, 0, 230.f / 255.f);

	const glm::vec3 normalTangentJointColor = glm::vec3(180.f / 255.f, 0, 180.f / 255.f);
	const glm::vec3 selectedTangentJointColor = glm::vec3(230.f / 255.f, 0, 230.f / 255.f);
	
	//scale factor
	const glm::vec3 jointScaleFactor = glm::vec3(.015f);

	//MARK: line width
	const float boldLineWidth = 7.5f;

	//MARK: line colors
	const glm::vec3 defaultLineColor = glm::vec3(0, 0, 0);
	const glm::vec3 middlePressedColor = normalJointColor;

	//MARK: buttons holder background color
	const glm::vec3 buttonsHolderBackgroundColor = glm::vec3(.5f);

	//MARK: default functions
	const glm::mat4& scale() {
		const static glm::mat4 s = glm::scale(glm::mat4(1), jointScaleFactor);
		return s;
	}

	const glm::mat4& rot45() {
		const static glm::mat4 r = glm::rotate(glm::mat4(1), glm::radians(45.f), glm::vec3(0, 0, 1));
		return r;
	}

}
