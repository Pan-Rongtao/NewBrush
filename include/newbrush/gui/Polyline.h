#pragma once
#include "newbrush/gui/Shape.h"

namespace nb{

class NB_API Polyline : public Shape
{
	NB_OBJECT
public:
	Polyline();
	virtual ~Polyline() = default;

	static DependencyPropertyPtr PointsProperty();	//�㼯�ϵ���������

	virtual void onRender(Viewport2D & drawContext) override;

protected:
	virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args) override;
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

private:
	void updateStrokeObject(const Rect &rc);
};

}