#pragma once

#include "canvasDrawable.hpp"
#include "selectable.hpp"
#include "removable.hpp"
#include "lineMesh.hpp"
#include "squareMesh.hpp"

#include <glm/glm.hpp>
#include <list>

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

	//MARK: Removable
	void ripMe() override;
	void setDelegate(RemovableDelegate* removableDelegate) override;

	//MARK: Selectable
	void leftPress() override;
	void leftRelease() override;
	void leftPosition(double xpos, double ypos) override;
	void resign() override;
	
	void middlePress() override;
	void middleRelease() override;

	bool mark() override;
	bool unmark() override;
	void setDelegate(SelectableDelegate* selectableDelegate) override;

private:
	class EdgePoint: public Selectable {
	public:
		EdgePoint(const glm::vec2& position);
		virtual ~EdgePoint();

		void draw() const override;
		void drawForPicking() const override;
		void leftPress() override;
		void leftRelease() override;
		void leftPosition(double xpos, double ypos) override;
		void resign() override;
		bool mark() override;
		bool unmark() override;

		const glm::vec2& getPosition() const;
		void setDefaultState();
		void addOffset(const glm::vec2& offset);
		void setParent(Line* parent);
		void setDelegate(SelectableDelegate* selectableDelegate) override;

	private:
		glm::vec2 position;
		Line* parent;

		glm::mat4 translation;
		glm::mat4 scale;
		glm::vec3 color;
		bool pressed, released;
		double xposPrev, yposPrev;

		void calcTranslation();
		const SquareMesh& mesh() const;
	};

	//MARK: fields
	glm::vec3 color;

	EdgePoint p1;
	EdgePoint p2;
	
	bool isRipped, pressed, released, moved, marked;
	double xposPrev, yposPrev;

	//MARK: private methods
	glm::mat4 calcTransformation() const;
	bool isBold() const;
	const LineMesh& mesh() const;

	glm::vec2 convertPos(double xpos, double ypos);
	
	//MARK: friens
	friend EdgePoint;
};

} /* namespace thesis */
