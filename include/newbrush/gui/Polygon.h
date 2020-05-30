#pragma once
#include "newbrush/gui/Shape.h"

namespace nb{

class NB_API Polygon : public Shape
{
	RTTR_ENABLE(Shape)
	NB_OBJECT
public:
	Polygon();
	virtual ~Polygon() = default;

	static DependencyProperty		PointsProperty();	//点集合的依赖属性

	virtual void onRender(Viewport2D & drawContext) override;

protected:
	virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args) override;
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

private:
	void updateFillObject();
	void updateStrokeObject();
};

}