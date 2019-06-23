#pragma once
#include "../gui/Shape.h"

namespace nb{ namespace gl{
	class Line;
}}

namespace nb{ namespace gui{

class NB_API Line : public Shape
{
public:
	Line();
	virtual ~Line() = default;

public:
	nb::core::Property_rw<double>		X1;
	nb::core::Property_rw<double>		X2;
	nb::core::Property_rw<double>		Y1;
	nb::core::Property_rw<double>		Y2;

	virtual void onRender(std::shared_ptr<nb::gl::Context> drawContext) override;

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) override;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) override;

};

}}