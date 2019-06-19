#pragma once
#include <string>
#include <map>
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

	GlyphInfo getGlyphInfo(wchar_t unicode);

private:
	uint32_t		m_fontSize;
	std::string		m_path;
	FT_FaceRec_		*m_face;
};


class NB_API Fonts
{
public:
	static constexpr char *MicrosoftYaHei		= "Microsoft YaHei";	//΢���ź�
	static constexpr char *SimSun				= "SimSun";				//����
	static constexpr char *STKaiti				= "STKaiti";			//���Ŀ���

	//�������л�ȡһ�����壬���û�У����ؿ�
	static std::shared_ptr<Font> getFont(const std::string &name);

	//��ȡ�Ѵ��ڵ�����
	static std::map<std::string, std::shared_ptr<Font>> systemFonts();

};

} }