/*
 * window.hpp
 *
 *  Created on: 14 Sep 2018
 *      Author: hatsil
 */

#pragma once

#include "defs.hpp"

#include "drawable.hpp"
#include "selectable.hpp"
#include "removable.hpp"

#include "canvasDelegate.hpp"
#include "buttonDelegate.hpp"

#include "buttonsHolder.hpp"
#include "canvas.hpp"

#include "shaders.hpp"
#include "meshes.hpp"

#include <set>
#include <string>
#include <exception>
#include <stdexcept>

#include <GLFW/glfw3.h>

namespace thesis {
class Window:
	public Drawable,
	public CanvasDelegate,
	public ButtonDelegate {
public:
	Window();
	virtual ~Window();

	//MARK: public methods
	bool isActive() const;

	//MARK: Drawable
	void draw() const override;
	void drawForPicking() const override;

	//MARK: CanvasDelegate
	void fixOffsetCanvas(double& xpos, double& ypos) const override;
	
	//MARK: ButtonDelegate
	void buttonViewport(int i) const override;
	void setDefaultPlate() override;
	void setLinePlate() override;
	void setBrokenLinePlate() override;
	Selectable* getDefaultPlate() const override;
	Selectable* getControlPlate() const override;
	Selectable* getLinePlate() const override;
	Selectable* getBrokenLinePlate() const override;

	//MARK: SelectableDelegate
	void getCursorPosition(double& xpos, double& ypos) const override;
	void setDraw() override;
	void setDrawForPicking() override;
	void setClearRemovables() override;
	void addSelectable(Selectable* selectable) override;
	void removeSelectable(Selectable* selectable) override;
	Selectable* getSelectable() const override;
	const LineMesh& getLineMesh() const override;
	const SquareMesh& getSquareMesh() const override;
	const TexMesh& getTexMesh() const override;

private:
	//MARK: private fields
	GLFWwindow* glfwWindow;
	std::set<Selectable*, SelectablePtrComp> selectables;
	size_t width, height;
	uchar* colorsBuffer;

	//MARK: commands plates
	ButtonsHolder* buttonsHolder;
	Canvas* canvas;

	//MARK: status vars
	bool drawStatus, drawForPickingStatus, clearRemovablesStatus;

	//MARK: shaders
	SimpleShader* simpleShader;
	TexShader* texShader;

	//MARK: meshes
	LineMesh* lineMesh;
	SquareMesh* squareMesh;
	TexMesh* texMesh;

	//MARK: current selectables
	Selectable* selected;
	Selectable* marked;

	//MARK: private methods
	void buttonsHolderViewport() const;
	void canvasViewport() const;
	Selectable* getSelectable(double xpos, double ypos) const;
	void initCallbacks() const;
	void controlPress();
	void controlRelease();
	void drawAll();
	void drawIfNeeded();
	
	//MARK: callbacks
	void keyCallback(int key, int scancode, int action, int mods);
	void mouseCallback(int button, int action, int mods);
	void cursorPositionCallback(double xpos, double ypos);

	//MARK: friends
	friend void keyCallback1(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods);
	friend void mouseCallback1(GLFWwindow* glfwWindow, int button, int action, int mods);
	friend void cursorPositionCallback1(GLFWwindow* glfwWindow, double xpos, double ypos);
};

} /* namespace thesis */

