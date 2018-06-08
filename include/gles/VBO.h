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
#include "core/Object.h"

namespace nb{ namespace gl{ namespace Gles{

class NB_EXPORT VBO
{
public:
	//����һ�����㻺�����
	//�쳣��
	VBO();
	~VBO();

	//����ʹ��VBO����ʾ֮��������ݶ��Ӵ˻���õ�
	void Active();

	//������VBO����ʾ������vbo����������
	void Deactive();

	//����һ��������Gpu����������ӵ�пռ�bytes��С�����ԭ���Ѿ��л��棬���������ԭ���Ŀռ�
	//�쳣��bytes < 0
	void CacheDataToGpu(const float *data, int bytes);

	//��ȡ����ռ��С
	int GetBytes() const;

	//����/�ύ�����ݵ�������
	//�쳣��bytesС��0����bytes+cacheOffset���ڻ��������󴴽�ʱ��ָ���Ĵ�С
	void UpdateCacheData(const float *data, int cacheOffset, int bytes);

private:
	unsigned int	m_glHandle;
	int				m_nBytes;
};

}}}
