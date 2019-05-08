﻿/*******************************************************
**	Brush
**
**	画刷
**	
**	是所有画刷的基类
**	
**	子类有纯色画刷、渐变画刷、纹理画刷等
**	
**
**		潘荣涛
**	
********************************************************/
#pragma once
#include "../core/Property.h"
#include "../core/Color.h"
#include "../gui/ImageSource.h"

namespace nb{ namespace gui {

//class Brush
class NB_API Brush
{
protected:
	Brush();
	Brush(double opacity);
	virtual ~Brush();

	nb::core::Property_rw<double>			Opacity;

private:
	Brush(const Brush &other) = delete;
	void operator = (const Brush &other) = delete;

};

//class SolidColorBrush
class NB_API SolidColorBrush : public Brush
{
public:
	SolidColorBrush();
	explicit SolidColorBrush(const nb::core::Color &color);

	nb::core::Property_rw<nb::core::Color>	Color;
};

//class ImageBrush
class NB_API ImageBrush : public Brush
{
public:
	ImageBrush();
	explicit ImageBrush(const std::shared_ptr<ImageSource> &imgSource);

	nb::core::Property_rw<std::shared_ptr<ImageSource>>	Source;
};

}}
