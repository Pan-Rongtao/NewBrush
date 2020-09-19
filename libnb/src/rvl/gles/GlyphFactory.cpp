#include "newbrush/rvl/gles/GlyphFactory.h"
#include <map>
#include <vector>
#include "newbrush/rvl/gles/Texture2D.h"
#include "newbrush/core/Log.h"
#include "newbrush/core/media/Font.h"
#include <opengl/GLES2/gl2.h>

using namespace nb;

class TextureGlyphAtlas;
static std::vector<TextureGlyphAtlas *>	g_glyphAtlas;
constexpr int							GlyphAltasWidth		= 1024;
constexpr int							GlyphAltasHeight	= 1024;

class NB_API TextureGlyphAtlas : public Texture2D
{
public:
	//����һ������ͼ������������Ϊwidth, height�����εĳߴ�ΪglypSize
	TextureGlyphAtlas(FontPtr font, const std::wstring &unicodeStr)
		: Texture2D(GlyphAltasWidth, GlyphAltasHeight) , m_x(0) , m_y(0) , m_font(font)
	{
		if ((width() != 0 && height() != 0) && (width() % m_font->size() != 0 || height() % m_font->size() != 0))
			Log::warn("width or height mod glypSize != 0");

		bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, width(), height(), 0, GL_ALPHA, GL_UNSIGNED_BYTE, 0);
		unbind();
		appendText(unicodeStr);
		g_glyphAtlas.push_back(this);
	}

	~TextureGlyphAtlas()
	{
		auto iter = std::find(g_glyphAtlas.begin(), g_glyphAtlas.end(), this);
		if (iter != g_glyphAtlas.end())
			g_glyphAtlas.erase(iter);
	}

	//font
	FontPtr font()
	{
		return m_font;
	}

	//��ȡһ���ַ�����Ϣ
	//������ڷ��ش��ڵ����Σ������½�һ�������Σ����洢����������TextureGlyphAtlas�����������½������շ��ص�Glyph.texureIdΪ-1
	GlyphPtr getGlyph(wchar_t ch)
	{
		auto iter = m_glyphs.find(ch);
		return (iter != m_glyphs.end()) ? iter->second : appendChar(ch);
	}

	//���ص�Plyph��texureId=-1��ʾ����ʧ�ܣ�����
	GlyphPtr appendChar(wchar_t ch)
	{
		if (m_glyphs.find(ch) != m_glyphs.end())
			return{ nullptr };

		auto glyph = GlyphMetrics::measureGlyp(font(), ch);
		//�����п���
		if (m_x + glyph.bm_width > width() && m_y + m_font->size() > height())
			return{ nullptr };

		glm::vec2 uv[4];

		bind();
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		if (m_x + glyph.bm_width <= width())
		{
			glTexSubImage2D(GL_TEXTURE_2D, 0, (int)m_x, (int)m_y, glyph.bm_width, glyph.bm_height, GL_ALPHA, GL_UNSIGNED_BYTE, glyph.bm_buffer);
			uv[0] = { m_x / width(), (m_y + glyph.bm_height) / height() };
			uv[1] = { (m_x + glyph.bm_width) / width(), (m_y + glyph.bm_height) / height() };
			uv[2] = { (m_x + glyph.bm_width) / width(), m_y / height() }; 
			uv[3] = { m_x / width(), m_y / height() };
			m_x += glyph.bm_width;
		}
		else
		{
			if (m_y + m_font->size() <= height())
			{
				m_x = static_cast<float>(glyph.bm_width);
				m_y += m_font->size();
				glTexSubImage2D(GL_TEXTURE_2D, 0, 0, (int)m_y, glyph.bm_width, glyph.bm_height, GL_ALPHA, GL_UNSIGNED_BYTE, glyph.bm_buffer);
				uv[0] = { 0.0, (m_y + glyph.bm_height) / height() };
				uv[1] = { glyph.bm_width / width(), (m_y + glyph.bm_height) / height() };
				uv[2] = { glyph.bm_width / width(), m_y / height() }; 
				uv[3] = { 0.0, m_y / height() };
			}
		}
		unbind();

		GlyphPtr ret = std::make_shared<Glyph>();
		ret->texureId = m_handle;
		ret->info = glyph;
		ret->uv[0] = uv[0];
		ret->uv[1] = uv[1];
		ret->uv[2] = uv[2];
		ret->uv[3] = uv[3];
		m_glyphs.insert({ ch, ret });
		return ret;
	}

	void appendText(const std::wstring &unicodeStr)
	{
		for (auto const &ch : unicodeStr)
			appendChar(ch);
	}

private:
	float										m_x;
	float										m_y;
	std::map<wchar_t, GlyphPtr>	m_glyphs;
	FontPtr						m_font;
	friend class GlyphFactory;
};

GlyphPtr GlyphFactory::getGlyph(FontPtr font, wchar_t ch)
{
	GlyphPtr ret;
	for (auto &atlas : g_glyphAtlas)
	{
		ret = atlas->getGlyph(ch);
		if (ret)
			return ret;
	}

	auto newAtlas = new TextureGlyphAtlas(font, L"");
	Log::info("char[%d] at new TextureGlyphAtlas", ch);
	return newAtlas->getGlyph(ch);
}