﻿#pragma once
#include "../gui/Shape.h"

namespace nb { namespace gui {

class NB_API Rectangle : public Shape
{
public:
	Rectangle();
	virtual ~Rectangle();

public:
	nb::core::Property_rw<double>		RadiusX;
	nb::core::Property_rw<double>		RadiusY;

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) const;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) const;

};

}}
