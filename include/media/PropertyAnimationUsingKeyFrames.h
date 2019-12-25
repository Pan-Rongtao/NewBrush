/*******************************************************
**	KeyFrame|PropertyAnimationUsingKeyFrames
**
**	�ؼ�֡��ؼ�֡����
**
**	�ؼ�֡��ʾ�ڶ����д��ڹؼ�״̬�����ݽṹ����ʹ����ʱ��㡢
**	ֵ��Easing�⼸������������һ���ؼ�֡��
**
**	���ؼ�֡���������һϵ�йؼ�֡��Ϊ������ִ�е����ݡ�����
**	�����ǹؼ�֡��ɵĴ��ж�����
**
**
**		������
**
********************************************************/

#pragma once
#include <set>
#include "../core/Property.h"
#include "../core/TimeSpan.h"
#include "AnimationTimeline.h"
#include "../core/Easing.h"

namespace nb{ namespace gui{

template<class T>
class NB_API KeyFrame : public DependencyObject
{
public:
	KeyFrame() : KeyFrame(T(), TimeSpan(), std::make_shared<LinearEase>()) {}
	KeyFrame(const T &value, const TimeSpan &keyTime) : KeyFrame(value, keyTime, std::make_shared<LinearEase>()) {}
	KeyFrame(const T &value, const TimeSpan &keyTime, shared_ptr<EasingBase> easing) 
		: Value([&](T v) { set(ValueProperty(), v); }, [&]()->T& {return get<T>(ValueProperty()); })
		, KeyTime([&](TimeSpan v) { set(KeyTimeProperty(), v); }, [&]()->TimeSpan& {return get<TimeSpan>(KeyTimeProperty()); })
		, Easing([&](shared_ptr<EasingBase> v) { set(EasingProperty(), v); }, [&]()->shared_ptr<EasingBase>& {return get<shared_ptr<EasingBase>>(EasingProperty()); })
	{
		KeyTime = keyTime;
		Value = value;
		Easing = easing;
	}
	bool operator < (const KeyFrame<T> &other) const { return KeyTime() < other.KeyTime(); }
	bool operator ==(const KeyFrame<T> &other) const { return KeyTime() == other.KeyTime(); }
	bool operator !=(const KeyFrame<T> &other) const { return KeyTime() != other.KeyTime(); }

	Property_rw<T>						Value;
	Property_rw<TimeSpan>				KeyTime;
	Property_rw<shared_ptr<EasingBase>>	Easing;
	static DependencyProperty	ValueProperty() { static auto dp = DependencyProperty::registerDependency<KeyFrame, T>("Value", T()); return dp; }
	static DependencyProperty	KeyTimeProperty() { static auto dp = DependencyProperty::registerDependency<KeyFrame, TimeSpan>("KeyTime", TimeSpan()); return dp; }
	static DependencyProperty	EasingProperty() { static auto dp = DependencyProperty::registerDependency<KeyFrame, shared_ptr<EasingBase>>("Easing", std::make_shared<LinearEase>()); return dp; }
};

template<class T>
class NB_API PropertyAnimationUsingKeyFrames : public AnimationTimeline<T>
{
public:
	PropertyAnimationUsingKeyFrames()
		: KeyFrames([&](std::set<shared_ptr<KeyFrame<T>>> v) { set(KeyFramesProperty(), v); }, [&]()->std::set<shared_ptr<KeyFrame<T>>>& {return get<std::set<shared_ptr<KeyFrame<T>>>>(KeyFramesProperty()); })
	{}

	Property_rw<std::set<shared_ptr<KeyFrame<T>>>>	KeyFrames;
	static DependencyProperty	KeyFramesProperty() { static auto dp = DependencyProperty::registerDependency<PropertyAnimationUsingKeyFrames, std::set<shared_ptr<KeyFrame<T>>>>("KeyFrames", {}); return dp; }

protected:
	virtual void progressing(float progress) override
	{
		if (!TargetProperty || KeyFrames().empty())	return;
		//����ticks��ȡ��ǰframe���Ҳ�����ʾ�����˷�Χ
		auto getCurrentFrame = [&](int64_t ticks)->std::set<shared_ptr<KeyFrame<T>>>::iterator
		{
			for (auto iter = KeyFrames().begin(); iter != KeyFrames().end(); ++iter)
			{
				auto k = (*iter)->KeyTime().totalMilliseconds();
				if (ticks <= k)
					return iter;
			}
			return KeyFrames().end();
		};

		int64_t ticks = (int64_t)(Duration().totalMilliseconds() * progress);
		auto curFrameIter = getCurrentFrame(ticks);
		if (curFrameIter != KeyFrames().end())
		{
			auto curFrame = *curFrameIter;
			auto prevFrameIter = (curFrameIter == KeyFrames().begin()) ? KeyFrames().end() : --curFrameIter;
			T fromValue = (prevFrameIter == KeyFrames().end()) ? curFrame->Value() : (*prevFrameIter)->Value();
			T toValue = curFrame->Value();
			int64_t frameBegTick = (prevFrameIter == KeyFrames().end() ? 0 : (int64_t)(*prevFrameIter)->KeyTime().totalMilliseconds());
			int64_t frameEndTick = (int64_t)curFrame->KeyTime().totalMilliseconds();
			auto t = (double)(ticks - frameBegTick) / (frameEndTick - frameBegTick);
			decltype(progress) ft = (decltype(progress))curFrame->Easing()->easeInCore(progress);
			//auto ft = curFrame.Easing()->easeInCore(t);
			*TargetProperty = fromValue + (toValue - fromValue) * ft;
		}
	}
};

}}