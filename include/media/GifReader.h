#pragma once
#include "system/String.h"
#include "media/Bitmap.h"

namespace nb{ namespace Media{

class GifReader_Internal;
class NB_EXPORT GifReader
{
public:
	//��һ��gif�ļ�
	bool Open(const nb::System::String &path);

	//�ر��ļ�
	void Close();

	//�Ƿ�������
	bool HasData() const;

	//��ȡ��֡��
	int GetFrameCount() const;

	//��ȡָ��֡��ͼ��
	Bitmap GetFrame(int index) const;

public:
	//����һ��Gif��ȡ��
	GifReader();

	~GifReader();

private:
	GifReader(const GifReader &other);
	void operator = (const GifReader &other);

	GifReader_Internal	*m_internal;
};

}}
