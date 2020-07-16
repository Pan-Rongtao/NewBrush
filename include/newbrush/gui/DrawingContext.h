#pragma once
#include "newbrush/core/Object.h"
#include "newbrush/core/Point.h"
#include "newbrush/core/Rect.h"
#include "newbrush/gles/Camera.h"
#include "newbrush/gles/Projection.h"

namespace nb {

class Pen;
class Brush;
class ImageSource;
class RenderObject;
using PenPtr = std::shared_ptr<Pen>;
using BrushPtr = std::shared_ptr<Brush>;
using ImageSourcePtr = std::shared_ptr<ImageSource>;
using RenderObjectPtr = std::shared_ptr<RenderObject>;

class NB_API DrawingContext : public Object
{
public:
	DrawingContext();

	//����һ���߶�
	void drawLine(PenPtr pen, const Point &p0, const Point &p1);

	//����һ������
	void drawRectangle(BrushPtr brush, PenPtr pen, const Rect &rect);

	//����һ��Բ�Ǿ���
	void drawRoundedRectangle(BrushPtr brush, PenPtr pen, const Rect &rect, float radiusX, float radiusY);

	//����һ����Բ
	void drawEllipse(BrushPtr brush, PenPtr pen, const Point &center, float radiusX, float radiusY);

	//����ͼƬ
	void drawImage(ImageSourcePtr source, const Rect &rect);

	//�����ı�
	void drawText(/*ImageSourcePtr source, FormattedText*/const Point &p);

private:
	void resize(int width, int height);
	void draw();

	Camera		m_camera;
	Projection	m_projection;
	std::vector<RenderObjectPtr> m_renderObjects;
	friend class Window;
};

}