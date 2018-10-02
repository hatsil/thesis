/*
 * canvas.hpp
 *
 *  Created on: 14 Sep 2018
 *      Author: hatsil
 */

#pragma once

#include "drawable.hpp"
#include "selectable.hpp"
#include "removable.hpp"

#include "removableDelegate.hpp"
#include "canvasDrawableDelegate.hpp"

#include "canvasPlates.hpp"
#include "canvasPlatesDelegates.hpp"

#include "concurrent.hpp"

#include <glm/glm.hpp>

#include <set>
#include <list>

namespace thesis {
class CanvasDelegate;
class CanvasDrawable;
class Canvas:
	public Drawable,
	public RemovableDelegate,
	public CanvasDrawableDelegate,
	public LinePlateDelegate,
	public ControlPlateDelegate,
	public DefaultPlateDelegate {
public:
	Canvas(size_t width, size_t height);
	virtual ~Canvas();

	//MARK: Drawable
	void draw() const override;
	void drawForPicking() const override;
	
	//MARK: plates delegates
	void defaultDraw() const override;
	void defaultDrawForPicking() const override;
	void controlDraw() const override;
	void controlDrawForPicking() const override;
	void lineDraw() override;
	void setTempLine(double xposBegin, double yposBegin, double xposEnd, double yposEnd) override;
	void packLine(double xposBegin, double yposBegin) override;
	
	//MARK: RemovableDelegate
	void addRemovable(Removable* removable) override;
	void addRipped(Removable* ripped) override;
	glm::vec2 convertPos(double xpos, double ypos) const override;

	//MARK: CanvasDrawableDelegate
	void remove(const std::list<CanvasDrawable*>::iterator& it) override;
	void moveToFront(std::list<CanvasDrawable*>::iterator& it) override;
	
	//MARK: plates setters and getters
	void setDefaultPlate();
	void setLinePlate();
	Selectable* getDefaultPlate() const;
	Selectable* getControlPlate() const;
	Selectable* getLinePlate() const;

	//MARK: public methods
	void undo();
	void clearRippedObjects();
	void controlPress();
	void controlRelease();
	void wait();

	size_t getWidth() const;
	size_t getHeight() const;

	void setDelegate(CanvasDelegate* canvasDelegate);

private:
	size_t width, height;
	CanvasDelegate* canvasDelegate;

	//MARK: Canvas Plates
	CanvasPlate* curPlate;
	CanvasPlate* prevPlate;

	DefaultPlate* defaultPlate;
	ControlPlate* controlPlate;
	LinePlate* linePlate;

	std::set<Removable*, SelectablePtrComp> removables;
	std::list<Removable*> rippedObjects;
	std::list<CanvasDrawable*> drawables;

	glm::mat4* lineTransformation;

	using CanvasDrawableFunc = void (CanvasDrawable::*)() const;
	
	//MARK: private methods
	void forEach(CanvasDrawableFunc func) const;
	const LineMesh& lineMesh() const;
};

} /* namespace thesis */
