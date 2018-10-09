#pragma once

#include "selectableDelegate.hpp"

namespace thesis {
class ButtonDelegate: virtual public SelectableDelegate {
public:
	virtual ~ButtonDelegate() {}
	virtual void buttonViewport(int i) const = 0;
	
	//MARK: setters
	virtual void setDefaultPlate() = 0;
	virtual void setLinePlate() = 0;
	virtual void setBrokenLinePlate() = 0;
	virtual void setCurvePlate() = 0;
	virtual void setSketchPlate() = 0;

	//MARK: getters
	virtual Selectable* getDefaultPlate() const = 0;
	virtual Selectable* getControlPlate() const = 0;
	virtual Selectable* getLinePlate() const = 0;
	virtual Selectable* getBrokenLinePlate() const = 0;
	virtual Selectable* getCurvePlate() const = 0;
	virtual Selectable* getSketchPlate() const = 0;
};

} /* namespace thesis */
