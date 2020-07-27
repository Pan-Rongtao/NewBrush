#pragma once
#include "newbrush/core/media/animation/AnimationTimeline.h"
#include "newbrush/core/base/Rect.h"

namespace nb {
	
class NB_API RectAnimationBase : public AnimationTimeline
{
public:
	

protected:
	RectAnimationBase() = default;
};

class NB_API RectAnimation : public RectAnimationBase
{
public:
	RectAnimation();
	RectAnimation(const Rect &toValue, const Duration &duration);
	RectAnimation(const Rect &toValue, const Duration &duration, FillBehaviorE fillBehavior);
	RectAnimation(const Rect &fromValue, const Rect &toValue, const Duration &duration);
	RectAnimation(const Rect &fromValue, const Rect &toValue, const Duration &duration, FillBehaviorE fillBehavior);

	static DependencyPropertyPtr FromProperty();			//��ʼֵ��optional<Rect>��Ĭ��ֵnullopt��
	static DependencyPropertyPtr ToProperty();				//�յ�ֵ��optional<Rect>��Ĭ��ֵnullopt��
	static DependencyPropertyPtr ByProperty();				//����ֵ��optional<Rect>��Ĭ��ֵnullopt��
	static DependencyPropertyPtr EasingFunctionProperty();	//��ʼֵ��std::shared_ptr<EasingBase>��Ĭ��ֵnullptr��

protected:
	virtual void onProcessing() override;

private:
	static void onPropertyChanged(DependencyObject *d, const DependencyPropertyChangedEventArgs &e);

	void validateFromTo();

	Rect m_actualFrom;
	Rect m_actualTo;
	bool m_needToValidationFromTo{ false };
};

class NB_API RectKeyFrame : public DependencyObject
{
public:
	RectKeyFrame();
	RectKeyFrame(const TimeSpan &keyTime, const Rect &value);

	static DependencyPropertyPtr KeyTimeProperty();	//��ʼֵ��TimeSpan��Ĭ��ֵTimeSpan(0)��
	static DependencyPropertyPtr ValueProperty();	//�յ�ֵ��Rect��Ĭ��ֵ0��
	static DependencyPropertyPtr EasingFunctionProperty();	//��ʼֵ��std::shared_ptr<EasingBase>��Ĭ��ֵnullptr��

	bool operator < (const RectKeyFrame &other) const;
};

class NB_API RectAnimationUsingKeyFrames : public RectAnimationBase
{
public:
	std::set<RectKeyFrame> &keyFrames();

protected:
	virtual void onProcessing() override;

private:
	std::set<RectKeyFrame> m_keyFrames;
};


}