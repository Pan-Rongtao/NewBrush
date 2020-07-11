#pragma once
#include "newbrush/media/AnimationTimeline.h"

namespace nb {
	
class NB_API BooleanAnimationBase : public AnimationTimeline
{
public:
	

protected:
	BooleanAnimationBase() = default;
};

class NB_API BooleanKeyFrame : public DependencyObject
{
public:
	BooleanKeyFrame();
	BooleanKeyFrame(const TimeSpan &keyTime, const bool &value);

	static DependencyPropertyPtr KeyTimeProperty();	//��ʼֵ��TimeSpan��Ĭ��ֵTimeSpan(0)��
	static DependencyPropertyPtr ValueProperty();	//�յ�ֵ��bool��Ĭ��ֵfalse��
	static DependencyPropertyPtr EasingFunctionProperty();	//��ʼֵ��std::shared_ptr<EasingBase>��Ĭ��ֵnullptr��

	bool operator < (const BooleanKeyFrame &other) const;
};

class NB_API BooleanAnimationUsingKeyFrames : public BooleanAnimationBase
{
public:
	std::set<BooleanKeyFrame> &keyFrames();

protected:
	virtual void onProcessing() override;

private:
	std::set<BooleanKeyFrame> m_keyFrames;
};


}