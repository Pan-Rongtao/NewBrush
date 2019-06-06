#pragma once
#include <string>
#include "../core/Def.h"

struct FT_FaceRec_;
struct FT_BitmapGlyphRec_;

namespace nb{ namespace media{

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

class NB_API Font
{
public:
	//����һ�����壬·��ΪfontPath���ߴ�Ϊ16
	Font(const std::string &fontPath);

	//����һ�����壬·��ΪfontPath���ߴ�ΪfontSize
	Font(const std::string &fontPath, uint32_t fontSize);
	~Font();

	//��������
	std::string name() const;

	//�����С����Χ[8, 72]��Խ�罫�����쳣
	void setSize(uint32_t fontSize);
	uint32_t size() const;

	GlyphInfo getGlyphInfo(wchar_t unicode);

private:
	uint32_t		m_fontSize;
	FT_FaceRec_		*m_face;
};

} }