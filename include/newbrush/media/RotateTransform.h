/*******************************************************
**	RotateTransform
**
**�������Ϊ���ĵ�ͼ����ת��ֻ��Ҫ��ƽ�ƺ���ת������ϼ���
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

		static DependencyProperty AngleProperty();	
		static DependencyProperty CenterXProperty();
		static DependencyProperty CenterYProperty();

		virtual glm::mat4x4 Value() override;

	protected:
		virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args) override;

	private:
		float m_angle;
		float m_centerX;
		float m_centerY;
	};
}