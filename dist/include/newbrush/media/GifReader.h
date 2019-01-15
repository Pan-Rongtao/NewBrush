#pragma once
#include "../core/String.h"
#include "Bitmap.h"

namespace nb{ namespace media{

class GifReader_Internal;
class NB_API GifReader
{
public:
	//����һ��Gif��ȡ��
	GifReader();

	~GifReader();

public:
	//��һ��gif�ļ�
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
	GifReader(const GifReader &other);
	void operator = (const GifReader &other);

	GifReader_Internal	*m_internal;
};

}}
