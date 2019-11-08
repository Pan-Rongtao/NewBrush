#pragma once
#include <string>
#include <map>
#include "../core/Def.h"

struct FT_LibraryRec_;
struct FT_FaceRec_;
struct FT_BitmapGlyphRec_;

namespace nb{

class NB_API Font
{
public:
	//����һ�����壬·��Ϊpath���ߴ�Ϊ16
	Font(const std::string &path);

	//����һ�����壬·��Ϊpath���ߴ�ΪfontSize
	Font(const std::string &path, uint32_t fontSize);
	~Font();

	//
	std::string path() const;

	//��������
	std::string familyName() const;

	//�����С����Χ[8, 72]��Խ�罫�����쳣
	void setSize(uint32_t fontSize);
	uint32_t size() const;

	static FT_LibraryRec_ *getFT();

private:
	uint32_t		m_fontSize;
	std::string		m_path;
	FT_FaceRec_		*m_face;
	friend class GlyphMetrics;
};

class NB_API Fonts
{
public:
	//�������л�ȡһ�����壬���û�У����ؿ�
	//name���������ƣ�����"Microsoft YaHei", "SimSun", "STKaiti"��
	static std::shared_ptr<Font> getFont(const std::string &name);

	//��ȡ�Ѵ��ڵ�����
	static std::map<std::string, std::shared_ptr<Font>> systemFonts();

private:
	static void initSystemFonts();
	static std::map<std::string, std::shared_ptr<Font>> s_systemFonts;
};

}