#pragma once
#include "../gui/Shape.h"

namespace nb{ namespace gui{

class NB_API Polyline : public Shape
{
public:
	Polyline();
	virtual ~Polyline() = default;

	Property_rw<std::vector<Point>>	Points;				//�㼯��
	static DependencyProperty		PointsProperty();	//�㼯�ϵ���������

	virtual void onRender(std::shared_ptr<nb::Context> drawContext) override;

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

private:
	void updateStrokeObject(const Rect &rc);
};

}}