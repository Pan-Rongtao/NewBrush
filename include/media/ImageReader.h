#pragma once
#include "../core/Size.h"
#include "Bitmap.h"

namespace nb{ namespace media{

class NB_API ImageReader
{
public:
	//����װ�سߴ�
	void setScaledSize(const nb::core::SizeI &size);

	//��ȡװ�سߴ�
	nb::core::SizeI scaledSize() const;

	//��ȡpath���ļ��������������ͼƬ���ݱ�����bm��
	void read(const nb::core::String &path, Bitmap *pBm);

	//��ȡpath���ļ������ѵȱ�������������ݱ��浽bm��
	void readUniform(const nb::core::String &path, Bitmap *pBm, nb::core::SizeI &OriginalSize);

public:
	//����һ��ͼƬ��ȡ��������ȡ�������ߴ�Ϊ160x160
	ImageReader();

	//����һ��ͼƬ��ȡ��������ȡ�������ߴ�Ϊsize
	//�쳣��size���
	ImageReader(const nb::core::SizeI &size);

	virtual ~ImageReader();

private:
	nb::core::SizeI		m_ScaleSize;
};

}}
