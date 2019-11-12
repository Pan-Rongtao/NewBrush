#pragma once
#include "../gui/UIElement.h"
#include "../gui/Brush.h"
#include "../gui/Stretch.h"

namespace nb{ namespace gui{

//��ñ��ʽ
enum class PenLineCapE
{
	Flat,		//û�б�ñ
	Round,		//Բ�α�ñ
	Square,		//���α�ñ
	Triangle,	//�����α�ñ
};

//������ʽ
enum class PenLineJoinE
{
	Beval,
	Miter,
	Round,
};

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
	Property_rw<PenLineCapE>		StrokeDashCap;				//�������˵ı�ñ��ʽ����������Line��Polyline����������״����Ч��
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

	std::shared_ptr<nb::gl::RenderObject>	m_fillObj;
	std::shared_ptr<nb::gl::RenderObject>	m_strokeObj;
};

//��
class NB_API Line : public Shape
{
public:
	Line();
	virtual ~Line() = default;

	Property_rw<float>			X1;				//X1
	Property_rw<float>			X2;				//X2
	Property_rw<float>			Y1;				//Y1
	Property_rw<float>			Y2;				//Y2
	static DependencyProperty	X1Property();	//X1����������
	static DependencyProperty	X2Property();	//X2����������
	static DependencyProperty	Y1Property();	//Y1����������
	static DependencyProperty	Y2Property();	//Y2����������

	virtual void onRender(std::shared_ptr<nb::gl::Context> drawContext) override;

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

};

//���߶�
class NB_API Polyline : public Shape
{
public:
	Polyline();
	virtual ~Polyline() = default;

	Property_rw<std::vector<Point>>	Points;				//�㼯��
	static DependencyProperty		PointsProperty();	//�㼯�ϵ���������

	virtual void onRender(std::shared_ptr<nb::gl::Context> drawContext) override;

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

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