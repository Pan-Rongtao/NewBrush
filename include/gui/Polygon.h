#pragma once
#include "../gui/Shape.h"

namespace nb{ namespace gui{

class NB_API Polygon : public Shape
{
public:
	Polygon();
	virtual ~Polygon() = default;

	Property_rw<std::vector<Point>>	Points;				//点集合
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

}}