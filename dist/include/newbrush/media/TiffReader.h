#pragma once
#include "../core/String.h"
#include "Bitmap.h"

namespace nb{ namespace media{

class TiffReader_Internal;
class NB_API TiffReader
{
public:
	//����һ��Tiff��ȡ��
	TiffReader();

	~TiffReader();

public:
	//��һ��tiff�ļ�
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
	TiffReader(const TiffReader &other);
	void operator = (const TiffReader &other);

	TiffReader_Internal	*m_internal;
};


}}
