#pragma once
#include "system/String.h"
#include "media/Bitmap.h"

namespace nb{ namespace Media{

class TiffReader_Internal;
class NB_EXPORT TiffReader
{
public:
	//��һ��tiff�ļ�
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
	//����һ��Tiff��ȡ��
	TiffReader();

	~TiffReader();

private:
	TiffReader(const TiffReader &other);
	void operator = (const TiffReader &other);

	TiffReader_Internal	*m_internal;
};


}}
