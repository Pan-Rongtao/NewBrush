#pragma once
#include "../TestBase.h"
#include "media/Timeline.h"

using namespace nb;
using namespace nb::gui;
class TestTimeline : public TestBase
{
public:
	void test();

	void onStateChanged(const Timeline::StateChangedArgs &args);
	void onProgress(const Timeline::ProgressArgs &args);
	void onCompleted(const Timeline::CompleteArgs &args);

	Timeline m_tl;
};