/******************************************************************************

* Copyright (c) 2016���������������������޹�˾

* All rights reserved

* ��д��: ������

* ��д����: 2017-03

* ��Ҫ����: ExifReader
				
		EXIF��Exchangeable Image File���ǡ��ɽ���ͼ���ļ�������д�����а�����
		ר��Ϊ�����������Ƭ�����Ƶ�Ԫ���ݣ����Լ�¼������Ƭ���������������ͼ
		������������Ϣ��
			1����������
			2���������ģ�������ͷ������Ƶȣ�
			3����������������ٶȡ���ȦFֵ��ISO�ٶȡ����ࡢ���ģʽ�ȣ�
			4��ͼ����������񻯡��Աȶȡ����Ͷȡ���ƽ��ȣ�
			5��ͼ����������Ȩ��Ϣ
			6��GPS��λ����
			7������ͼ��һ��ͼƬ���ܰ����������ͼ���ݣ�

* �޸ļ�¼:

*****************************************************************************/
#pragma once
#include <vector>
#include "system/String.h"
#include "media/Bitmap.h"

namespace nb{ namespace Media{

class ExifReader_Internal;
class NB_EXPORT ExifReader
{
public:
	struct ThumbnailProperties
	{
		int Width;
		int Height;
		int Bytes;
	};

public:
	//��
	//�쳣���ļ�������
	void Open(const nb::System::String &fileName);

	//��ȡ���
	int GetWidth() const;

	//��ȡ�߶�
	int GetHeight() const;

	//��ȡ����ͼ������Ϣ
	void GetThumbnailsProperties(std::vector<ThumbnailProperties> &results) const;

	//��ȡ����ͼ
	void GetThumbnails(std::vector<nb::Media::Bitmap> &results) const;

public:
	//����һ��ExifReader��ȡ��
	ExifReader();

	//����һ��ExifReader����ָ��·��ΪfileName���ļ�
	//�쳣���ļ�������
	explicit ExifReader(const nb::System::String &fileName);

	~ExifReader();

private:
	ExifReader(const ExifReader &other);
	void operator = (const ExifReader &other);

	ExifReader_Internal		*m_internal;
};

}}
