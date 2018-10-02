#include "canvasPlate.hpp"
#include "window.hpp"

namespace thesis {
CanvasPlate::CanvasPlate():
	Selectable() {}

CanvasPlate::~CanvasPlate() {}

void CanvasPlate::drawForPicking() const {
	mesh().draw(glm::mat4(1), pickingColorVec);
}

void CanvasPlate::leftPress(Selectable*) {}

void CanvasPlate::leftRelease() {}

const SquareMesh& CanvasPlate::mesh() const {
	return selectableDelegate->getSquareMesh();
}

} /* namespace thesis */