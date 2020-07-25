#pragma once
#include "newbrush/gui/shapes/Shape.h"

namespace nb{

class NB_API Line : public Shape
{
	RTTR_ENABLE(Shape)
public:
	static DependencyPropertyPtr X1Property();	//X1����������
	static DependencyPropertyPtr X2Property();	//X2����������
	static DependencyPropertyPtr Y1Property();	//Y1����������
	static DependencyPropertyPtr Y2Property();	//Y2����������

	virtual void onRender(DrawingContextPtr dc) override;

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

};

}