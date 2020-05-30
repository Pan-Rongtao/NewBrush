/*******************************************************
**	RotateTransform
**
**�ڶ�ά x-y ����ϵ���������Ϊ���ĵ�ͼ����ת��ֻ��Ҫ��ƽ�ƺ���ת������ϼ���
**		���裺
**		1.	�Ƚ�����ϵƽ�Ƶ�ָ����
**		2.	�����µ�����ԭ��Ϊ������ת
**		3.	Ȼ���µ�����ԭ��ƽ�ƻ�ԭ����ϵԭ��
**
********************************************************/

#pragma once
#include "newbrush/media/Transform.h"

namespace nb {

	class NB_API RotateTransform : public Transform
	{
	public:
		RotateTransform();
		RotateTransform(float angle);
		RotateTransform(float angle, float centerX, float centerY);
		virtual ~RotateTransform() = default;

		static DependencyPropertyPtr AngleProperty();
		static DependencyPropertyPtr CenterXProperty();
		static DependencyPropertyPtr CenterYProperty();

		virtual glm::mat4x4 value() override;

	};
}