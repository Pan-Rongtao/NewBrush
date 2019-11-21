#pragma once
#include "../gui/UIElement.h"
#include "../gui/Brush.h"
#include "../gui/Stretch.h"
#include "../media/Media.h"

namespace nb{ namespace gui{

using nb::media::PenLineCapE;
using nb::media::PenLineJoinE;
//��״��
class NB_API Shape : public UIElement
{
public:
	Property_rw<shared_ptr<Brush>>	Fill;						//��仭ˢ���������״��rectangle��eclipse��polygon��Ч��line�Ȳ���Ч��
	Property_rw<shared_ptr<Brush>>	Stroke;						//������ˢ
	Property_rw<float>				StrokeThickness;			//�������
	Property_rw<PenLineCapE>		StrokeStartLineCap;			//��������������ñ��ʽ����������Line��Polyline����������״����Ч��
	Property_rw<PenLineCapE>		StrokeEndLineCap;			//�����������յ��ñ��ʽ����������Line��Polyline����������״����Ч��
	Property_rw<std::vector<float>>	StrokeDashArray;			//���ߵļ�϶ռλ����λΪStrokeThickness������{1, 2}����ʾ����1����϶2�����Դ�ѭ��������ĩ
	Property_rw<float>				StrokeDashOffset;			//���߿�ʼ��ƫ�ƣ���ֵΪ��ƫ����ֵΪ��ƫ��
	Property_rw<PenLineCapE>		StrokeDashCap;				//�������˵ı�ñ��ʽ
	Property_rw<PenLineJoinE>		StrokeLineJoin;				//����������ʽ
	Property_rw<StretchE>			Stretch;					//������ʽ
	
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
	void updateMeterial(std::shared_ptr<nb::gl::RenderObject> ro, std::shared_ptr<Brush> brush);

	std::shared_ptr<nb::gl::RenderObject>	m_fillObject;
	std::shared_ptr<nb::gl::RenderObject>	m_strokeObject;
};


//�����
class NB_API Polygon : public Shape
{
public:
	Polygon();
	virtual ~Polygon() = default;

	Property_rw<std::vector<Point>>	Points;				//�㼯��
	static DependencyProperty		PointsProperty();	//�㼯�ϵ���������

	virtual void onRender(std::shared_ptr<nb::gl::Context> drawContext) override;

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

};

//��Բ
class NB_API Ellipse : public Shape
{
public:
	Ellipse();

	virtual void onRender(std::shared_ptr<nb::gl::Context> drawContext) override;

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

private:
	void onPropertyChanged(const PropertyChangedArgs & args);
};

}}