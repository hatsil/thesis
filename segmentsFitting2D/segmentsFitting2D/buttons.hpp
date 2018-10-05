#pragma once

#include "button.hpp"

namespace thesis {
class DefaultButton: public Button {
public:
	DefaultButton();
	virtual ~DefaultButton();

protected:
	void buttonOperation() override;
	void setRelatives() override;
};

class LineButton: public Button {
public:
	LineButton();
	virtual ~LineButton();

protected:
	void buttonOperation() override;
	void setRelatives() override;
};

class BrokenLineButton: public Button {
public:
	BrokenLineButton();
	virtual ~BrokenLineButton();

protected:
	void buttonOperation() override;
	void setRelatives() override;
};

class CurveButton: public Button {
public:
	CurveButton();
	virtual ~CurveButton();

protected:
	void buttonOperation() override;
	void setRelatives() override;
};

} /* namespace thesis */