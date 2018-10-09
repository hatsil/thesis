#pragma once

#include "selectable.hpp"
#include "texture.hpp"
#include "squareMesh.hpp"
#include "texMesh.hpp"

#include <set>

namespace thesis {
class ButtonDelegate;
class Button: public Selectable {
public:
	Button(const char* fileName);
	virtual ~Button();

	//MARK: Drawable
	void draw() const override;
	void drawForPicking() const override;

	//MARK: Selectable
	void leftPress(Selectable* prev) override;
	void leftRelease() override;
	void resign() override;
	bool mark() override;
	bool unmark() override;

	void setDelegate(ButtonDelegate* buttonDelegate);
	
protected:
	ButtonDelegate* buttonDelegate;

	virtual void buttonOperation() = 0;
	virtual void setRelatives() = 0;

	std::set<Selectable*> relatives;
	bool isRelative(Selectable* selectable) const;

private:
	//MARK: private fields
	Texture texture;
	bool marked, needRelease;

	//MARK: private methods
	const TexMesh& texMesh() const;
	const SquareMesh& squareMesh() const;
};

} /* namespace thesis */
