#pragma once
#include "newbrush/core/media/animation/AnimationTimeline.h"

namespace nb {
	
class NB_API FloatAnimationBase : public AnimationTimeline
{
public:
	

protected:
	FloatAnimationBase() = default;
};

class NB_API FloatAnimation : public FloatAnimationBase
{
public:
	FloatAnimation();
	FloatAnimation(float toValue, const Duration &duration);
	FloatAnimation(float toValue, const Duration &duration, FillBehaviorE fillBehavior);
	FloatAnimation(float fromValue, float toValue, const Duration &duration);
	FloatAnimation(float fromValue, float toValue, const Duration &duration, FillBehaviorE fillBehavior);

	static DependencyPropertyPtr FromProperty();			//��ʼֵ��optional<float>��Ĭ��ֵnullopt��
	static DependencyPropertyPtr ToProperty();				//�յ�ֵ��optional<float>��Ĭ��ֵnullopt��
	static DependencyPropertyPtr ByProperty();				//����ֵ��optional<float>��Ĭ��ֵnullopt��
	static DependencyPropertyPtr EasingFunctionProperty();	//��ʼֵ��std::shared_ptr<EasingBase>��Ĭ��ֵnullptr��

protected:
	virtual void onProcessing() override;

private:
	static void onPropertyChanged(DependencyObject *d, const DependencyPropertyChangedEventArgs &e);

	void validateFromTo();

	float m_actualFrom;
	float m_actualTo;
	bool m_needToValidationFromTo{ false };
};

class NB_API FloatKeyFrame : public DependencyObject
{
public:
	FloatKeyFrame();
	FloatKeyFrame(const TimeSpan &keyTime, float value);

	static DependencyPropertyPtr KeyTimeProperty();	//��ʼֵ��TimeSpan��Ĭ��ֵTimeSpan(0)��
	static DependencyPropertyPtr ValueProperty();	//�յ�ֵ��float��Ĭ��ֵ0��
	static DependencyPropertyPtr EasingFunctionProperty();	//��ʼֵ��std::shared_ptr<EasingBase>��Ĭ��ֵnullptr��

	bool operator < (const FloatKeyFrame &other) const;
};

class NB_API FloatAnimationUsingKeyFrames : public FloatAnimationBase
{
public:
	std::set<FloatKeyFrame> &keyFrames();

protected:
	virtual void onProcessing() override;

private:
	std::set<FloatKeyFrame> m_keyFrames;
};


}