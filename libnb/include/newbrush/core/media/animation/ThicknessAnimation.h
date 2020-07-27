#pragma once
#include "newbrush/core/media/animation/AnimationTimeline.h"
#include "newbrush/core/base/Thickness.h"

namespace nb {
	
class NB_API ThicknessAnimationBase : public AnimationTimeline
{
public:
	

protected:
	ThicknessAnimationBase() = default;
};

class NB_API ThicknessAnimation : public ThicknessAnimationBase
{
public:
	ThicknessAnimation();
	ThicknessAnimation(const Thickness &toValue, const Duration &duration);
	ThicknessAnimation(const Thickness &toValue, const Duration &duration, FillBehaviorE fillBehavior);
	ThicknessAnimation(const Thickness &fromValue, const Thickness &toValue, const Duration &duration);
	ThicknessAnimation(const Thickness &fromValue, const Thickness &toValue, const Duration &duration, FillBehaviorE fillBehavior);

	static DependencyPropertyPtr FromProperty();			//��ʼֵ��optional<Thickness>��Ĭ��ֵnullopt��
	static DependencyPropertyPtr ToProperty();				//�յ�ֵ��optional<Thickness>��Ĭ��ֵnullopt��
	static DependencyPropertyPtr ByProperty();				//����ֵ��optional<Thickness>��Ĭ��ֵnullopt��
	static DependencyPropertyPtr EasingFunctionProperty();	//��ʼֵ��std::shared_ptr<EasingBase>��Ĭ��ֵnullptr��

protected:
	virtual void onProcessing() override;

private:
	static void onPropertyChanged(DependencyObject *d, const DependencyPropertyChangedEventArgs &e);

	void validateFromTo();

	Thickness m_actualFrom;
	Thickness m_actualTo;
	bool m_needToValidationFromTo{ false };
};

class NB_API ThicknessKeyFrame : public DependencyObject
{
public:
	ThicknessKeyFrame();
	ThicknessKeyFrame(const TimeSpan &keyTime, const Thickness &value);

	static DependencyPropertyPtr KeyTimeProperty();	//��ʼֵ��TimeSpan��Ĭ��ֵTimeSpan(0)��
	static DependencyPropertyPtr ValueProperty();	//�յ�ֵ��Thickness��Ĭ��ֵ0��
	static DependencyPropertyPtr EasingFunctionProperty();	//��ʼֵ��std::shared_ptr<EasingBase>��Ĭ��ֵnullptr��

	bool operator < (const ThicknessKeyFrame &other) const;
};

class NB_API ThicknessAnimationUsingKeyFrames : public ThicknessAnimationBase
{
public:
	std::set<ThicknessKeyFrame> &keyFrames();

protected:
	virtual void onProcessing() override;

private:
	std::set<ThicknessKeyFrame> m_keyFrames;
};


}