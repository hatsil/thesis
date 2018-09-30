#pragma once

#include "selectable.hpp"

namespace thesis {
class RemovableDelegate;
class Removable: public Selectable {
public:
	Removable();
	virtual ~Removable();

	void draw() const override;
	void drawForPicking() const override;
	bool isRemovable() const override;

	virtual void ripMe() = 0;
	virtual void setDelegate(RemovableDelegate* removableDelegate);

protected:
	RemovableDelegate* removableDelegate;
};

} /* namespace thesis */
