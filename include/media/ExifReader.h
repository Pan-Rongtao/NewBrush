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
#include <string>
#include "Bitmap.h"

namespace nb{ namespace media{

class ExifReader_Internal;
class NB_API ExifReader
{
public:
	struct ThumbnailProperties
	{
		int Width;
		int Height;
		int Bytes;
	};

public:
	//����һ��ExifReader��ȡ��
	ExifReader();

	ExifReader(const ExifReader &other) = delete;
	void operator = (const ExifReader &other) = delete;

	~ExifReader();

	//��
	//�쳣���ļ�������
	void open(const std::string &path);

	//��ȡ���
	int width() const;

	//��ȡ�߶�
	int height() const;

	//��ȡ����ͼ������Ϣ
	void getThumbnailsProperties(std::vector<ThumbnailProperties> &results) const;

	//��ȡ����ͼ
	void getThumbnails(std::vector<Bitmap> &results) const;

private:
	ExifReader_Internal		*m_internal;
};

}}
