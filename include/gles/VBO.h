/*******************************************************
**	VBO
**
**	vertex buffer object
**	
**	���㻺�������һ�ֳ��õ�������GPU����ͨ��Ч�ʵļ��������ܹ�
**	�Ѷ������ݻ�����GPU�����²���ÿ�ζ���GPU�ύ����
**		
**		������
**	
********************************************************/
#pragma once
#include "../core/Def.h"

namespace nb{

class NB_API VBO
{
public:
	//����һ�����㻺�����
	//�쳣��
	VBO();
	~VBO();

	//����ʹ��VBO����ʾ֮��������ݶ��Ӵ˻���õ�
	void active();

	//������VBO����ʾ������vbo����������
	void deactive();

	//����һ��������Gpu����������ӵ�пռ�bytes��С�����ԭ���Ѿ��л��棬���������ԭ���Ŀռ�
	void cacheDataToGpu(const float *data, uint32_t bytes);

	//��ȡ����ռ��С
	uint32_t bytes() const;

	//����/�ύ�����ݵ�������
	void updateCacheData(const float *data, uint32_t cacheOffset, uint32_t size);

private:
	unsigned int	m_glHandle;
	uint32_t		m_nBytes;
};

}
