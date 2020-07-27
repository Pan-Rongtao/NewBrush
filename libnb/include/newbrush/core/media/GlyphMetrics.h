#pragma once
#include "newbrush/core/base/Size.h"
#include "newbrush/core/media/Font.h"
#include "newbrush/core/media/Media.h"

namespace nb{

struct GlyphInfo
{
	int				left;
	int				top;
	int				advancex;
	int				advancey;
	unsigned int    bm_width;
	unsigned int    bm_height;
	int             bm_pitch;
	unsigned char*  bm_buffer;
};

class NB_API GlyphMetrics
{
public:
	//����һ��unicode�ַ�
	static GlyphInfo measureGlyp(FontPtr font, wchar_t ch);

	//����һ���ַ���������ռ�õ����سߴ�
	static Size measureGlyphAltas(FontPtr font, const std::string &text, float charSpacing, float lineHeight, TextWrappingE tw, float widthMax);

};

}