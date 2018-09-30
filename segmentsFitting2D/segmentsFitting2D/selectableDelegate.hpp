#pragma once

#include "meshes.hpp"
#include "selectable.hpp"

namespace thesis {
class SelectableDelegate {
public:
	virtual ~SelectableDelegate() {}

	virtual void getCursorPosition(double& xpos, double& ypos) const = 0;
	virtual void setDraw() = 0;
	virtual void setDrawForPicking() = 0;
	virtual void setDrawAll() = 0;
	virtual void setClearRemovables() = 0;
	virtual void addSelectable(Selectable* selectable) = 0;
	virtual void removeSelectable(Selectable* selectable) = 0;
	virtual Selectable* getSelectable() const = 0;
	virtual const LineMesh& getLineMesh() const = 0;
	virtual const SquareMesh& getSquareMesh() const = 0;
	virtual const TexMesh& getTexMesh() const = 0;
};

} /* namespace thesis */