/*
 * pressable.hpp
 *
 *  Created on: 13 Sep 2018
 *      Author: hatsil
 */

#pragma once

#include "drawable.hpp"

#include <glm/glm.hpp>

namespace thesis {
class SelectableDelegate;
struct SelectablePtrComp;

class Selectable: public Drawable {
public:
	Selectable();
	virtual ~Selectable();

	virtual void leftPress() = 0;
	virtual void leftRelease() = 0;
	virtual void leftPosition(double xpos, double ypos);
	virtual void resign();

	virtual void rightPress();
	virtual void rightRelease();
	virtual void rightPosition(double xpos, double ypos);

	virtual void middlePress();
	virtual void middleRelease();

	virtual bool mark();
	virtual bool unmark();
	virtual bool isRemovable() const;

	virtual void setDelegate(SelectableDelegate* selectableDelegate);
	
protected:
	uint pickingColor;
	glm::vec3 pickingColorVec;
	SelectableDelegate* selectableDelegate;

private:
	//friends:
	friend SelectablePtrComp;
};

struct SelectablePtrComp {
	using is_transparent = uint;
	bool operator()(Selectable* const & lhs, Selectable* const & rhs) const;
	bool operator()(Selectable* const & lhs, const uint& rhs) const;
	bool operator()(const uint& lhs, Selectable* const & rhs) const;
};

} /* namespace thesis */
