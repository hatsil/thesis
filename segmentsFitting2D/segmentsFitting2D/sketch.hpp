/*
 * sketch.hpp
 *
 *  Created on: 8 Oct 2018
 *      Author: hatsil
 */

#pragma once

#include "canvasDrawable.hpp"
#include "selectableDelegate.hpp"
#include "removableDelegate.hpp"
#include "globalVars.hpp"
#include "selectable.hpp"
#include "removable.hpp"
#include "lineMesh.hpp"
#include "squareMesh.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <set>

namespace thesis {

class Sketch:
	public CanvasDrawable,
	public Removable {
public:
	Sketch(const std::vector<glm::vec2>& poitns);
	virtual ~Sketch();

	//MARK: CanvasDrawable
	void defaultDraw() const override;
	void defaultDrawForPicking() const override;
	void controlDraw() const override;
	void controlDrawForPicking() const override;
	void setDelegate(CanvasDrawableDelegate* canvasDrawableDelegate) override;

	//MARK: Selectable
	void leftPress(Selectable* prev) override;
	void leftRelease() override;
	void leftPosition(double xpos, double ypos) override;
	void resign() override;
	void middlePress() override;
	void middleRelease() override;
	bool mark() override;
	bool unmark() override;
	void setDelegate(SelectableDelegate* selectableDelegate) override;

	//MARK: removable
	void ripMe() override;
	void setDelegate(RemovableDelegate* removableDelegate) override;

private:
	class EdgePoint: public Removable {
	public:
		EdgePoint(const glm::vec2& position);
		virtual ~EdgePoint();

		//MARK: Drawable
		void draw() const override;
		void drawForPicking() const override;

		//MARK: Selectable
		void leftPress(Selectable* prev) override;
		void leftRelease() override;
		void leftPosition(double xpos, double ypos) override;
		void middlePress() override;
		void middleRelease() override;
		void resign() override;
		bool mark() override;
		bool unmark() override;
		void setDelegate(SelectableDelegate* selectableDelegate) override;

		//MARK: Removable
		void ripMe() override;
		void setDelegate(RemovableDelegate* removableDelegate) override;

		//MARK: public methods
		inline const glm::vec2& getPosition() const {
			return position;
		}

		inline void setDefaultState() {
			pressed = released = false;
			color = normalJointColor;
		}

		inline void addOffset(const glm::vec2& offset) {
			position += offset;
			calcTranslation();
		}

		inline void setParent(Sketch* parent) {
			this->parent = parent;
		}

	private:
		//MARK: private fields
		glm::vec2 position;
		Sketch* parent;

		glm::mat4 translation;
		glm::vec3 color;
		bool pressed, released, moved;
		double xposPrev, yposPrev;

		//MARK: private methods
		inline void calcTranslation() {
			translation = glm::translate(glm::mat4(1), glm::vec3(position, 0));
		}

		inline const SquareMesh& mesh() const {
			return selectableDelegate->getSquareMesh();
		}
	};

	//MARK: private fields
	std::vector<glm::vec2> points;
	LineMesh* mesh;
	glm::vec3 color;
	std::set<Selectable*> relatives;
	EdgePoint* p1, *p2;

	bool isRipped, pressed, released, moved, marked;
	double xposPrev, yposPrev;

	//MARK: private methods
	inline glm::mat4 calcTransformation() const {
		return LineMesh::calcTransformation(q1(), q2(), p1->getPosition(), p2->getPosition());
	}

	inline bool isBold() const {
		return pressed || marked;
	}

	inline glm::vec2 convertPos(double xpos, double ypos) const {
		return removableDelegate->convertPos(xpos, ypos);
	}

	inline bool isRelative(Selectable* selectable) const {
		return relatives.find(selectable) != relatives.cend();
	}

	inline const glm::vec2& q1() const {
		return points.front();
	}

	inline const glm::vec2& q2() const {
		return points.back();
	}

	//MARK: friens
	friend EdgePoint;
};

} /* namespace thesis */
