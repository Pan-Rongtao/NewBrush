#pragma once
#include "newbrush/media/AnimationTimeline.h"

namespace nb {
	
class NB_API Int32AnimationBase : public AnimationTimeline
{
public:
	

protected:
	Int32AnimationBase() = default;
};

class NB_API Int32Animation : public Int32AnimationBase
{
public:
	Int32Animation();
	Int32Animation(int32_t toValue, const Duration &duration);
	Int32Animation(int32_t toValue, const Duration &duration, FillBehaviorE fillBehavior);
	Int32Animation(int32_t fromValue, int32_t toValue, const Duration &duration);
	Int32Animation(int32_t fromValue, int32_t toValue, const Duration &duration, FillBehaviorE fillBehavior);

	static DependencyPropertyPtr FromProperty();			//��ʼֵ��optional<int32_t>��Ĭ��ֵnullopt��
	static DependencyPropertyPtr ToProperty();				//�յ�ֵ��optional<int32_t>��Ĭ��ֵnullopt��
	static DependencyPropertyPtr ByProperty();				//����ֵ��optional<int32_t>��Ĭ��ֵnullopt��
	static DependencyPropertyPtr EasingFunctionProperty();	//��ʼֵ��std::shared_ptr<EasingBase>��Ĭ��ֵnullptr��

protected:
	virtual void onProcessing() override;

private:
	static void onPropertyChanged(DependencyObject *d, const DependencyPropertyChangedEventArgs &e);

	void validateFromTo();

	int32_t m_actualFrom;
	int32_t m_actualTo;
	bool m_needToValidationFromTo{ false };
};

class NB_API Int32KeyFrame : public DependencyObject
{
public:
	Int32KeyFrame();
	Int32KeyFrame(const TimeSpan &keyTime, int32_t value);

	static DependencyPropertyPtr KeyTimeProperty();	//��ʼֵ��TimeSpan��Ĭ��ֵTimeSpan(0)��
	static DependencyPropertyPtr ValueProperty();	//�յ�ֵ��int32_t��Ĭ��ֵ0��
	static DependencyPropertyPtr EasingFunctionProperty();	//��ʼֵ��std::shared_ptr<EasingBase>��Ĭ��ֵnullptr��

	bool operator < (const Int32KeyFrame &other) const;
};

class NB_API Int32AnimationUsingKeyFrames : public Int32AnimationBase
{
public:
	std::set<Int32KeyFrame> &keyFrames();

protected:
	virtual void onProcessing() override;

private:
	std::set<Int32KeyFrame> m_keyFrames;
};


}