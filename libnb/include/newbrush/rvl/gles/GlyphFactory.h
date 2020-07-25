#pragma once
#include "newbrush/core/media/GlyphMetrics.h"
#include "glm/glm.hpp"

namespace nb{

struct Glyph
{
	int			texureId;	//������������
	glm::vec2	uv[4];		//��������
	GlyphInfo	info;		//������Ϣ
};

using GlyphPtr = std::shared_ptr<Glyph>;

class NB_API GlyphFactory
{
public:
	static GlyphPtr getGlyph(FontPtr font, wchar_t ch);

};

}