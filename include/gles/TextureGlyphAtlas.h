#pragma once
#include "../core/Def.h"
#include <map>
#include <string>
#include "Texture2D.h"
#include "../media/FamilyTypeface.h"

namespace nb{ namespace gl{

struct Glyph
{
	int texId;	//������������
	int left;	//
	int right;	//
	int top;
	int bottom;

};

class NB_API TextureGlyphAtlas : public Texture2D
{
public:
	//����һ������ͼ���������Ϊwidth, height�����εĳߴ�ΪglypSize
	TextureGlyphAtlas(uint32_t width, uint32_t height, uint32_t glypSize);

	//׷���ı�������ʵ��׷�ӵĳ��ȣ������ĳ��ȱ����ԣ�
	uint32_t appendChar(wchar_t unicode);
	uint32_t appendText(const std::wstring &unicodeStr);

	//��ȡһ���ַ�����Ϣ
	
private:
	uint32_t					m_x;
	uint32_t					m_y;
	uint32_t					m_glypSize;
	std::map<wchar_t, Glyph>	m_glyphs;
	media::FamilyTypeface		m_face;
};

}}