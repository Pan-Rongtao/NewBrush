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

namespace nb{ namespace gl{

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
	//�쳣��bytes < 0
	void cacheDataToGpu(const float *data, int bytes);

	//��ȡ����ռ��С
	int bytes() const;

	//����/�ύ�����ݵ�������
	//�쳣��sizeС��0����size+cacheOffset���ڻ��������󴴽�ʱ��ָ���Ĵ�С
	void updateCacheData(const float *data, int cacheOffset, int size);

private:
	unsigned int	m_glHandle;
	int				m_nBytes;
};

}}
