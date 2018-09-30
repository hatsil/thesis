#pragma once

#include "globalVars.hpp"

namespace thesis {
	//MARK: joints vars
	//colors:
	const glm::vec3 normalJointColor = glm::vec3(230.f/255.f, 0, 0);
	const glm::vec3 selectedJointColor = glm::vec3(0, 204.f/255.f, 0);
	const glm::vec3 markedJointColor = glm::vec3(250.f/255.f, 205.f/255.f, 0);
	
	//scale factor
	const glm::vec3 jointScaleFactor = glm::vec3(.015f);

	//MARK: line width
	const float boldLineWidth = 7.5f;

	//MARK: line colors
	const glm::vec3 defaultLineColor = glm::vec3(0, 0, 0);
	const glm::vec3 middlePressedColor = normalJointColor;

	//MARK: buttons holder background color
	const glm::vec3 buttonsHolderBackgroundColor = glm::vec3(.5f);
}
