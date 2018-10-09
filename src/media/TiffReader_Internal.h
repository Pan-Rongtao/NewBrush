#pragma once
#define FREEIMAGE_COLORORDER	FREEIMAGE_COLORORDER_RGB	//ʹ��RGB�洢��ʽ
#include "freeImage/FreeImage.h"
#include "core/String.h"
#include "media/Bitmap.h"

namespace nb{ namespace media{

class TiffReader_Internal
{
public:
	TiffReader_Internal();
	~TiffReader_Internal();

	bool open(const nb::core::String &path);

	//�ر��ļ�
	void close();

	//�Ƿ�������
	bool hasData() const;

	//��ȡ��֡��
	int frameCount() const;

	//��ȡָ��֡��ͼ��
	Bitmap frame(int index) const;

private:
	TiffReader_Internal(const TiffReader_Internal &other);
	void operator = (const TiffReader_Internal &other);

	FIMULTIBITMAP		*m_pFreeImage;
};

}}
