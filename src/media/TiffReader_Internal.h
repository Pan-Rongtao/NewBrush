#pragma once
#define FREEIMAGE_COLORORDER	FREEIMAGE_COLORORDER_RGB	//ʹ��RGB�洢��ʽ
#include "freeImage/FreeImage.h"
#include "system/String.h"
#include "media/Bitmap.h"

namespace nb{ namespace Media{

class TiffReader_Internal
{
public:
	TiffReader_Internal();
	~TiffReader_Internal();

	bool Open(const nb::System::String &path);

	//�ر��ļ�
	void Close();

	//�Ƿ�������
	bool HasData() const;

	//��ȡ��֡��
	int GetFrameCount() const;

	//��ȡָ��֡��ͼ��
	Bitmap GetFrame(int index) const;

private:
	TiffReader_Internal(const TiffReader_Internal &other);
	void operator = (const TiffReader_Internal &other);

	FIMULTIBITMAP		*m_pFreeImage;
};

}}
