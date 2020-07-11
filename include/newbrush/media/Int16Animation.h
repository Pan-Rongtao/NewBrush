#pragma once
#include "newbrush/media/AnimationTimeline.h"

namespace nb {
	
class NB_API Int16AnimationBase : public AnimationTimeline
{
public:
	

protected:
	Int16AnimationBase() = default;
};

class NB_API Int16Animation : public Int16AnimationBase
{
public:
	Int16Animation();
	Int16Animation(int16_t toValue, const Duration &duration);
	Int16Animation(int16_t toValue, const Duration &duration, FillBehaviorE fillBehavior);
	Int16Animation(int16_t fromValue, int16_t toValue, const Duration &duration);
	Int16Animation(int16_t fromValue, int16_t toValue, const Duration &duration, FillBehaviorE fillBehavior);

	static DependencyPropertyPtr FromProperty();			//��ʼֵ��optional<int16_t>��Ĭ��ֵnullopt��
	static DependencyPropertyPtr ToProperty();				//�յ�ֵ��optional<int16_t>��Ĭ��ֵnullopt��
	static DependencyPropertyPtr ByProperty();				//����ֵ��optional<int16_t>��Ĭ��ֵnullopt��
	static DependencyPropertyPtr EasingFunctionProperty();	//��ʼֵ��std::shared_ptr<EasingBase>��Ĭ��ֵnullptr��

protected:
	virtual void onProcessing() override;

private:
	static void onPropertyChanged(DependencyObject *d, const DependencyPropertyChangedEventArgs &e);

	void validateFromTo();

	int16_t m_actualFrom;
	int16_t m_actualTo;
	bool m_needToValidationFromTo{ false };
};

class NB_API Int16KeyFrame : public DependencyObject
{
public:
	Int16KeyFrame();
	Int16KeyFrame(const TimeSpan &keyTime, int16_t value);

	static DependencyPropertyPtr KeyTimeProperty();	//��ʼֵ��TimeSpan��Ĭ��ֵTimeSpan(0)��
	static DependencyPropertyPtr ValueProperty();	//�յ�ֵ��int16_t��Ĭ��ֵ0��
	static DependencyPropertyPtr EasingFunctionProperty();	//��ʼֵ��std::shared_ptr<EasingBase>��Ĭ��ֵnullptr��

	bool operator < (const Int16KeyFrame &other) const;
};

class NB_API Int16AnimationUsingKeyFrames : public Int16AnimationBase
{
public:
	std::set<Int16KeyFrame> &keyFrames();

protected:
	virtual void onProcessing() override;

private:
	std::set<Int16KeyFrame> m_keyFrames;
};


}