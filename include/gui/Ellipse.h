#pragma once
#include "../gui/Shape.h"

namespace nb{ namespace gui{

class NB_API Ellipse : public Shape
{
public:
	Ellipse();

public:
	virtual void onRender(std::shared_ptr<nb::gl::Context> drawContext) override;

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) override;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) override;

};

}}