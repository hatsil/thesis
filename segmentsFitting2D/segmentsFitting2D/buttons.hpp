#pragma once

#include "button.hpp"

namespace thesis {
class DefaultButton : public Button {
public:
	DefaultButton();
	virtual ~DefaultButton();

protected:
	void buttonOperation() override;

};

class LineButton : public Button {
public:
	LineButton();
	virtual ~LineButton();

protected:
	void buttonOperation() override;

};

} /* namespace thesis */