#pragma once
#include <string>
#include "../core/Def.h"

struct FT_LibraryRec_;
namespace nb{ namespace media{

class NB_API FontFamily
{
public:
	//����һ��FontFamily������·��ΪfontPath;
	FontFamily(const std::string &fontPath);

	//��׼��
	void setBaseline(int bl);
	int getBaseline() const;

	//�м��
	void setLineSpacing(int ls);
	int getLineSpacing() const;

	static FT_LibraryRec_ *getFT();

private:
	int		m_baseline;
	int		m_lineSpacing;
};

}}