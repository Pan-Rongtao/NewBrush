﻿#include "gui/PropertyAnimation.h"
#include "gui/Storyboard.h"

using namespace nb::core;
using namespace nb::gui;

ColorAnimation::ColorAnimation()
	: TargetProperty(nullptr)
	, Easing(std::make_shared<LinearEase>())
{
	ProgressEvent += [&](const Timeline::ProgressArgs &args)
	{
		auto t = args.progress;
		auto ft = Easing()->easeInCore(t);
		int r = 0, g = 0, b = 0;
		r = (int)((int)From().red() + ft * ((int)To().red() - (int)From().red()));
		g = (int)((int)From().green() + ft * ((int)To().green() - (int)From().green()));
		b = (int)((int)From().blue() + ft * ((int)To().blue() - (int)From().blue()));
		*TargetProperty = Color(r, g, b);
	};
}

void ColorAnimation::beginAinimation(Property_rw<Color>* property)
{
	TargetProperty = property;
	start();
}
