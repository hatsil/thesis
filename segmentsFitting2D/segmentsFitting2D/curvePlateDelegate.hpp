#pragma once

namespace thesis {
class CurvePlateDelegate {
public:
	virtual ~CurvePlateDelegate() {}

	virtual void curveDraw() = 0;
	virtual void setTempCurve(double xposBegin, double yposBegin, double xposEnd, double yposEnd) = 0;
	virtual void packCurve(double xposBegin, double yposBegin) = 0;
};

} /* namespace thesis */