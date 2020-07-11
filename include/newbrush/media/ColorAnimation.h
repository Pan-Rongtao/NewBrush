#pragma once
#include "newbrush/media/AnimationTimeline.h"
#include "newbrush/media/Color.h"

namespace nb {
	
class NB_API ColorAnimationBase : public AnimationTimeline
{
public:
	

protected:
	ColorAnimationBase() = default;
};

class NB_API ColorAnimation : public ColorAnimationBase
{
public:
	ColorAnimation();
	ColorAnimation(const Color &toValue, const Duration &duration);
	ColorAnimation(const Color &toValue, const Duration &duration, FillBehaviorE fillBehavior);
	ColorAnimation(const Color &fromValue, const Color &toValue, const Duration &duration);
	ColorAnimation(const Color &fromValue, const Color &toValue, const Duration &duration, FillBehaviorE fillBehavior);

	static DependencyPropertyPtr FromProperty();			//��ʼֵ��optional<Color>��Ĭ��ֵnullopt��
	static DependencyPropertyPtr ToProperty();				//�յ�ֵ��optional<Color>��Ĭ��ֵnullopt��
	static DependencyPropertyPtr ByProperty();				//����ֵ��optional<Color>��Ĭ��ֵnullopt��
	static DependencyPropertyPtr EasingFunctionProperty();	//��ʼֵ��std::shared_ptr<EasingBase>��Ĭ��ֵnullptr��

protected:
	virtual void onProcessing() override;

private:
	static void onPropertyChanged(DependencyObject *d, const DependencyPropertyChangedEventArgs &e);

	void validateFromTo();

	Color m_actualFrom;
	Color m_actualTo;
	bool m_needToValidationFromTo{ false };
};

class NB_API ColorKeyFrame : public DependencyObject
{
public:
	ColorKeyFrame();
	ColorKeyFrame(const TimeSpan &keyTime, const Color &value);

	static DependencyPropertyPtr KeyTimeProperty();	//��ʼֵ��TimeSpan��Ĭ��ֵTimeSpan(0)��
	static DependencyPropertyPtr ValueProperty();	//�յ�ֵ��Color��Ĭ��ֵ0��
	static DependencyPropertyPtr EasingFunctionProperty();	//��ʼֵ��std::shared_ptr<EasingBase>��Ĭ��ֵnullptr��

	bool operator < (const ColorKeyFrame &other) const;
};

class NB_API ColorAnimationUsingKeyFrames : public ColorAnimationBase
{
public:
	std::set<ColorKeyFrame> &keyFrames();

protected:
	virtual void onProcessing() override;

private:
	std::set<ColorKeyFrame> m_keyFrames;
};


}