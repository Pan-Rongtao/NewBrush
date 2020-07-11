#pragma once
#include "newbrush/media/AnimationTimeline.h"

namespace nb {
	
class NB_API StringAnimationBase : public AnimationTimeline
{
public:
	

protected:
	StringAnimationBase() = default;
};

class NB_API StringKeyFrame : public DependencyObject
{
public:
	StringKeyFrame();
	StringKeyFrame(const TimeSpan &keyTime, const std::string &value);

	static DependencyPropertyPtr KeyTimeProperty();	//��ʼֵ��TimeSpan��Ĭ��ֵTimeSpan(0)��
	static DependencyPropertyPtr ValueProperty();	//�յ�ֵ��std::string��Ĭ��ֵ""��
	static DependencyPropertyPtr EasingFunctionProperty();	//��ʼֵ��std::shared_ptr<EasingBase>��Ĭ��ֵnullptr��

	bool operator < (const StringKeyFrame &other) const;
};

class NB_API StringAnimationUsingKeyFrames : public StringAnimationBase
{
public:
	std::set<StringKeyFrame> &keyFrames();

protected:
	virtual void onProcessing() override;

private:
	std::set<StringKeyFrame> m_keyFrames;
};


}