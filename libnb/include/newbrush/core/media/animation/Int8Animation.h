#pragma once
#include "newbrush/core/media/animation/AnimationTimeline.h"

namespace nb {
	
class NB_API Int8AnimationBase : public AnimationTimeline
{
public:
	

protected:
	Int8AnimationBase() = default;
};

class NB_API Int8Animation : public Int8AnimationBase
{
public:
	Int8Animation();
	Int8Animation(int8_t toValue, const Duration &duration);
	Int8Animation(int8_t toValue, const Duration &duration, FillBehaviorE fillBehavior);
	Int8Animation(int8_t fromValue, int8_t toValue, const Duration &duration);
	Int8Animation(int8_t fromValue, int8_t toValue, const Duration &duration, FillBehaviorE fillBehavior);

	static DependencyPropertyPtr FromProperty();			//��ʼֵ��optional<int8_t>��Ĭ��ֵnullopt��
	static DependencyPropertyPtr ToProperty();				//�յ�ֵ��optional<int8_t>��Ĭ��ֵnullopt��
	static DependencyPropertyPtr ByProperty();				//����ֵ��optional<int8_t>��Ĭ��ֵnullopt��
	static DependencyPropertyPtr EasingFunctionProperty();	//��ʼֵ��std::shared_ptr<EasingBase>��Ĭ��ֵnullptr��

protected:
	virtual void onProcessing() override;

private:
	static void onPropertyChanged(DependencyObject *d, const DependencyPropertyChangedEventArgs &e);

	void validateFromTo();

	int8_t m_actualFrom;
	int8_t m_actualTo;
	bool m_needToValidationFromTo{ false };
};

class NB_API Int8KeyFrame : public DependencyObject
{
public:
	Int8KeyFrame();
	Int8KeyFrame(const TimeSpan &keyTime, int8_t value);

	static DependencyPropertyPtr KeyTimeProperty();	//��ʼֵ��TimeSpan��Ĭ��ֵTimeSpan(0)��
	static DependencyPropertyPtr ValueProperty();	//�յ�ֵ��int8_t��Ĭ��ֵ0��
	static DependencyPropertyPtr EasingFunctionProperty();	//��ʼֵ��std::shared_ptr<EasingBase>��Ĭ��ֵnullptr��

	bool operator < (const Int8KeyFrame &other) const;
};

class NB_API Int8AnimationUsingKeyFrames : public Int8AnimationBase
{
public:
	std::set<Int8KeyFrame> &keyFrames();

protected:
	virtual void onProcessing() override;

private:
	std::set<Int8KeyFrame> m_keyFrames;
};

}