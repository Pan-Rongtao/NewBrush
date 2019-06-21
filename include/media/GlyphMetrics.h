#pragma once
#include "../core/Size.h"

namespace nb{ namespace media {

enum class TextWrappingE
{
	NoWrap,				//������
	Wrap,				//����
	WrapWithOverflow,
};

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

class Font;
class NB_API GlyphMetrics
{
public:
	//����һ��unicode�ַ�
	static GlyphInfo measureGlyp(std::shared_ptr<Font> font, wchar_t ch);

	//����һ���ַ���������ռ�õ����سߴ�
	static core::Size measureGlyphAltas(std::shared_ptr<Font> font, const std::string &text, float charSpacing, float lineHeight, TextWrappingE tw, float widthMax);

};

} }