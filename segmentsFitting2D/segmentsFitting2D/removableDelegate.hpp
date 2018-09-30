#pragma once

#include "removable.hpp"

#include <glm/glm.hpp>

namespace thesis {
class RemovableDelegate {
public:
	virtual ~RemovableDelegate() {}

	virtual void addRemovable(Removable* removable) = 0;
	virtual void addRipped(Removable* removable) = 0;
	virtual glm::vec2 convertPos(double xpos, double ypos) const = 0;
};

} /* namespace thesis */