#pragma once
#include "newbrush/gui/shapes/Shape.h"

namespace nb{

class NB_API Polygon : public Shape
{
	RTTR_ENABLE(Shape)
public:
	Polygon() = default;
	virtual ~Polygon() = default;

	static DependencyPropertyPtr PointsProperty();	//�㼯�ϵ���������

	virtual void onRender(DrawingContextPtr dc) override;

protected:
	virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args) override;
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

};

}