#pragma once
#include <string>
#include "../core/Def.h"

struct FT_FaceRec_;
struct FT_BitmapGlyphRec_;

namespace nb{ namespace media{

class NB_API FamilyTypeface
{
public:
	FamilyTypeface(const std::string &fontPath);
	~FamilyTypeface();

	//��������
	std::string getFontName() const;

	//�����С����Χ[8, 72]��Խ�罫�����쳣
	void setFontSize(uint32_t fontSize);
	int getFontSize() const;

	FT_BitmapGlyphRec_ *loadChar(wchar_t unicode);

	FT_FaceRec_ *get();

private:
	int				m_fontSize;
	
	FT_FaceRec_		*m_face;
};

} }