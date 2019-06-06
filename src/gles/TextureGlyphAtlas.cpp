#include "gles/TextureGlyphAtlas.h"
#include <opengl/GLES2/gl2.h>
#include <freetype/ft2build.h>
#include <freetype/ftglyph.h>
#include <freetype/ftbitmap.h>
#include "media/FontFamily.h"
#include FT_FREETYPE_H

using namespace nb::core;
using namespace nb::gl;
using namespace nb::media;
#define GLYPHATLAS_WIDTH	512
#define GLYPHATLAS_HEIGHT	512

TextureGlyphAtlas::TextureGlyphAtlas(std::shared_ptr<Font> font, const std::wstring &unicodeStr)
	: Texture2D(GLYPHATLAS_WIDTH, GLYPHATLAS_HEIGHT)
	, m_x(0)
	, m_y(0)
	, m_font(font)
	, m_full(false)
{
	if ((m_width != 0 && m_height != 0) && (m_width % m_font->size() != 0 || m_height % m_font->size() != 0))
		printf("warning: width or height mod glypSize != 0\n");

	setWrapping(TextureWrapping());
	setFilter(TextureFilter());
	bind();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, m_width, m_height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, 0);
	unbind();
	appendText(unicodeStr);
}

std::shared_ptr<Font> TextureGlyphAtlas::font()
{
	return m_font;
}

Glyph TextureGlyphAtlas::appendChar(wchar_t ch)
{
	if (m_glyphs.find(ch) != m_glyphs.end())
		return {-1};

	auto glyph = m_font->getGlyphInfo(ch);
	//�����п���
	if(m_x + glyph.bm_width > m_width && m_y + m_font->size() > m_height)
		return{ -1 };

	core::Vec2 uv[4];

	bind();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	if (m_x + glyph.bm_width <= m_width)
	{
		glTexSubImage2D(GL_TEXTURE_2D, 0, m_x, m_y, glyph.bm_width, glyph.bm_height, GL_ALPHA, GL_UNSIGNED_BYTE, glyph.bm_buffer);
		uv[0] = { (float)(m_x + glyph.bm_width) / width(), (float)(m_y + glyph.bm_height) / height() };
		uv[1] = { (float)(m_x / width()), (float)(m_y + glyph.bm_height) / height() };
		uv[2] = { (float)m_x / width(), (float)m_y / height() };
		uv[3] = { (float)(m_x + glyph.bm_width) / width(), (float)m_y / height() };
		m_x += glyph.bm_width;
	}
	else
	{
		if (m_y + m_font->size() <= m_height)
		{
			m_x = glyph.bm_width;
			m_y += m_font->size();
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, m_y, glyph.bm_width, glyph.bm_height, GL_ALPHA, GL_UNSIGNED_BYTE, glyph.bm_buffer);
			uv[0] = { (float)glyph.bm_width / width(), (float)(m_y + glyph.bm_height) / height() };
			uv[1] = { 0.0, (float)glyph.bm_height / height() };
			uv[2] = { 0.0, 0.0 };
			uv[3] = { (float)glyph.bm_width / width(), 0.0 };
		}
	}
	unbind();

	return{ (int)m_handle, { uv[0], uv[1], uv[2], uv[3] }, glyph };
}

void TextureGlyphAtlas::appendText(const std::wstring & unicodeStr)
{
	for (auto const &ch : unicodeStr)
		appendChar(ch);
}

Glyph TextureGlyphAtlas::getGlyph(wchar_t ch)
{
	auto iter = m_glyphs.find(ch);
	if (iter != m_glyphs.end())
	{
		return iter->second;
	}
	else
	{
		return appendChar(ch);
	}
}

std::vector<TextureGlyphAtlas>	GlyphFactory::m_glyphAtlas;
Glyph GlyphFactory::getGlyph(wchar_t ch)
{
	Glyph ret;
	for (auto &atlas : m_glyphAtlas)
	{
		ret = atlas.getGlyph(ch);
		if (ret.texureId != -1)
			return ret;
	}

	auto newAtlas = std::make_shared<TextureGlyphAtlas>(m_glyphAtlas[0].font(), L"");
	return newAtlas->getGlyph(ch);
}
