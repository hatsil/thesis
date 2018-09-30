/*
 * buttonsHolder.hpp
 *
 *  Created on: 14 Sep 2018
 *      Author: hatsil
 */

#pragma once

#include "drawable.hpp"
#include "selectable.hpp"
#include "button.hpp"
#include "squareMesh.hpp"

#include <functional>
#include <vector>
#include <iostream>

namespace thesis {
class ButtonDelegate;
class ButtonsHolder: public Drawable {
public:
	ButtonsHolder(size_t width, size_t buttonSize);
	virtual ~ButtonsHolder();

	//MARK: Drawable
	void draw() const override;
	void drawForPicking() const override;

	//MARK: pubnlic methods
	void controlPress();
	void controlRelease();
	ButtonsHolder& initButtons();

	size_t getWidth() const;
	size_t getHeight() const;

	void setDelegate(ButtonDelegate* buttonDelegate);

private:
	//MARK: private fields
	size_t width, height;
	bool controlPressed;
	std::vector<Button*> buttons;
	ButtonDelegate* buttonDelegate;

	void forEach(const std::function<void(int, Button*)>& func) const;
	void forEach(const std::function<void(Button*)>& func) const;

	const SquareMesh& mesh() const;
};



} /* namespace thesis */
