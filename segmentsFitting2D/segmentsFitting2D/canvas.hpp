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

#include "selectableDelegate.hpp"
#include "removableDelegate.hpp"
#include "canvasDrawableDelegate.hpp"

#include "canvasPlates.hpp"
#include "canvasPlatesDelegates.hpp"

#include "lineMesh.hpp"

#include "globalVars.hpp"

#include <glm/glm.hpp>

#include <set>
#include <list>
#include <vector>
#include <utility>

namespace thesis {
class CanvasDelegate;
class CanvasDrawable;
class Canvas:
	public Drawable,
	public RemovableDelegate,
	public CanvasDrawableDelegate,
	public LinePlateDelegate,
	public ControlPlateDelegate,
	public DefaultPlateDelegate,
	public BrokenLinePlateDelegate,
	public CurvePlateDelegate,
	public SketchPlateDelegate {
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

	void lineDraw() override {
		lineDraw(defaultLineColor);
	}

	void setTempLine(double xposBegin, double yposBegin, double xposEnd, double yposEnd) override;
	void packLine(double xposBegin, double yposBegin) override;
	void brokenLineDraw() override;
	void brokenLineLeftPress() override;
	void brokenLineRightPress() override;
	void brokenLineResign() override;
	void brokenLinePosition(double xpos, double ypos) override;
	void sketchDraw() override;
	void sketchLeftPress() override;
	void sketchLeftPosition(double xpos, double ypos) override;
	void packSketch() override;
	
	void curveDraw() override {
		lineDraw(defaultCurveColor);
	}
	
	void setTempCurve(double xposBegin, double yposBegin, double xposEnd, double yposEnd) override {
		setTempLine(xposBegin, yposBegin, xposEnd, yposEnd);
	}

	void packCurve(double xposBegin, double yposBegin) override;
	
	//MARK: RemovableDelegate
	void addRipped(Removable* ripped) override;
	glm::vec2 convertPos(double xpos, double ypos) const override;

	//MARK: CanvasDrawableDelegate
	void remove(const std::list<CanvasDrawable*>::iterator& it) override;
	void moveToFront(std::list<CanvasDrawable*>::iterator& it) override;
	
	//MARK: plates setters and getters
	void setDefaultPlate();
	void setLinePlate();
	void setBrokenLinePlate();
	void setCurvePlate();
	void setSketchPlate();
	Selectable* getDefaultPlate() const;
	Selectable* getControlPlate() const;
	Selectable* getLinePlate() const;
	Selectable* getBrokenLinePlate() const;
	Selectable* getCurvePlate() const;
	Selectable* getSketchPlate() const;

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

	DefaultPlate* defaultPlate;
	ControlPlate* controlPlate;
	LinePlate* linePlate;
	BrokenLinePlate* brokenLinePlate;
	CurvePlate* curvePlate;
	SketchPlate* sketchPlate;

	std::list<Removable*> rippedObjects;
	std::list<CanvasDrawable*> drawables;
	std::list<glm::vec2> brokenLineList;

	struct TempLine {
		TempLine(): hasLine(false), p1(0), p2(0) {}
		TempLine(const glm::vec2& p1, const glm::vec2& p2): hasLine(true), p1(p1), p2(p2) {}

		virtual ~TempLine() {}

		operator bool() const {
			return hasLine;
		}

		operator glm::mat4() const {
			return LineMesh::calcTransformation(p1, p2);
		}

		bool operator=(bool hasLine) {
			this->hasLine = hasLine;
			return hasLine;
		}

		bool hasLine;
		glm::vec2 p1, p2;
	};

	struct TempSketch:
		public Drawable {
		TempSketch():
			Drawable(),
			mesh(nullptr),
			points(),
			selectableDelegate(nullptr) {}

		TempSketch(const TempSketch& other):
			Drawable(),
			mesh(nullptr),
			points(other.points),
			selectableDelegate(other.selectableDelegate) {
			if(other)
				mesh = new LineMesh(selectableDelegate->getSimpleShader(), points);
		}

		TempSketch(TempSketch&& other):
			Drawable(),
			mesh(other.mesh),
			points(std::move(other.points)),
			selectableDelegate(other.selectableDelegate) {
			other.mesh = nullptr;
		}

		virtual ~TempSketch() {
			if(mesh)
				delete mesh;
		}

		TempSketch& operator=(const TempSketch& other) {
			points = other.points;
			selectableDelegate = other.selectableDelegate;
			if(mesh) {
				delete mesh;
				mesh = nullptr;
			}

			if(other)
				mesh = new LineMesh(selectableDelegate->getSimpleShader(), points);

			return *this;
		}

		TempSketch& operator=(TempSketch&& other) {
			points = std::move(other.points);
			selectableDelegate = other.selectableDelegate;

			if(mesh)
				delete mesh;

			mesh = other.mesh;
			other.mesh = nullptr;

			return *this;
		}

		void draw() const override {
			if(mesh) {
				mesh->draw(glm::mat4(1), defaultSketchColor);
			}
		}

		void drawForPicking() const override {}

		const glm::vec2& operator<<(const glm::vec2& point) {
			points.push_back(point);

			if(mesh) {
				delete mesh;
				mesh = nullptr;
			}

			if(points.size() > 1)
				mesh = new LineMesh(selectableDelegate->getSimpleShader(), points);

			return point;
		}

		std::nullptr_t operator=(std::nullptr_t) {
			if(mesh) {
				delete mesh;
				mesh = nullptr;
			}
			points.clear();
			return nullptr;
		}

		void setDelegate(SelectableDelegate* selectableDelegate) {
			this->selectableDelegate = selectableDelegate;
		}

		operator const std::vector<glm::vec2>&() const {
			return points;
		}

		operator bool() const {
			return mesh != nullptr;
		}

		LineMesh* mesh;
		std::vector<glm::vec2> points;
		SelectableDelegate* selectableDelegate;
	};

	TempLine tempLine;
	TempSketch tempSketch;

	using CanvasDrawableFunc = void (CanvasDrawable::*)() const;
	
	//MARK: private methods
	void forEach(CanvasDrawableFunc func) const;
	const LineMesh& lineMesh() const;
	void lineDraw(const glm::vec3& color);

};

} /* namespace thesis */
