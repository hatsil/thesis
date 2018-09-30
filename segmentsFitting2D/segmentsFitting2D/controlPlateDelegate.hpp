#pragma once

namespace thesis {
class ControlPlateDelegate {
public:
	virtual ~ControlPlateDelegate() {}

	virtual void controlDraw() const = 0;
	virtual void controlDrawForPicking() const = 0;
};

} /* namespace thesis */