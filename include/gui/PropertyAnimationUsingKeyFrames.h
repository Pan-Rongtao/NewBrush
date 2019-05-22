#pragma once
#include <set>
#include "../core/Property.h"
#include "../core/TimeSpan.h"
#include "AnimationTimeline.h"
#include "Easing.h"

namespace nb{ namespace gui{

template<class T>
class NB_API KeyFrame
{
public:
	KeyFrame() : KeyFrame(T(), TimeSpan(), std::make_shared<LinearEase>()) {}
	KeyFrame(const core::Property_rw<T> &value, const core::TimeSpan &keyTime) : KeyFrame(value, keyTime, std::make_shared<LinearEase>()) {}
	KeyFrame(const core::Property_rw<T> &value, const core::TimeSpan &keyTime, std::shared_ptr<EasingBase> easing) : Value(value), KeyTime(keyTime), Easing(easing) {}

	bool operator < (const KeyFrame<T> &other) const
	{
		return KeyTime() < other.KeyTime();
	}

	core::Property_rw<T>							Value;
	core::Property_rw<core::TimeSpan>				KeyTime;
	core::Property_rw<std::shared_ptr<EasingBase>>	Easing;
};

template<class T>
class NB_API PropertyAnimationUsingKeyFrames : public AnimationTimeline
{
public:
	void beginAnimation(core::Property_rw<T> *property)
	{
		TargetProperty = property;
		start();
	}

	core::Property_rw<T>							*TargetProperty;
	core::Property_rw<std::set<KeyFrame<T>>>		KeyFrames;

protected:
	virtual void progressing(double progress) override;
};

}
template<class T>
inline void gui::PropertyAnimationUsingKeyFrames<T>::progressing(double progress)
{
	if (KeyFrames().empty())	return;

	auto getCurrentFrame = [&](int64_t ticks) ->std::set<KeyFrame<T>>::iterator {
		for (auto iter = KeyFrames().begin(); iter != KeyFrames().end(); ++iter)
		{
			if (ticks <= (*iter).KeyTime().totalMilliseconds())
				return iter;
		}
		return KeyFrames().end();
	};

	int64_t ticks = (int64_t)(Duration().totalMilliseconds() * progress);
	auto curFrameIter = getCurrentFrame(ticks);
	if (curFrameIter != KeyFrames().end())
	{
		const KeyFrame<T> &curFrame = *curFrameIter;
		auto prevFrameIter = (curFrameIter == KeyFrames().begin()) ? KeyFrames().end() : --curFrameIter;
		T fromValue = (prevFrameIter == KeyFrames().end()) ? curFrame.Value : (*prevFrameIter).Value();
		T toValue = curFrame.Value();
		int64_t frmeBegTick = (prevFrameIter == KeyFrames().end() ? 0 : (*prevFrameIter).KeyTime().totalMilliseconds());
		int64_t frameEndTick = curFrame.KeyTime().totalMilliseconds();
		double t = (double)(ticks - frmeBegTick) / (double)(frameEndTick - frmeBegTick);
		auto ft = curFrame.Easing()->easeInCore(t);
		*TargetProperty = fromValue + (toValue - fromValue) * ft;
	}
}
}