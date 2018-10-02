#pragma once

#include "squareMesh.hpp"
#include "selectable.hpp"

namespace thesis {
class CanvasPlate: public Selectable {
public:
	CanvasPlate();
	virtual ~CanvasPlate();

	//MARK: Drawable
	void drawForPicking() const override;

	//MARK: Selectable
	void leftPress(Selectable*) override;
	void leftRelease() override;

protected:
	virtual const SquareMesh& mesh() const;
};

}