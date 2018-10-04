#pragma once

namespace thesis {
class BrokenLinePlateDelegate {
public:
	virtual ~BrokenLinePlateDelegate() {}

	virtual void brokenLineDraw() = 0;
	virtual void brokenLineLeftPress() = 0;
	virtual void brokenLineRightPress() = 0;
	virtual void brokenLineResign() = 0;
	virtual void brokenLinePosition(double xpos, double ypos) = 0;
};

} /* namespace thesis */
