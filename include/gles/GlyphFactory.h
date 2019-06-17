#pragma once
#include "../media/Font.h"
#include "glm/glm.hpp"

namespace nb{ namespace gl{

struct Glyph
{
	int					texureId;	//������������
	glm::vec2			uv[4];		//��������
	media::GlyphInfo	info;		//������Ϣ
};

class NB_API GlyphFactory
{
public:
	static std::shared_ptr<Glyph> getGlyph(wchar_t ch);

};

}}