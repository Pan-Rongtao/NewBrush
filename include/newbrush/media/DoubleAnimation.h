#pragma once
#include "newbrush/media/AnimationTimeline.h"

namespace nb {
	
class NB_API DoubleAnimationBase : public AnimationTimeline
{
public:
	

protected:
	DoubleAnimationBase() = default;
};

class NB_API DoubleAnimation : public DoubleAnimationBase
{
public:
	DoubleAnimation();
	DoubleAnimation(double toValue, const Duration &duration);
	DoubleAnimation(double toValue, const Duration &duration, FillBehaviorE fillBehavior);
	DoubleAnimation(double fromValue, double toValue, const Duration &duration);
	DoubleAnimation(double fromValue, double toValue, const Duration &duration, FillBehaviorE fillBehavior);

	static DependencyPropertyPtr FromProperty();			//��ʼֵ��optional<double>��Ĭ��ֵnullopt��
	static DependencyPropertyPtr ToProperty();				//�յ�ֵ��optional<double>��Ĭ��ֵnullopt��
	static DependencyPropertyPtr ByProperty();				//����ֵ��optional<double>��Ĭ��ֵnullopt��
	static DependencyPropertyPtr EasingFunctionProperty();	//��ʼֵ��std::shared_ptr<EasingBase>��Ĭ��ֵnullptr��

protected:
	virtual void onProcessing() override;

private:
	static void onPropertyChanged(DependencyObject *d, const DependencyPropertyChangedEventArgs &e);

	void validateFromTo();

	double m_actualFrom;
	double m_actualTo;
	bool m_needToValidationFromTo{ false };
};

class NB_API DoubleKeyFrame : public DependencyObject
{
public:
	DoubleKeyFrame();
	DoubleKeyFrame(const TimeSpan &keyTime, double value);

	static DependencyPropertyPtr KeyTimeProperty();	//��ʼֵ��TimeSpan��Ĭ��ֵTimeSpan(0)��
	static DependencyPropertyPtr ValueProperty();	//�յ�ֵ��double��Ĭ��ֵ0��
	static DependencyPropertyPtr EasingFunctionProperty();	//��ʼֵ��std::shared_ptr<EasingBase>��Ĭ��ֵnullptr��

	bool operator < (const DoubleKeyFrame &other) const;
};

class NB_API DoubleAnimationUsingKeyFrames : public DoubleAnimationBase
{
public:
	std::set<DoubleKeyFrame> &keyFrames();

protected:
	virtual void onProcessing() override;

private:
	std::set<DoubleKeyFrame> m_keyFrames;
};


}