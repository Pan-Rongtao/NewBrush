#pragma once
#include "../core/Def.h"
#include "glm/glm.hpp"
#include <map>
#include <vector>
#include <string>
#include "Texture2D.h"
#include "../media/Font.h"

namespace nb{ namespace gl{

struct Glyph
{
	int					texureId;	//������������
	glm::vec2			uv[4];		//��������
	media::GlyphInfo	info;		//������Ϣ
};

class NB_API TextureGlyphAtlas : public Texture2D
{
public:
	//����һ������ͼ���������Ϊwidth, height�����εĳߴ�ΪglypSize
	TextureGlyphAtlas(std::shared_ptr<nb::media::Font> font, const std::wstring &unicodeStr);
	~TextureGlyphAtlas();

	//font
	std::shared_ptr<media::Font> font();

	//׷���ı�������ʵ��׷�ӵĳ��ȣ������ĳ��ȱ����ԣ�
	//���ص�Plyph��texureId=-1��ʾ���ʧ�ܣ�����
	Glyph appendChar(wchar_t unicode);
	void appendText(const std::wstring &unicodeStr);

	//��ȡһ���ַ�����Ϣ
	Glyph getGlyph(wchar_t ch);
	
private:
	float						m_x;
	float						m_y;
	std::map<wchar_t, Glyph>	m_glyphs;
	bool						m_full;
	std::shared_ptr<media::Font>m_font;
};

class NB_API GlyphFactory
{
public:
	static Glyph getGlyph(wchar_t ch);

private:
	static std::vector<TextureGlyphAtlas *>	m_glyphAtlas;
	friend class TextureGlyphAtlas;
};

}}