#pragma once
#include "newbrush/core/Object.h"
#include "newbrush/core/Point.h"
#include "newbrush/core/Rect.h"

namespace nb {

class Pen;
class Brush;
class ImageSource;
using PenPtr = std::shared_ptr<Pen>;
using BrushPtr = std::shared_ptr<Brush>;
using ImageSourcePtr = std::shared_ptr<ImageSource>;

class DrawingContext : public Object
{
public:
	//����һ���߶�
	void drawLine(PenPtr pen, const Point &p0, const Point &p1);

	//����һ������
	void drawRectangle(BrushPtr brush, PenPtr pen, const Rect &rect);

	//����һ��Բ�Ǿ���
	void drawRoundedRectangle(BrushPtr brush, PenPtr pen, const Rect &rect, double radiusX, double radiusY);

	//����һ����Բ
	void drawEllipse(BrushPtr brush, PenPtr pen, const Point &center, double radiusX, double radiusY);

	//����ͼƬ
	void drawImage(ImageSourcePtr source, const Rect &rect);

	//�����ı�
	void drawText(/*ImageSourcePtr source, FormattedText*/const Point &p);
};

}