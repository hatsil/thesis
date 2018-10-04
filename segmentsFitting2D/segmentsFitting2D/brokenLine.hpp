#pragma once

#include "canvasDrawable.hpp"
#include "globalVars.hpp"
#include "selectable.hpp"
#include "removable.hpp"
#include "lineMesh.hpp"
#include "squareMesh.hpp"

#include "selectableDelegate.hpp"
#include "removableDelegate.hpp"
#include "canvasDrawableDelegate.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <utility>
#include <list>
#include <set>
#include <iterator>

namespace thesis {
class BrokenLine: public CanvasDrawable {
public:
	BrokenLine(const std::list<glm::vec2> & points);
	virtual ~BrokenLine();

	//MARK: CanvasDrawable
	void defaultDraw() const override;
	void defaultDrawForPicking() const override;
	void controlDraw() const override;
	void controlDrawForPicking() const override;
	void setDelegate(CanvasDrawableDelegate* canvasDrawableDelegate) override;

	//MARK: public methods
	void setDelegate(SelectableDelegate* selectableDelegate);
	void setDelegate(RemovableDelegate* removableDelegate);

private:
	class Joint;
	class Segment: public Removable {
	public:
		Segment();
		virtual ~Segment();

		//MARK: Drawable
		void draw() const override;
		void drawForPicking() const override;

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

		//MARK: public methods
		void controlDraw() const;

		inline void setParent(BrokenLine* parent) {
			this->parent = parent;
			parent->add(this);
		}

		inline void inserted(const std::list<Joint*>::iterator& it) {
			this->it = it;
		}

	private:
		//MARK: private fields
		BrokenLine* parent;
		std::list<Joint*>::iterator it;
		bool deleteParent;

		//MARK: private methods
		inline glm::mat4 calcTransformation() const {
			return LineMesh::calcTransformation(joint1()->getPosition(), joint2()->getPosition());
		}

		inline const LineMesh& mesh() const {
			return selectableDelegate->getLineMesh();
		}

		inline Joint* joint1() const {
			return *it;
		}

		inline Joint* joint2() const {
			return *std::next(it);
		}
	};

	class Joint: public Removable {
	public:
		Joint(const glm::vec2& position);
		virtual ~Joint();

		inline void inserted(const std::list<Joint*>::iterator& it) {
			this->it = it;
		}

		inline void inserted(std::list<Joint*>::iterator&& it) {
			this->it = std::move(it);
		}

		inline void setParent(BrokenLine* parent) {
			this->parent = parent;
			parent->add(this);
		}

		void createSegment();
		
		inline void destroySegment() {
			if(segment)
				delete segment;
		}

		//MARK: Drawable
		void draw() const override;
		void drawForPicking() const override;

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

		//MARK: public methods
		inline void setDefaultState() {
			pressed = released = false;
			color = normalJointColor;
		}

		inline void addOffset(const glm::vec2& offset) {
			position += offset;
			calcTranslation();
		}

		inline const glm::vec2& getPosition() const {
			return position;
		}

		void controlDraw() const;
		void controlDrawForPicking() const;

	private:
		//MARK: private fields
		glm::vec2 position;
		Segment* segment;
		std::list<Joint*>::iterator it;
		bool deleteParent;
		BrokenLine* parent;

		glm::mat4 translation;
		glm::mat4 scale;
		glm::vec3 color;
		bool isRipped, pressed, released, moved;
		double xposPrev, yposPrev;

		//MARK: private methods
		inline const SquareMesh& mesh() const {
			return selectableDelegate->getSquareMesh();
		}

		inline void calcTranslation() {
			translation = glm::translate(glm::mat4(1), glm::vec3(position, 0));
		}

		//MARK: friends
		friend Segment;
	};

	//MARK: private fields
	std::list<Joint*> joints;
	std::set<Selectable*> relatives;
	glm::vec3 color;
	bool pressed, released, moved, marked;
	double xposPrev, yposPrev;

	SelectableDelegate* selectableDelegate;
	RemovableDelegate* removableDelegate;

	//MARK: private methods
	//MARK pseudo Selectable - as parent
	void leftPress(Selectable* prev);
	void leftRelease();
	void leftPosition(double xpos, double ypos);
	void resign();
	void middlePress();
	void middleRelease(Removable* child);
	bool mark();
	bool unmark();

	//MARK: relatives managment
	inline void add(Selectable* relative) {
		relatives.insert(relative);
	}
	
	inline void remove(Selectable* relative) {
		relatives.erase(relative);
	}
	
	inline bool isRelative(Selectable* selectable) const {
		return relatives.find(selectable) != relatives.cend();
	}

	inline void remove(const std::list<Joint*>::iterator& it) {
		joints.erase(it);
	}

	template<class Function>
	void forEach(const Function& func) const {
		for(Joint* joint : joints)
			func(joint);
	}
	
	template<class Function>
	void forEach(const Function& func) {
		for(Joint* joint : joints)
			func(joint);
	}

	inline bool isBold() const {
		return pressed || marked;
	}

	inline glm::vec2 convertPos(double xpos, double ypos) const {
		return removableDelegate->convertPos(xpos, ypos);
	}

	inline void setDefaultState() {
		forEach([](Joint* joint) {
			joint->setDefaultState();
		});
	}

	inline bool canTakeDemolitionOwnership() const {
		return joints.size() == 2;
	}

	inline bool isLast(const std::list<Joint*>::iterator& it) const {
		return std::next(it) == joints.cend();
	}

	inline void clear() {
		joints.clear();
		canvasDrawableDelegate->remove(it);
	}

	//MARK: friends
	friend Joint;
	friend Segment;
};

} /* namespace thesis */