#pragma once
#include "../TestBase.h"
#include "core/Point.h"
#include "core/Color.h"
#include "media/PropertyAnimation.h"

using namespace nb;
using namespace nb::gui;

class TestPropertyAnimation : public TestBase
{
public:
	TestPropertyAnimation();
	void test();

	Property_rw<double>			Width;
	PropertyAnimation<double>	doubleAni;

	Property_rw<Point>			Position;
	PropertyAnimation<Point>	pointAni;

	Property_rw<Color>			Background;
	PropertyAnimation<Color>	colorAni;

private:
	void onStateChanged(const Timeline::StateChangedArgs &args);
	void onProgress(const Timeline::ProgressArgs &args);
	void onCompleted(const Timeline::CompleteArgs &args);

	double	m_double;
	Point	m_point;
	Color	m_color;
};