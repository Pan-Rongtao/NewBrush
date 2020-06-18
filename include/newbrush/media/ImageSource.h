﻿/*******************************************************
**	ImageSource
**
**		图片源
**	
**	
**		由路径加载的位图源，
**	
**
**		潘荣涛
**	
********************************************************/
#pragma once
#include "newbrush/media/Bitmap.h"

namespace nb{

class NB_API ImageSource
{
public:
	ImageSource();
	ImageSource(const std::string &uri);

	void load(const unsigned char *buffer, uint32_t bytes);

	int width() const;
	int height() const;
	int channels() const;

	const std::string &stream() const;


private:
	std::string	m_stream;
	int			m_width;
	int			m_height;
	int			m_channels;
};

}
