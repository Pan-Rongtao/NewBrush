/*******************************************************
**	TextureMipmap
**
**	�༶������
**	
**		һ����������level�㼶���ϵ�������󡣼�������Դͼ����Ϊ
**	32x16����ᱣ��32x16��16x8��8x4��4x2��2x1,1x1��������
**
**		���ⲿʹ����˵�����ؿ����ڲ������ڲ�ѡ���ϸ�ڡ�
**	OpengGL���Զ�ѡ����Ϊ�ӽ��ĳߴ磬������ָ����������˷�ʽ���й���
**
**	
**	�����������ڴ�����С�����ر����ã��ɱ�֤ͼ�񲻹���ʧ�棻
**	������ƶ���˸
**
**		������
**	
********************************************************/
#pragma once
#include "gles/Texture2D.h"

namespace nb{ namespace gl{ namespace Gles{

class NB_EXPORT TextureMipmap : public Texture2D
{
public:
	//�����༶����
	void Generate();

public:
	TextureMipmap();
	~TextureMipmap();
};

}}}
