#pragma once

namespace thesis {
class LinePlateDelegate {
public:
	virtual ~LinePlateDelegate() {}

	virtual void lineDraw() = 0;
	virtual void setTempLine(double xposBegin, double yposBegin, double xposEnd, double yposEnd) = 0;
	virtual void packLine(double xposBegin, double yposBegin) = 0;
};

} /* namespace thesis */