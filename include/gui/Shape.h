#pragma once
#include "../gui/UIElement.h"
#include "../gui/Brush.h"
#include "../gui/Stretch.h"

namespace nb{ namespace gui{

enum class PenLineCapE
{
	Flat,
	Round,
	Square,
	Triangle,
};

enum class PenLineJoinE
{
	Beval,
	Miter,
	Round,
};

class NB_API Shape : public UIElement
{
public:
	Property_rw<shared_ptr<Brush>>		Fill;						//���
	Property_rw<StretchE>				Stretch;					//������ʽ
	Property_rw<shared_ptr<Brush>>		Stroke;						//�ʻ�
	Property_rw<PenLineCapE>			StrokeDashCap;				//�ʻ�ñ
	Property_rw<PenLineJoinE>			StrokeLineJoin;				//
	Property_rw<Thickness>				StrokeThickness;			//���ʺ��
	
	static const DependencyProperty		FillProperty();				//������������
	static const DependencyProperty		StretchProperty();			//������ʽ����������
	static const DependencyProperty		StrokeProperty();			//�ʻ�����������
	static const DependencyProperty		StrokeDashCapProperty();	//�ʻ�ñ����������
	static const DependencyProperty		StrokeLineJoinProperty();	//
	static const DependencyProperty		StrokeThicknessProperty();	//�ʻ���ȵ���������

protected:
	Shape();

};

}}