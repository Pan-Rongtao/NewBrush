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
	static DependencyProperty FillProperty();				//��仭ˢ����������(std::shared_ptr<Brush>)
	static DependencyProperty StrokeProperty();				//������ˢ����������(std::shared_ptr<Brush>)
	static DependencyProperty StrokeThicknessProperty();	//������ȵ���������(float)
	static DependencyProperty StrokeStartLineCapProperty();	//��������������ñ��ʽ����������(PenLineCapE)
	static DependencyProperty StrokeEndLineCapProperty();	//�����������յ��ñ��ʽ����������(PenLineCapE)
	static DependencyProperty StrokeDashArrayProperty();	//���ߵļ�϶����������(std::vector<float>)
	static DependencyProperty StrokeDashOffsetProperty();	//���߿�ʼ��ƫ�Ƶ���������(float)
	static DependencyProperty StrokeDashCapProperty();		//�ʻ�ñ����������(PenLineCapE)
	static DependencyProperty StrokeLineJoinProperty();		//����������ʽ����������(PenLineJoinE)
	static DependencyProperty StretchProperty();			//������ʽ����������(StretchE)

protected:
	Shape();
	void updateMeterial(std::shared_ptr<nb::RenderObject> ro, std::shared_ptr<Brush> brush);

	std::shared_ptr<RenderObject>	m_fillObject;
	std::shared_ptr<RenderObject>	m_strokeObject;
};

}}