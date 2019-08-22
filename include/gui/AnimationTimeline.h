﻿#pragma once
#include "Timeline.h"
#include "../core/Easing.h"
#include "../gui/DependencyProperty.h"

namespace nb{
namespace gui{

template<class T>
class NB_API AnimationTimeline : public Timeline
{
public:
	AnimationTimeline()
		//: TargetProperty([&](Property_rw<T> *v) {set(TargetPropertyProperty(), v); }, [&]() {return get<Property_rw<T> *>(TargetPropertyProperty()); })
		: Easing(nullptr, nullptr)
	{
		ProgressEvent += [&](const Timeline::ProgressArgs &args) {	progressing(args.progress);	};
	}
	virtual ~AnimationTimeline() = default;

	//Property_rw<T>					*TargetProperty;
	Property_rw<std::shared_ptr<EasingBase>>	Easing;

	static DependencyProperty	TargetPropertyProperty() { return DependencyProperty; }
	static DependencyProperty	EasingProperty()		{ return DependencyProperty; }

protected:
	virtual void progressing(float progress) = 0;

};

}}