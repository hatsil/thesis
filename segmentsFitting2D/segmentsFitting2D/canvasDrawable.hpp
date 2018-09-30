#pragma once

#include <list>

namespace thesis {
class CanvasDrawableDelegate;
class CanvasDrawable {
public:
	CanvasDrawable();
	virtual ~CanvasDrawable();

	virtual void defaultDraw() const = 0;
	virtual void defaultDrawForPicking() const = 0;
	
	virtual void controlDraw() const = 0;
	virtual void controlDrawForPicking() const = 0;

	void inserted(const std::list<CanvasDrawable*>::iterator& it);
	void inserted(std::list<CanvasDrawable*>::iterator&& it);

	virtual void setDelegate(CanvasDrawableDelegate* canvasDrawableDelegate);

protected:
	std::list<CanvasDrawable*>::iterator it;
	CanvasDrawableDelegate* canvasDrawableDelegate;
};

} /* namespace thesis */