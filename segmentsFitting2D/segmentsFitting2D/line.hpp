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
#include <list>
#include <set>

namespace thesis {
class Line:
	public CanvasDrawable,
	public Removable {
public:
	Line(const glm::vec2& q1, const glm::vec2& q2);
	virtual ~Line();

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

	//MARK: Removable
	void ripMe() override;
	void setDelegate(RemovableDelegate* removableDelegate) override;

private:
	class EdgePoint: public Selectable {
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
		void resign() override;
		bool mark() override;
		bool unmark() override;
		void setDelegate(SelectableDelegate* selectableDelegate) override;

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

		inline void setParent(Line* parent) {
			this->parent = parent;
		}

	private:
		//MARK: private fields
		glm::vec2 position;
		Line* parent;

		glm::mat4 translation;
		glm::mat4 scale;
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
	glm::vec3 color;
	std::set<Selectable*> relatives;

	EdgePoint* p1, *p2;
	
	bool isRipped, pressed, released, moved, marked;
	double xposPrev, yposPrev;

	//MARK: private methods
	inline glm::mat4 calcTransformation() const {
		return LineMesh::calcTransformation(p1->getPosition(), p2->getPosition());
	}

	inline bool isBold() const {
		return pressed || marked;
	}

	inline const LineMesh& mesh() const {
		return selectableDelegate->getLineMesh();
	}

	inline glm::vec2 convertPos(double xpos, double ypos) const {
		return removableDelegate->convertPos(xpos, ypos);
	}

	inline bool isRelative(Selectable* selectable) const {
		return relatives.find(selectable) != relatives.cend();
	}
	
	//MARK: friens
	friend EdgePoint;
};

} /* namespace thesis */
