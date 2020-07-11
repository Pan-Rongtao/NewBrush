#pragma once
#include "newbrush/media/AnimationTimeline.h"

namespace nb {
	
class NB_API Int64AnimationBase : public AnimationTimeline
{
public:
	

protected:
	Int64AnimationBase() = default;
};

class NB_API Int64Animation : public Int64AnimationBase
{
public:
	Int64Animation();
	Int64Animation(int64_t toValue, const Duration &duration);
	Int64Animation(int64_t toValue, const Duration &duration, FillBehaviorE fillBehavior);
	Int64Animation(int64_t fromValue, int64_t toValue, const Duration &duration);
	Int64Animation(int64_t fromValue, int64_t toValue, const Duration &duration, FillBehaviorE fillBehavior);

	static DependencyPropertyPtr FromProperty();			//��ʼֵ��optional<int64_t>��Ĭ��ֵnullopt��
	static DependencyPropertyPtr ToProperty();				//�յ�ֵ��optional<int64_t>��Ĭ��ֵnullopt��
	static DependencyPropertyPtr ByProperty();				//����ֵ��optional<int64_t>��Ĭ��ֵnullopt��
	static DependencyPropertyPtr EasingFunctionProperty();	//��ʼֵ��std::shared_ptr<EasingBase>��Ĭ��ֵnullptr��

protected:
	virtual void onProcessing() override;

private:
	static void onPropertyChanged(DependencyObject *d, const DependencyPropertyChangedEventArgs &e);

	void validateFromTo();

	int64_t m_actualFrom;
	int64_t m_actualTo;
	bool m_needToValidationFromTo{ false };
};

class NB_API Int64KeyFrame : public DependencyObject
{
public:
	Int64KeyFrame();
	Int64KeyFrame(const TimeSpan &keyTime, int64_t value);

	static DependencyPropertyPtr KeyTimeProperty();	//��ʼֵ��TimeSpan��Ĭ��ֵTimeSpan(0)��
	static DependencyPropertyPtr ValueProperty();	//�յ�ֵ��int64_t��Ĭ��ֵ0��
	static DependencyPropertyPtr EasingFunctionProperty();	//��ʼֵ��std::shared_ptr<EasingBase>��Ĭ��ֵnullptr��

	bool operator < (const Int64KeyFrame &other) const;
};

class NB_API Int64AnimationUsingKeyFrames : public Int64AnimationBase
{
public:
	std::set<Int64KeyFrame> &keyFrames();

protected:
	virtual void onProcessing() override;

private:
	std::set<Int64KeyFrame> m_keyFrames;
};


}