#pragma once
#include "../gui/Shape.h"
#include "../core/Point.h"

namespace nb{
namespace gl{
	class Polyline;
}}

namespace nb{
namespace gui{

class NB_API Polygon : public Shape
{
public:
	Polygon();
	virtual ~Polygon() = default;

	Property_rw<std::vector<Point>>	Points;				//�㼯��
	static DependencyProperty		PointsProperty();	//�㼯�ϵ���������

	virtual void onRender(std::shared_ptr<nb::gl::Context> drawContext) override;

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

};

}}
