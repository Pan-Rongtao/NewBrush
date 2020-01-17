﻿/*******************************************************
**	PropertyAnimation|ColorAnimation
**
**	属性动画
**
**	属性动画做为最常用的单动画体系，用来处理属性的变化过程。
**	它由TargetProperty指定目标属性，From、To指定属性的变化
**	初值和目标值，Easing指定缓动对象。
**
**	值得注意的是，使用PropertyAnimation模板类，必须实现了
**	operator +, operator -, operator *，来表达属性对于的
**	运算变化的支持
**
**		潘荣涛
**
********************************************************/
#pragma once
#include <type_traits>
#include "../core/Color.h"
#include "AnimationTimeline.h"
#include "../core/Easing.h"

namespace nb{

class NB_API FloatAnimation : public AnimationTimeline
{
public:
	FloatAnimation();
	FloatAnimation(float to, const TimeSpan &duration);
	FloatAnimation(float from, float to, const TimeSpan &duration);

	void setFrom(float from) &;
	float from() const;

	void setTo(float to) &;
	float to() const;

	void setEasingFunction(std::shared_ptr<EasingBase> easing);
	std::shared_ptr<EasingBase> easingFunction() const;
	
protected:
	virtual void onStateChanged();
	virtual void onProcessing() override;

private:
	float						m_from;
	float						m_to;
	float						m_actualFrom;
	float						m_actualTo;
	std::shared_ptr<EasingBase>	m_easingFunction;
};

//特化Color
//template<>
//void PropertyAnimation<Color>::progressing(float progress)
//{
/*	if (!TargetProperty)	return;

	decltype(progress) ft = (decltype(progress))Easing()->easeInCore(progress);
	int r = (int)((int)From().red() + ft * ((int)To().red() - (int)From().red()));
	int g = (int)((int)From().green() + ft * ((int)To().green() - (int)From().green()));
	int b = (int)((int)From().blue() + ft * ((int)To().blue() - (int)From().blue()));*/
	//set<Color>(*TargetProperty, Color(r, g, b));
	//(*TargetProperty)().setRgb(r, g, b);
//}

}