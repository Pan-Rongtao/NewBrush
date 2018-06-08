#pragma once
#include "system/SizeI.h"
#include "media/Bitmap.h"

namespace nb{ namespace Media{

class ImageReader
{
public:
	//����װ�سߴ�
	void SetScaledSize(const nb::System::SizeI &size);

	//��ȡװ�سߴ�
	nb::System::SizeI GetScaledSize() const;

	//��ȡpath���ļ��������������ͼƬ���ݱ�����bm��
	void Read(const nb::System::String &path, nb::Media::Bitmap *pBm);

	//��ȡpath���ļ������ѵȱ�������������ݱ��浽bm��
	void ReadUniform(const nb::System::String &path, nb::Media::Bitmap *pBm, nb::System::SizeI &OriginalSize);

public:
	//����һ��ͼƬ��ȡ��������ȡ�������ߴ�Ϊ160x160
	ImageReader();

	//����һ��ͼƬ��ȡ��������ȡ�������ߴ�Ϊsize
	//�쳣��size���
	ImageReader(const nb::System::SizeI &size);

	virtual ~ImageReader();

private:
	nb::System::SizeI		m_ScaleSize;
};

}}
