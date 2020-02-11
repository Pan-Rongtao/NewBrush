#pragma once
#include "newbrush/gui/UIElement.h"
#include "newbrush/gui/Stretch.h"
#include "newbrush/media/Media.h"

namespace nb{
class Brush;
namespace gui{

using nb::media::PenLineCapE;
using nb::media::PenLineJoinE;
class NB_API Shape : public UIElement
{
public:
	static DependencyProperty		FillProperty();				//��仭ˢ����������
	static DependencyProperty		StrokeProperty();			//������ˢ����������
	static DependencyProperty		StrokeThicknessProperty();	//������ȵ���������
	static DependencyProperty		StrokeStartLineCapProperty();//��������������ñ��ʽ����������
	static DependencyProperty		StrokeEndLineCapProperty();	//�����������յ��ñ��ʽ����������
	static DependencyProperty		StrokeDashArrayProperty();	//���ߵļ�϶����������
	static DependencyProperty		StrokeDashOffsetProperty();	//���߿�ʼ��ƫ�Ƶ���������
	static DependencyProperty		StrokeDashCapProperty();	//�ʻ�ñ����������
	static DependencyProperty		StrokeLineJoinProperty();	//����������ʽ����������
	static DependencyProperty		StretchProperty();			//������ʽ����������

protected:
	Shape();
	void updateMeterial(std::shared_ptr<nb::RenderObject> ro, std::shared_ptr<Brush> brush);

	std::shared_ptr<RenderObject>	m_fillObject;
	std::shared_ptr<RenderObject>	m_strokeObject;
};

}}